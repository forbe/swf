//
//  read_bits.cpp
//  SWFParser
//
//  Created by Simon Harvey on 12-03-14.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

using namespace std;

template <class T>
class BitReader
{
	istream &input;
	T cur;
	const size_t type_size;
	size_t off;
	
public:
	BitReader(istream &input) : input(input), type_size(sizeof(T)*8), off(0) {
		off = type_size;
	}
	template <class U>
	void read(U &dest, size_t length) {
		dest = 0;
		char * dest_p = (char *)&dest;
		int left = length;
		while (left > 0) {
			
			if (off >= type_size) {
				off = 0;
				input.read((char *)&cur, sizeof(T));
			}
			
			size_t left_in_cur = type_size - off;
			size_t to_read = left_in_cur < left ? left_in_cur : left;
			
			dest <<= to_read;
			
			T val = cur;
			// discard right of zone
			T too_much = type_size-(off+to_read);
			val >>= too_much;
			T mask = (1 << to_read)-1;
			val &= mask;
			dest |= val;
			//memcpy(dest_p, &val, sizeof(U));
			
			off += to_read;
			left -= to_read;
			//dest_p += to_read;
			//cur <<= to_read;
		}
	}
	
	void skip(int length) {
		
	}
};