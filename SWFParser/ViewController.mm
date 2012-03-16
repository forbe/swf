//
//  ViewController.m
//  SWFParser
//
//  Created by Simon Harvey on 12-03-11.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#include "swf.h"
#include <istream>

@interface ViewController ()

@end

@implementation ViewController

-(void)viewDidLoad {
	[super viewDidLoad];
	using namespace swf;
	using namespace std;
	SWF s;
	
	if (CFByteOrderBigEndian == CFByteOrderGetCurrent()) {
		cout << "big endian" << endl;
	} else {
		cout << "little endian" << endl;
	}
	
	const char *swf_path = [[[NSBundle mainBundle] pathForResource:@"ball" ofType:@"swf"] UTF8String];
	ifstream input;
	input.open(swf_path);
	swf::parse(input, s);
}

@end
