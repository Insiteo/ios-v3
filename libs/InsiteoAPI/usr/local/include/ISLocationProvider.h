//
//  LocationProvider.h
//  LocationAPI
//
//  Created by INSITEO on 04/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISLocationProvider.hpp
 ISLocationProvider
 */

#import <Foundation/Foundation.h>

/*!
 1
 */
extern int const GPS;

/*!
 2
 */
extern int const WIFI;

/*!
 4
 */
extern int const BLE;

/*!
 8
 */
extern int const COMPASS;

/*!
 16
 */
extern int const MOTION_FILTERING;

/*!
 32
 */
extern int const MEMS;

/*!
 2000
 */
extern int const DEFAULT_SCAN_FREQUENCY;

#define NAVIGATION_FLAGS (GPS|BLE|COMPASS|MEMS)
#define BACKGROUND_FLAGS (BLE|MOTION_FILTERING)

#import "ISPLocationListener.h"
#import "ISPLbsModule.h"
#import "ISLocationRequest.h"

@class ISLocationRenderer;

/*!
 Class used to provide and get user locations.
 @warning When using this class, you will need to tag your implementor as C++ class (*.mm extension OR specific compiler settings).
 */
@interface ISLocationProvider : NSObject

/*!
 Last computed location.
 */
@property (nonatomic, retain) ISLocation * lastLocation;

/*!
 Location listener.
 */
@property (nonatomic, assign) id<ISPLocationListener> locationListener;

/*!
 Boolean used to know if the location provider is started.
 */
@property (nonatomic, readonly) Boolean isStarted;

/*!
 Location services list.
 */
@property (nonatomic, retain) NSMutableDictionary * locationServices;

/*!
 Last location session identifier (-1 if failed, 0 if fake, >0 otherwise).
 */
@property (nonatomic, readwrite) int sessionId;

/*!
 Current location flags
 */
@property (nonatomic, readonly) int locationFlags;

/*
 Boolean used to know if the location was too degrade to be considered.
 */
@property (nonatomic, readwrite) Boolean locationLost;

/*!
 Location Renderer.
 */
@property (nonatomic, retain) ISLocationRenderer * renderer;

/*!
 Static method used to know the current location package version.
 @return Current location package version.
 */
+ (int)getLocationPackageVersion;

/*!
 Static method used to know the current location library version.
 @return Current location library version.
 */
+ (NSString *)getLocationCodeVersion;

/*!
 Static method used to get the ISLocationProvider shared instance.
 @return The ISLocationProvider shared instance.
 */
+ (ISLocationProvider *)sharedInstance;

/*!
 Method used to get a lbs module with a specifi type.
 @param lbsModuleType Lbs module type.
 */
- (id<ISPLbsModule>)getLbsModule:(LbsModuleType)lbsModuleType;

/*!
 Method used to start the location with specific configuration.
 @param locationFlags Location flags.
 @param locationListener Location events listener.
 @param scanFrequency Location scan frequency.
 @param defaultMapId Default map identifier to use
 @param forceDefaultMap Boolean used to know if we force the default map.
 @param locationPath The location package directory.
 @param uuidService UUID service to scan for (could be nil).
 */
- (Boolean)startLocation:(int)locationFlags andLocationListener:(id<ISPLocationListener>)locationListener andScanFrequency:(int)scanFrequency andDefaultMapId:(int)defaultMapId andForceDefaultMap:(Boolean)forceDefaultMap andLocationPath:(NSString *)locationPath andUUIDService:(NSString *)uuidService;

/*!
 Method used to start the location with specific configuration.
 @param locationFlags Location flags.
 @param locationListener Location events listener.
 @param scanFrequency Location scan frequency.
 @param defaultMapId Default map identifier to use
 @param forceDefaultMap Boolean used to know if we force the default map.
 */
- (Boolean)startLocation:(int)locationFlags andLocationListener:(id<ISPLocationListener>)locationListener andScanFrequency:(int)scanFrequency andDefaultMapId:(int)defaultMapId andForceDefaultMap:(Boolean)forceDefaultMap;

/*!
 Method used to start the location with specific configuration.
 @param locationFlags Location flags.
 @param locationListener Location events listener.
 @param scanFrequency Location scan frequency.
 */
- (Boolean)startLocation:(int)locationFlags andLocationListener:(id<ISPLocationListener>)locationListener andScanFrequency:(int)scanFrequency;

/*!
 Method used to start the location with specific configuration.
 @param locationFlags Location flags.
 @param locationListener Location events listener.
 */
- (Boolean)startLocation:(int)locationFlags andLocationListener:(id<ISPLocationListener>)locationListener;

/*!
 Method used to stop the location.
 */
- (void)stopLocation;

/*!
 Method used to change the location flags.
 @param flags New location flags.
 */
- (void)changeLocationWithFlags:(int)flags;

/*!
 Method called to get a one shot location (After a timeout of 10 seconds with no computed location, fail callback is called).
 @param locationRequestListener Listener to notify when a location is computed.
 @param locationFlags Location flags to used.
 @return The related location request to identify callers.
 */
- (ISLocationRequest *)requestUniqueLocationWithLocationRequestListener:(id<ISPLocationRequestListener>)locationRequestListener andLocationFlags:(int)locationFlags;

/*!
 Method used to delete the location logs directory.
 @result <b>YES</b> if the directory was successfuly deleted, otherwise <b>NO</b>.
 @warning The ISLocationProvider needs to be stopped before calling this method.
 */
- (Boolean)deleteLogs;

/*
 Intern method used to update azimuth information.
 @param azimuth Azimuth to use.
 */
- (void)onAzimuthReceived:(float)azimuth;

@end
