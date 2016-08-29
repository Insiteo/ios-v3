//
//  SDKInitTableViewController.h
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, InitMode) {
    InitModeAllInOne = 0,
    InitModeStepByStep,
};

@interface SDKInitTableViewController : UITableViewController

@property (nonatomic, assign, readwrite) InitMode exampleInitMode;

@end
