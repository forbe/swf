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
	EAGLContext *ctx = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	GLKView *glv = (GLKView *)self.view;
	glv.context = ctx;
	NSLog(@"view did load");
	m_swf = NULL;
}

-(void)update {
	
	CGRect frame = self.view.frame;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, frame.size.width, 0, frame.size.height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	
	glClearColor(.2, .2, .2, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (m_swf) 
	{
		glPushMatrix();
		glColor4f(1, 1, 1, 1);
		swf::RECT &f = m_swf->frame_size;
		glTranslatef(frame.size.width/2, frame.size.height/2, 0);
		glScalef(.05f, .05f, 1);
		glTranslatef(-(f.x_max-f.x_min)/2, -(f.y_max-f.y_min)/2, 0);
		float stage[] = {
			(float)f.x_min, (float)f.y_min,
			(float)f.x_min, (float)f.y_max,
			(float)f.x_max, (float)f.y_max,
			(float)f.x_max, (float)f.y_min,
		};
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, &stage[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glPopMatrix();
	}
}

-(void)setSwfPath:(NSString *)swfPath {
	NSLog(@"set swf path:%@", swfPath);
	_swfPath = swfPath;
	
	if (m_swf) delete m_swf;
	m_swf = new swf::SWF();
	
	ifstream input;
	input.open([swfPath UTF8String]);
	swf::init_tag_parsers();
	swf::parse(input, *m_swf);
}

@end