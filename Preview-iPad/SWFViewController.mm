//
//  SWFViewController.m
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SWFViewController.h"
#include "swf.h"

@implementation SWFViewController

@synthesize swfPath = _swfPath;

-(void)viewDidLoad {
	[super viewDidLoad];
	EAGLContext *ctx = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
	GLKView *glv = (GLKView *)self.view;
	glv.context = ctx;
	NSLog(@"view did load");
}

-(void)update {
	glClearColor(.2, .2, .2, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

-(void)setSwfPath:(NSString *)swfPath {
	NSLog(@"set swf path:%@", swfPath);
	_swfPath = swfPath;
	
	swf::SWF SWF;
	ifstream input;
	input.open([swfPath UTF8String]);
	swf::init_tag_parsers();
	swf::parse(input, SWF);
}

@end
