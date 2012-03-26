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
			reader.skip(sizeof(UI16));
		if (!has_fill_flag) {
			input >> style.color;
		} else {
			assert(false); // fill stroke not supported
		}
		
		return input;
	}
	
	struct LINESTYLEARRAY
	{
		
	};
	
	istream &operator>>(istream &input, LINESTYLEARRAY array) {
		return input;
	}
	
	struct SHAPERECORD
	{
		
	};
	
	struct SHAPEWITHSTYLE 
	{
		FILLSTYLEARRAY fill_styles;
		LINESTYLEARRAY line_styles;
		UI8 num_fill_bits;
		UI8 num_line_bits;
	};
	
	istream &operator>>(istream &input, SHAPEWITHSTYLE &shape) {
		input >> shape.fill_styles;
		input >> shape.line_styles;
		BitReader<UI8> reader(input);
		reader.read(shape.num_fill_bits, 4);
		reader.read(shape.num_line_bits, 4);
		
		do {
			//BitReader<UI8> reader(input);
			
		} while (false);
		
		return input;
	}
	
	// shape records
	
	struct ENDSHAPERECORD
	{
		
	};
	
	struct STYLECHANGERECORD
	{
		
	};
	
	struct STRAIGHTEDGERECORD
	{
		
	};
	
	struct CURVEDEDGERECORD
	{
		
	};
}

#endif
