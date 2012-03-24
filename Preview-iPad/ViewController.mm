//
//  ViewController.m
//  Preview-iPad
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize documentsView, swfView;

-(void)viewDidLoad {
	[super viewDidLoad];
	self.documentsView = (DocumentsTableViewController *)[[self.viewControllers objectAtIndex:0] topViewController];
	self.documentsView.tableView.delegate = self;
	self.swfView = (SWFViewController *)[self.viewControllers objectAtIndex:1];
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	self.swfView.swfPath = [self.documentsView pathForDocumentAt:indexPath]; 
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	return YES;
}

@end
