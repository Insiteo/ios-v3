//
//  ISPMotionListener.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 19/10/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPMotionListener.h
 ISPMotionListener
 */

#import <Foundation/Foundation.h>
#import <CoreMotion/CoreMotion.h>

/*!
 Protocol used to handle accelerometer events.
 */
@protocol ISPMotionListener <NSObject>

/*!
 Method called when a new motion result is available.
 @param motion New motion available.
 */
- (void)onMotionAvailable:(int)motion;

@end
