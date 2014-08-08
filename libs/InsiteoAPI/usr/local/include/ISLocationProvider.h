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

//DLL Listener
#import "IEmbeddedLocationListener.h"

@class CompassProvider;
@class WifiProvider;
@class GpsProvider;
@class MotionProvider;
@class BleProvider;
@class ISEmbeddedLocationProvider;
@class BeaconProvider;
@class InitInformation;
@class ISLocationRenderer;

class ISEmbeddedLocationListener:IEmbeddedLocationListener {
    
public:
    void * mLocationProvider;
    
    ISEmbeddedLocationListener(void * locationProvider);
	~ISEmbeddedLocationListener();
    
    void onLocation(InternalLocation * aLocation);
    void zoneOUT(InternalLocation * aLocation);
    void onGpsStatusChange(bool aEnable);
    void onUserOnSite(bool aUserOnSite);
    void onAPMissingV2(InternalLocation * location, char * orderIDs, char * counts, char * orderIDsseens, int techno);
};

/*!
 Class used to provide and get user locations.
 @warning When using this class, you will need to tag your implementor as C++ class (*.mm extension OR specific compiler settings).
 */
@interface ISLocationProvider : NSObject {
    
@protected
    
#pragma mark - Structure
    
    //Last computed location
    ISLocation * m_lastLocation;
    //Current GPS location
	CLLocation * m_gpsLocation;
    //Array containing current access points measures
	NSMutableArray * m_wifiAps;
    //Array containing current bluetooth visible peripherals
    NSMutableArray * m_bluetoothAps;
    
#pragma mark - Embedded Location Provider
    
    //DLL wrapper provider
    ISEmbeddedLocationProvider * m_embeddedLocationProvider;
    //DLL listener
    ISEmbeddedLocationListener * m_embeddedLocationListener;
    
#pragma mark - Sensor Providers
    
    //Compass provider
    CompassProvider * m_compassProvider;
    //GPS location provider
	GpsProvider * m_gpsLocationProvider;
	//Wifi location provider
	WifiProvider * m_wifiLocationProvider;
    //Bluetooth provider
    BleProvider * m_bluetoothProvider;
    BeaconProvider * m_beaconProvider;
    //Accelerometer provider
    MotionProvider * m_motionProvider;
	
    //Location listener
    id<ISPLocationListener> m_locationListener;
	//Location services list
	NSMutableDictionary * m_locationServices;
    
#pragma mark - Internal
    
    //Location flags (used to activate sensors)
    int m_locationFlags;
    //Default map identifier to use
    int m_defaultMapId;
    //Boolean used to know if we force the default map for results
    Boolean m_forceDefaultMap;
    //Location bluetooth scan frequency
    int m_scanFrequency;
    //Location path
    NSString * m_locationPath;
    
    //Internal Boolean used to know if a FakeLocation is available
    Boolean m_isFakeLoc;
    //Boolean used to know if the location provider is started
    Boolean m_isStarted;
    //Boolean used to know if the location was started manually (not unique)
    Boolean m_isManuallyStarted;
    //Session id reference
    int m_sessionId;
    //Boolean used to know if we can push a location to the server
    volatile Boolean m_canPushLocation;
    //Boolean used to know if the location was too degrade to be considered.
    Boolean m_locationLost;
    
    //Intern mutex
    NSLock * m_lock;
    //Internal date used to store and compare the last API initialization date
    NSDate * m_lastInitDate;
    
#pragma mark - ISLocationRequest
    
    //An array of ISLocationRequest (intern)
    NSMutableArray * m_locationRequests;
    
#pragma mark - Render
    
    //Location renderer
    ISLocationRenderer * m_locationRenderer;
}

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
 */
- (Boolean)startLocation:(int)locationFlags andLocationListener:(id<ISPLocationListener>)locationListener andScanFrequency:(int)scanFrequency andDefaultMapId:(int)defaultMapId andForceDefaultMap:(Boolean)forceDefaultMap andLocationPath:(NSString *)locationPath;

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

#pragma mark - Fingerprint quality

/*
 Internal method used to get a fingerprint quality.
 @return Return an array for each fingerprint point with its quality.
 */
- (NSArray *)getFingerprintQuality;

/*!
 Intern method used to update azimuth information.
 @param azimuth Azimuth to use.
 */
- (void)onAzimuthReceived:(float)azimuth;

@end
