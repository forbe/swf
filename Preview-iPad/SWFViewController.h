//
//  SWFViewController.h
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <GLKit/GLKit.h>z

namespace swf {
	struct SWF;
}

@interface SWFViewController : GLKViewController {
	NSString *_swfPath;
	swf::SWF *m_swf;
}

@property (strong, nonatomic) NSString * swfPath;

@end
