//
//  swf.h
//  swf
//
//  Created by Simon Harvey on 12-03-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SWFParser_swf_h
#define SWFParser_swf_h

#include <iostream>
#include <fstream>
#include <istream>
#include <map>
#include <OpenGLES/ES1/gl.h>

#include "types.h"
#include "shape.h"


namespace swf
{
	class SWF;
	
	using namespace std;
	
	typedef void (*parse_tag_fun)(istream &, SWF &swf);
	static void (*tag_parser[91])(istream &, SWF &swf) = { 0 };
	
	template <class T>
	static void read(istream &stream, T &target) {
		stream.read((char *)&target, sizeof(T));
	}
	
	static void register_parser(tag_id tag, parse_tag_fun f) {
		tag_parser[tag] = f;
	}
	
	class SWF
	{
	public:
		UI8 version;
		map<UI16, vector<float>> dictionary;
		float frame_rate;
		RECT frame_size;
		UI16 frame_count;
		UI16 cur_frame;
	private:
		istream * m_input;
	public:
		
		//SWF(istream &_input) : input(_input.rdbuf()) {
		SWF(istream *input) : m_input(input), cur_frame(0) {
			read_header();
		}
		
		void process_frame() {
			istream &input = *m_input;
			streampos frame_start = input.tellg();
			cur_frame++;
			cout << "- start frame:" << cur_frame << " ------" << endl;
			
			RECORDHEADER header;
			do {
				input >> header;
				parse_tag_fun &p = tag_parser[(tag_id)header.tag];
				if (!p) {
					cout << "TAG [" << int(header.tag) << "] NOT IMPLEMENTED" << endl;
					input.seekg((streamsize)input.tellg()+header.length);
				} else {
					streampos start_pos = input.tellg();
					p(input, *this);
					// check that the parser consumed all the required data
					int cur_pos = input.tellg();
					streamsize read = cur_pos-start_pos;
					if (read != header.length) {
						cout << "TAG [" << header.tag << "] BYTES UNREAD:" << (header.length-read) << endl;
						input.seekg(start_pos+(streampos)header.length);
					}
				}
			} while (header.tag && header.tag != ShowFrame);
			
			if (cur_frame >= frame_count) { // stop at last frame
				input.seekg(frame_start);
				cur_frame--;
			}
		}
		
		void read_header() {
			istream &input = *m_input;
			UI8 sig[4] = {0};
			UI32 file_length = 0;
			UI16 frame_rate = 0;
			READ_SIZE(input, sig, 3);
			assert(sig[0] == 'F');
			READ(input,	version);
			READ(input, file_length);
			input >> frame_size;
			READ(input, frame_rate);
			this->frame_rate = to_fixed(frame_rate);
			READ(input, frame_count);
		}
	};
	
	// tags
	
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
		bool uses_fill_winding_rule, uses_non_scaling_strokes, uses_scaling_strokes;
		
		READ(s, shape_id);
		s >> shape_bounds;
		s >> edge_bounds;
		BitReader<UI8> reader(s);
		reader.skip(5); // reserved
		reader.read(uses_fill_winding_rule, 1);
		reader.read(uses_non_scaling_strokes, 1);
		reader.read(uses_scaling_strokes, 1);
		
		//do {
			SHAPEWITHSTYLE shape;
			s >> shape;
		//} while(false);
		
		swf.dictionary[shape_id] = shape.vertices;
	}
	
	void place_object_2(istream &s, SWF &swf) {
		bool flag_actions, flag_depth, flag_name, flag_ratio, flag_colortransform, flag_matrix, flag_character, flag_move;
		BitReader<UI8> reader(s);
		reader.read(flag_actions);
		assert(!flag_actions); // clip actions are not supported, yet
		reader.read(flag_depth);
		reader.read(flag_name);
		reader.read(flag_ratio);
		reader.read(flag_colortransform);
		reader.read(flag_matrix);
		reader.read(flag_character);
		reader.read(flag_move);
		
		UI16 depth;
		READ(s, depth);
		UI16 character_id = 0;
		if (flag_character)
			READ(s, character_id);
		MATRIX mat = {0};
		if (flag_matrix) {
			s >> mat;
		}
		if (flag_colortransform) {
			// todo;
		}
		if (flag_ratio)
			SKIP(s, sizeof(UI16));
		
		/*GLfloat p[] = {
			(GLfloat)mat.translate_x, (GLfloat)mat.translate_y
		};*/
		
		glPushMatrix();
		glTranslatef((GLfloat)mat.translate_x, (GLfloat)mat.translate_y, 0);
		vector<float> verts = swf.dictionary[1];
		cout << "num verts: " << verts.size()/2 << endl;
		for ( auto it = verts.begin(); it != verts.end(); ) {
			cout << "(" << *(++it) << ", " << *(++it) << "), ";
		}
		cout << endl;
		glVertexPointer(2, GL_FLOAT, 0, &verts[0]);
		glColor4f(1, 0, 0, 1);
		glPointSize(10.0f);
		//glLineWidth(4.0f);
		glDrawArrays(GL_LINE_STRIP, 0, verts.size()/2);
		glPopMatrix();
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
	
	void show_frame(istream &s, SWF &swf) { }
	
	static void init_tag_parsers() {
		//register_parser(DefineShape, &define_shape);
		register_parser(ShowFrame, &show_frame);
		register_parser(DefineShape4, &define_shape_4);
		register_parser(PlaceObject2, &place_object_2);
	}
}

#endif
