//
//  shape.h
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SWFParser_shape_h
#define SWFParser_shape_h

#include "swf.h"

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
	
	struct FILLSTYLE_GRADIENT : FILLSTYLE
	{
		
	};
	
	struct FILLSTYLEARRAY
	{
		UI8 fill_style_count;
		UI16 fill_style_extended;
		FILLSTYLE *fill_styles;
	};
	
	struct LINESTYLEARRAY
	{
		
	};
	
	struct SHAPERECORD
	{
		
	};
	
	struct SHAPEWITHSTYLE 
	{
		
	};
	
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
