//
//  swf.h
//  swf
//
//  Created by Simon Harvey on 12-03-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <istream>
#include "types.h"

using namespace std;

namespace swf
{
	//typedef void *(parse_tag_fun)(istream &);
	
	//static parse_tag_fun tag_parser[91];
	
	struct SWF
	{
		
	};

	void parse(istream &f, SWF &result) 
	{

#define READ_S(t, s) \
	f.read((char *)&t, s)

#define READ(t) \
	f.read((char *)&t, sizeof(t))
		UI8 sig[4] = {0};
		UI8 version;
		UI32 file_length;
		RECT frame_size;
		UI16 frame_rate, frame_count;
		READ_S(sig, 3);
		cout << "SIGNATURE:" << sig << endl;
		f.read((char *)&version, 1);
		cout << "VERSION:" << int(version) << endl;
		READ(file_length);
		cout << "FILE LENGTH:" << file_length << endl;
		f >> frame_size;
		cout << frame_size;
		READ(frame_rate);
		READ(frame_count);
		cout << "FRAME RATE:" << frame_rate << endl << "FRAME COUNT" << frame_count << endl;
	}
}