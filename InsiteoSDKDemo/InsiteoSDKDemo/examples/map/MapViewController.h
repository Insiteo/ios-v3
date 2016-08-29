//
//  MapViewController.h
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, MapMode) {
    MapModeRTO = 0,
    MapModeLoc,
    MapModeGeofence,
    MapModeItinerary,
};

@interface MapViewController : UIViewController

@property (nonatomic, assign, readwrite) MapMode exampleMapMode;

@end
