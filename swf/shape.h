//
//  shape.h
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SWFParser_shape_h
#define SWFParser_shape_h

#include "types.h"
#include <vector>

using namespace std;

namespace swf 
{
	struct Shape
	{
		
	};
	
	
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
	};
	
	/*struct FILLSTYLE_GRADIENT : FILLSTYLE
	{
		
	};*/
	
	/*struct FILLSTYLEARRAY
	{
		UI16 fill_style_count;
		vector<FILLSTYLE> fill_styles;
	};*/
	
	typedef vector<FILLSTYLE> FILLSTYLEARRAY;
	
	istream &operator>>(istream &input, FILLSTYLEARRAY &array) {
		UI16 num_styles = 0;
		READ_TYPE(input, num_styles, UI8);
		if (num_styles == 0xFF)
			READ_TYPE(input, num_styles, UI16);
		array.reserve(num_styles);
		for (int i=0; i<num_styles; ++i) {
			FILLSTYLE style;
			//input >> style;
			array.push_back(style);
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
	
	istream &operator>>(istream &st, SHAPEWITHSTYLE &sh) 
	{
		
	}
}

#endif
