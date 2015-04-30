//
//  BeaconRegionDetailTableViewController.h
//  InsiteoSDKDemo
//
//  Created by Lionel on 08/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <InsiteoSDK/ISBeaconProvider.h>

@interface BeaconRegionDetailTableViewController : UITableViewController <ISBeaconDelegate>

- (id)initWithBeaconRegion:(ISBeaconRegion *)beaconRegion andIsEntered:(BOOL)entered;

@end
