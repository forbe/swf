//
//  DocumentsTableView.h
//  SWFParser
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SWFViewController.h"

@interface DocumentsTableViewController : UITableViewController <UITableViewDataSource>

@property (strong, nonatomic) IBOutlet SWFViewController *detail;
@property (strong, nonatomic) NSArray *files;

-(NSString *)pathForDocumentAt:(NSIndexPath *)path;

@end
