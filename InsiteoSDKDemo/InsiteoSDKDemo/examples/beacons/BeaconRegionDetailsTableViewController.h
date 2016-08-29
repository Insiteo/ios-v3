//
//  BeaconRegionDetailTableViewController.h
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-present Insiteo. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <InsiteoSDK/ISBeaconProvider.h>

@interface BeaconRegionDetailsTableViewController : UITableViewController <ISBeaconDelegate>

// Pass the region and a boolean value to indicate that region is entered
- (void)setRegion:(ISBeaconRegion *)region isAlreadyEntered:(BOOL)alreadyEntered;

@end
