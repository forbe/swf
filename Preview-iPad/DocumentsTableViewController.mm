//
//  DocumentsTableView.m
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "DocumentsTableViewController.h"

@implementation DocumentsTableViewController

#define DOCUMENT_PATH [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]

@synthesize files;
@synthesize detail;

-(void)viewDidLoad {
	[super viewDidLoad];
	NSError *error;
	self.files = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:DOCUMENT_PATH error:&error];
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return [self.files count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
	if (cell == nil) {
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
	}
	cell.textLabel.text = [self.files objectAtIndex:indexPath.row];
	return cell;
}

//

-(NSString *)pathForDocumentAt:(NSIndexPath *)path {
	NSString *s = [NSString stringWithFormat:@"%@/%@", DOCUMENT_PATH, [self.files objectAtIndex:path.row]];
	return s;
}

@end
