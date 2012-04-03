//
//  utils.h
//  SWFParser
//
//  Created by Simon Harvey on 12-04-01.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SWFParser_utils_h
#define SWFParser_utils_h

#include <string>
#include <istream>

#define RAD_TO_DEG(x) x * 180 / 3.141592654

template <class T>
string to_bin(T value, streampos p = 0)
{
	p = (int)p % 4;
	int length = sizeof(T) * 8;
	int num_spaces = (length+p)/4;
	char result[length+num_spaces];
	result[length] = 0;
	int b = length;//+num_spaces;
	char *c = &result[length+num_spaces-1];
	while (b>=0)
	{
		*(c--) = value & 1 ? '1' : '0';
		value >>= 1;
		--b;
		if (!(b%4))
			*(c--) = ' ';
	}
	return result;
}

#endif
