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
#include <map>

using namespace std;

namespace swf
{
	struct SWF;
	
	typedef void (*parse_tag_fun)(istream &, SWF &swf);
	static void (*tag_parser[91])(istream &, SWF &swf) = { 0 };
	
	template <class T>
	static void read(istream &stream, T &target) {
		stream.read((char *)&target, sizeof(T));
	}
	
	static void register_parser(tag_id tag, parse_tag_fun f) {
		tag_parser[tag] = f;
	}
	
	struct SWF
	{
		UI8 version;
		map<UI16, void *> dictionary;
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
		
		assert(sig[0] == 'F'); // compressed swf not supported yet
		
		f >> frame_size;
		cout << frame_size;
		READ(frame_rate);
		READ(frame_count);
		cout << "FRAME RATE:" << frame_rate << endl << "FRAME COUNT:" << frame_count << endl;
		
		while (f.good()) {
			
			RECORDHEADER header;
			f >> header;
			
			parse_tag_fun &p = tag_parser[(tag_id)header.tag];
			if (!p) {
				cout << "TAG NOT IMPLEMENTED:" << int(header.tag) << endl;
				streamsize off = skip_size(header);
				f.seekg((streamsize)f.tellg()+off);
				//f.ignore(off); // this shitty function doesn't work, I wonder why.
			} else {
				streampos start_pos = f.tellg();
				p(f, result);
				// check that the parser consumed all the required data
				streampos len = skip_size(header);
				streampos read = f.tellg()-start_pos;
				if (read != len) {
					cout << "TAG BYTES UNREAD:" << (len-read) << " [" << header.tag << "]" << endl;
					f.seekg(start_pos+len-read);
				}
			}
		}
	}
	
	// tags
	
	void end(istream &s, SWF &swf) {
		cout << "end" << endl;
	}
	
	void show_frame(istream &s, SWF &swf) {
		cout << "show frame" << endl;
	}
	
	void define_shape(istream &s, SWF &swf) {
		cout << "DEFINE SHAPE" << endl;
		UI16 shape_id;
		RECT shape_bounds;
		read(s, shape_id);
		s >> shape_bounds;
	}
	
	void define_shape_4(istream &s, SWF &swf) {
		UI16 shape_id;
		RECT shape_bounds;
		RECT edge_bounds;
		UI8 reserved, uses_fill_winding_rule, uses_non_scaling_strokes, uses_scaling_strokes;
	}
	
	void file_attributes(istream &s, SWF &swf) {
		BitReader<UI8> reader(s);
		UI8 reserved, use_direct_blit, use_gpu, has_metadata, as3, use_network;
		reader.read(reserved, 1);
		reader.read(use_direct_blit, 1);
		reader.read(use_gpu, 1);
		reader.read(has_metadata, 1);
		reader.read(as3, 1);
		reader.read(reserved, 2);
		reader.read(use_network, 1);
		reader.read(reserved, 24);
	}
	
	static void init_tag_parsers() {
		register_parser(End, &end);
		register_parser(ShowFrame, &show_frame);
		//register_parser(DefineShape, &define_shape);
		register_parser(DefineShape4, &define_shape_4);
	}
}