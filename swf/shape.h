//
//  shape.h
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SWFParser_shape_h
#define SWFParser_shape_h

#include <vector>
#include "types.h"
#include "utils.h"

using namespace std;

namespace swf 
{	
	enum fill_style_type_t {
		solid = 0,
		gradient_linear = 0x10,
		gradient_radial = 0x12,
		gradient_focal_radial = 0x13,
		bitmap_repeat = 0x40,
		bitmap_clipped = 0x42,
		bitmap_repeat_nonsmoothed = 0x42,
		bitmap_clipped_nonsmoothed = 0x43
	};
	
	struct FILLSTYLE
	{
		UI8 fill_style_type;
		RGBA color;
	};
	
	istream &operator>>(istream &input, FILLSTYLE &style) 
	{
		READ(input, style.fill_style_type);
		assert(style.fill_style_type == solid);
		READ(input, style.color);
		return input;
	}
	
	typedef vector<FILLSTYLE> FILLSTYLEARRAY;
	
	istream &operator>>(istream &input, FILLSTYLEARRAY &array) {
		UI16 num_styles = 0;
		READ_TYPE(input, num_styles, UI8);
		if (num_styles == 0xFF)
			READ_TYPE(input, num_styles, UI16);
		array.reserve(num_styles);
		for (int i=0; i<num_styles; ++i) {
			FILLSTYLE style;
			input >> style;
			array.push_back(style);
		}
		return input;
	}
	
	struct LINESTYLE2
	{
		UI16 width;
		RGBA color;
	};
	
	istream &operator>>(istream &input, LINESTYLE2 &style) {
		READ(input, style.width);
		BitReader<UI8> reader(input);
		reader.skip(2); // cap style
		UI8 join_style;
		reader.read(join_style, 2);
		bool has_fill_flag;
		reader.read(has_fill_flag, 1); // has fill flag
		reader.skip(2); // no hscale and vscale
		reader.skip(1); // pixel hinting
		reader.skip(5); // reserved
		reader.skip(1); // no close
		reader.skip(2); // end cap style
		
		if (join_style == 2)
			reader.skip(sizeof(UI16)*8);
		if (!has_fill_flag) {
			input >> style.color;
		} else {
			assert(false); // fill stroke not supported
		}
		
		return input;
	}
	
	typedef vector<LINESTYLE2> LINESTYLEARRAY;
	
	istream &operator>>(istream &input, LINESTYLEARRAY &array) {
		UI16 count;
		READ_TYPE(input, count, UI8);
		if (count == 0xFF)
			READ_TYPE(input, count, UI16);
		for (int i=0; i<count; i++) {
			LINESTYLE2 style;
			input >> style;
			array.push_back(style);
		}
		return input;
	}
	
	struct SHAPERECORD
	{
		
	};
	
	enum RecordType {
		ENDSHAPE,
		STYLECHANGE,
		STRAIGHTEDGE,
		CURVEDEDGE
	};
	
	struct SHAPEWITHSTYLE 
	{
		FILLSTYLEARRAY fill_styles;
		LINESTYLEARRAY line_styles;
		UI8 num_fill_bits;
		UI8 num_line_bits;
		vector<float> vertices;
	};
	
	istream &operator>>(istream &input, SHAPEWITHSTYLE &shape) {
		// cout << "---- parse shape with style ----" << endl;
		input >> shape.fill_styles;
		input >> shape.line_styles;
		BitReader<UI8> reader(input);
		reader.read(shape.num_fill_bits, 4);
		reader.read(shape.num_line_bits, 4);
		
		bool shape_end = false;
		vector<float> vertices;
		SI32 pos_x = 0, pos_y = 0;
		do {
			UI16 front = reader.peek<UI16>(16); 
			//cout << to_bin(front, reader.offset()) << " : ";
			
			bool type_flag;
			reader.read(type_flag, 1);
			
			if (!type_flag) {
				// non edge record
				if (reader.peek<UI8>(5) == 0) {
					// end of shape;
					//cout << "ENDSHAPE" << endl;
					reader.skip(5);
					shape_end = true;
				} else {
					//cout << "CHANGESTYLE" << endl;
					bool state_new_styles, state_line_style, state_fill_style_1, state_fill_style_0, state_moveto;
					reader.read(state_new_styles);
					reader.read(state_line_style);
					reader.read(state_fill_style_1);
					reader.read(state_fill_style_0);
					reader.read(state_moveto);
					
					if (state_moveto) {
						UI8 move_bits;
						reader.read(move_bits, 5);
						SI32 move_x, move_y;
						reader.read_signed(move_x, move_bits);
						reader.read_signed(move_y, move_bits);
						pos_x += move_x;
						pos_y += move_y;
						vertices.push_back(pos_x);
						vertices.push_back(pos_y);
					}
					
					if (state_fill_style_0) {
						reader.skip(shape.num_fill_bits);
					}
					
					if (state_fill_style_1) {
						reader.skip(shape.num_fill_bits);
					}
					
					if (state_line_style) {
						reader.skip(shape.num_line_bits);
					}
					
					if (false && state_new_styles) { // not used by define shape 4
						FILLSTYLEARRAY a;
						input >> a;
						LINESTYLEARRAY b;
						input >> b;
						UI8 c;
						READ(input, c);
					}
				}
			} else {
				bool straight_flag = reader.read<UI8>(1);
				UI8 num_bits = reader.read<UI8>(4);
				
				if (straight_flag) {
					//cout << "STRAIGHT EDGE" << endl;
					SI32 delta_x = 0, delta_y = 0;
					bool general_line_flag;
					reader.read(general_line_flag, 1);
					if (general_line_flag) {
						reader.read_signed(delta_x, num_bits+2);
						reader.read_signed(delta_y, num_bits+2);
					} else {
						bool vertical = reader.read<UI8>(1);
						reader.read_signed(vertical ? delta_y : delta_x, num_bits+2);
					}
					pos_x += delta_x;
					pos_y += delta_y;
					vertices.push_back(pos_x);
					vertices.push_back(pos_y);
				} else {
					//cout << "CURVED EDGE" << endl;
					assert(false);
				}
				
			}
		} while (!shape_end);
	
		shape.vertices = vertices;
		
		return input;
	}
}

#endif
