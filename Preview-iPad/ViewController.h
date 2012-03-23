//
//  ViewController.h
//  Preview-iPad
//
//  Created by Simon Harvey on 12-03-23.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DocumentsTableViewController.h"

@interface ViewController : UISplitViewController <UITableViewDelegate>

@property (strong, nonatomic) DocumentsTableViewController *documentsView;
@property (strong, nonatomic) SWFViewController *swfView;

@end
