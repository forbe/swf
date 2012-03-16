//
//  types.h
//  SWFParser
//
//  Created by Simon Harvey on 12-03-14.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef SWFParser_types_h
#define SWFParser_types_h

#include "read_bits.cpp"

namespace swf 
{
	typedef char	SI8;
	typedef short	SI16;
	typedef int		SI32;
	typedef unsigned char	UI8;
	typedef unsigned short	UI16;
	typedef unsigned int	UI32;
	
	struct RECT 
	{
		unsigned char nbits;
		int x_min, x_max, y_min, y_max;
	};
	
	std::istream &operator>>(std::istream &st, RECT &rect) {
		BitReader<UI8> r(st);
		r.read(rect.nbits, 5);
		r.read(rect.x_min, rect.nbits);
		r.read(rect.x_max, rect.nbits);
		r.read(rect.y_min, rect.nbits);
		r.read(rect.y_max, rect.nbits);
		return st;
	}
	
	std::ostream &operator<<(std::ostream &st, const RECT &rect) {
		st << int(rect.nbits) << endl;
		return st;
	}
	
	enum tag_id
	{
		End = 0 ,
		ShowFrame = 1 ,
		DefineShape = 2 ,
		PlaceObject = 4 ,
		RemoveObject = 5 ,
		DefineBits = 6 ,
		DefineButton = 7 ,
		JPEGTables = 8 ,
		SetBackgroundColor = 9 ,
		DefineFont = 10 ,
		DefineText = 11 ,
		DoAction = 12 ,
		DefineFontInfo = 13 ,
		DefineSound = 14 ,
		StartSound = 15 ,
		DefineButtonSound = 17 ,
		SoundStreamHead = 18 ,
		SoundStreamBlock = 19 ,
		DefineBitsLossless = 20 ,
		DefineBitsJPEG2 = 21 ,
		DefineShape2 = 22 ,
		DefineButtonCxform = 23 ,
		Protect = 24 ,
		PlaceObject2 = 26 ,
		RemoveObject2 = 28 ,
		DefineShape3 = 32 ,
		DefineText2 = 33 ,
		DefineButton2 = 34 ,
		DefineBitsJPEG3 = 35 ,
		DefineBitsLossless2 = 36 ,
		DefineEditText = 37 ,
		DefineSprite = 39 ,
		FrameLabel = 43 ,
		SoundStreamHead2 = 45 ,
		DefineMorphShape = 46 ,
		DefineFont2 = 48 ,
		ExportAssets = 56 ,
		ImportAssets = 57 ,
		EnableDebugger = 58 ,
		DoInitAction = 59 ,
		DefineVideoStream = 60 ,
		VideoFrame = 61 ,
		DefineFontInfo2 = 62 ,
		EnableDebugger2 = 64 ,
		ScriptLimits = 65 ,
		SetTabIndex = 66 ,
		FileAttributes = 69 ,
		PlaceObject3 = 70 ,
		ImportAssets2 = 71 ,
		DefineFontAlignZones = 73 ,
		CSMTextSettings = 74 ,
		DefineFont3 = 75 ,
		SymbolClass = 76 ,
		Metadata = 77 ,
		DefineScalingGrid = 78 ,
		DoABC = 82 ,
		DefineShape4 = 83 ,
		DefineMorphShape2 = 84 ,
		DefineSceneAndFrameLabelData = 86 ,
		DefineBinaryData = 87 ,
		DefineFontName = 88 ,
		StartSound2 = 89 ,
		DefineBitsJPEG4 = 90 ,
		DefineFont4 = 91 ,
	};
}

#endif