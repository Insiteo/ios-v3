//
//  ISPLocationListener.h
//  LocationAPI
//
//  Created by INSITEO on 06/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPLocationListener.h
 ISPLocationListener
 */

#import <UIKit/UIKit.h>

#import "ISInsiteoError.h"
#import "ISLocation.h"

/*!
 Protocol used to handle Location events.
 */
@protocol ISPLocationListener <NSObject>

/*!
 Method called when the location init is done.
 @param success Boolean used to know if the initialization succeeded or not.
 @param error Relative fail error. Could be nil if success.
 */
- (void)onLocationInitDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error;

/*!
 Method called when a new location is received.
 @param location New location received.
 */
- (void)onLocationReceived:(ISLocation *)location;

/*!
 Method called when a new azimuth is received.
 @param azimuth Updated azimuth.
 */
- (void)onAzimuthReceived:(float)azimuth;

@optional

/*!
 Method called when no registered beacon were detected.
 */
- (void)noRegisteredBeaconDetected;

/*!
 Method called when the location computed is lost.
 @param lastPosition The last known position.
 */
- (void)onLocationLost:(ISPosition *)lastPosition;

@end
