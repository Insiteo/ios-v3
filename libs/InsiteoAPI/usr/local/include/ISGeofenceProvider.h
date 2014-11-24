//
//  ISGeofenceProvider.h
//  LocationAPI
//
//  Created by INSITEO on 14/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISGeofenceProvider.h
 ISGeofenceProvider
 */

#import <Foundation/Foundation.h>

extern Boolean const IS_GEO_PUSH_DEFAULT_EVENT_ENABLED;     //YES
extern float const IS_GEO_PUSH_DEFAULT_EVENT_TIME;          //3.0
extern float const IS_GEO_PUSH_DEFAULT_CUSTOM_GEO_WIDTH;    //2.0

@class ISGeofenceArea;
@class ISGeofenceAreaRenderer;

#import "ISPLbsModule.h"
#import "ISPGeofenceListener.h"
#import "ISMapSettings.h"
#import "ISZonePoi.h"

/*!
 This class handles the geofencing process. You can retrieve an instance of it by calling getModule:GEOFENCING on your location provider. It provides a way to be notified when location is detected in a certain area (see ISGeofenceZone), defined on Insiteo servers. To use this class, you just have to call setListener(ISPGeofenceListener), and start the location. The listener will then receive notification each time location enter/stay/leave an area.
 */
@interface ISGeofenceProvider : NSObject <ISPLbsModule> {
    
@private
    
    //Coordinates mode to use
    CoordinatesMode m_coordMode;
    //If no location was received during this time, we notify that a reset of all zone's state have been done
    NSTimeInterval m_timeToReset;
    //Maps settings (geomatrix, map identifier, scale)
    NSMutableDictionary * m_mapsSettings;
    //All geofencing areas to consider
    NSMutableDictionary * m_areas;
    //Areas mutex
    NSLock * m_lock;
    //Current active geofencing zones (state != UNDEFINED)
    NSMutableArray * m_activeZones;
    //Geofencing notifications listener
    id<ISPGeofenceListener> m_listener;
    
    //Boolean use to know if the provider is initialized
    volatile Boolean m_isInitialized;
    //Internal boolean use to know if the provider is initializing
    volatile Boolean m_isInitializing;
    
    //Internal timer use to handle reset time
    NSTimer * m_resetTimer;
    //Intenr last package version
    int m_lastPackageVersion;
    
#pragma mark - GeoPush
    
    NSDictionary * m_geoPushMapSettings;
    
#pragma mark - Render
    
    //Geofence area Renderer
    ISGeofenceAreaRenderer * m_geofenceAreaRenderer;
}

/*!
 Geofencing notifications listener.
 */
@property (assign) id<ISPGeofenceListener> listener;

/*!
 Boolean use to know if the provider is initialized.
 */
@property (nonatomic, readonly) Boolean isInitialized;

/*
 All current used geofence areas
 */
@property (nonatomic, readonly) NSDictionary * areas;

/*!
 Geofence area Renderer.
 */
@property (nonatomic, retain) ISGeofenceAreaRenderer * renderer;

/*!
 Method used to know if a ISGeofenceArea exists with a specified guid.
 @param guid Corresponding area guid.
 @return <b>YES</b> if the area already exists; otherwise <b>NO</b>.
 */
- (Boolean)geofenceAreaExistsWithGuid:(NSString *)guid;

/*!
 Method used to know if a ISGeofenceArea exists with a specified zone identifier.
 @param zoneId Corresponding area zone identifier.
 @return <b>YES</b> if the area already exists; otherwise <b>NO</b>.
 */
- (Boolean)geofenceAreaExistsWithZoneId:(int)zoneId;

/*!
 Method used to know if a ISGeofenceArea exists with a specified Zone/Poi association.
 @param zonePoi Zone/Poi association.
 @return <b>YES</b> if the area already exists; otherwise <b>NO</b>.
 */
- (Boolean)geofenceAreaExistsWithZonePoi:(ISZonePoi *)zonePoi;

/*!
 Method used to know if a ISGeofenceArea exists.
 @param area Corresponding area.
 @return <b>YES</b> if the area already exists; otherwise <b>NO</b>.
 */
- (Boolean)geofenceAreaExistsWithArea:(ISGeofenceArea *)area;

#pragma mark - ISZone

/*!
 Equivalent to addGeofenceAreaWithZoneId:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andDefaultGeoWidth: with the following values defaultGeoWidth = value defined in geoPush.csv, enteredEnabled = stayedEnabled = leaveEnabled = value defined in geoPush.csv and enteredTime = stayedTime = leaveTime = value defined in geoPush.csv.
 @param zoneId  zone identifier.
 @param content The content for the created GeofenceArea.
 */
- (ISGeofenceArea *)addGeofenceAreaWithZoneId:(int)zoneId andContent:(NSString *)content;

/*!
 Equivalent to addGeofenceAreaWithZoneId:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andDefaultGeoWidth: with the following values defaultGeoWidth = value defined in geoPush.csv and enteredEnabled = stayedEnabled = leaveEnabled = value defined in geoPush.csv.
 @param zoneId  zone identifier.
 @param content The content for the created GeofenceArea.
 @param eventTime The time used to trigged the geofencing events.
 */
- (ISGeofenceArea *)addGeofenceAreaWithZoneId:(int)zoneId andContent:(NSString *)content andEventTime:(float)eventTime;

/*!
 Creates a new ISGeofenceArea for the given zone. The area will be constructed with the given parameters.
 @param zoneId  zone identifier.
 @param content The content for the created GeofenceArea.
 @param enterEnabled True if entered event should be enabled.
 @param enterTime The threshold time to trigger the entered event.
 @param stayEnabled True if stayed event should be enabled.
 @param stayTime The threshold time to trigger the stayed event.
 @param leaveEnabled True if leave event should be enabled.
 @param leaveTime The threshold time to trigger the leave event.
 @param defaultGeoWidth The default geofence depth.
 */
- (ISGeofenceArea *)addGeofenceAreaWithZoneId:(int)zoneId andContent:(NSString *)content andEnterEnabled:(Boolean)enterEnabled andEnterTime:(float)enterTime andStayEnabled:(Boolean)stayEnabled andStayTime:(float)stayTime andLeaveEnabled:(Boolean)leaveEnabled andLeaveTime:(float)leaveTime andDefaultGeoWidth:(float)defaultGeoWidth;

#pragma mark - ISZonePoi

/*!
 Equivalent to addGeofenceAreaWithZonePoi:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andDefaultGeoWidth: with the following values defaultGeoWidth = value defined in geoPush.csv, enteredEnabled = stayedEnabled = leaveEnabled = value defined in geoPush.csv and enteredTime = stayedTime = leaveTime = value defined in geoPush.csv.
 @param zonePoi Related Zone/Poi association (could be nil).
 @param content The content for the created GeofenceArea.
 */
- (ISGeofenceArea *)addGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi andContent:(NSString *)content;

/*!
 Equivalent to addGeofenceAreaWithZonePoi:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andDefaultGeoWidth: with the following values defaultGeoWidth = value defined in geoPush.csv and enteredEnabled = stayedEnabled = leaveEnabled = value defined in geoPush.csv.
 @param zonePoi Related Zone/Poi association (could be nil).
 @param content The content for the created GeofenceArea.
 @param eventTime The time used to trigged the geofencing events.
 */
- (ISGeofenceArea *)addGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi andContent:(NSString *)content andEventTime:(float)eventTime;

/*!
 Creates a new ISGeofenceArea for the given Zone/Poi association. The area will be constructed with the given parameters.
 @param zonePoi Related Zone/Poi association (could be nil).
 @param content The content for the created GeofenceArea.
 @param enterEnabled True if entered event should be enabled.
 @param enterTime The threshold time to trigger the entered event.
 @param stayEnabled True if stayed event should be enabled.
 @param stayTime The threshold time to trigger the stayed event.
 @param leaveEnabled True if leave event should be enabled.
 @param leaveTime The threshold time to trigger the leave event.
 @param defaultGeoWidth The default geofence depth.
 */
- (ISGeofenceArea *)addGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi andContent:(NSString *)content andEnterEnabled:(Boolean)enterEnabled andEnterTime:(float)enterTime andStayEnabled:(Boolean)stayEnabled andStayTime:(float)stayTime andLeaveEnabled:(Boolean)leaveEnabled andLeaveTime:(float)leaveTime andDefaultGeoWidth:(float)defaultGeoWidth;

#pragma mark - Custom point

/*!
 Equivalent to addGeofenceAreaWithGUID:andCenter:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andSize: with the following values size = 4 * IS_GEO_PUSH_DEFAULT_CUSTOM_GEO_WIDTH, enteredEnabled = stayedEnabled = leaveEnabled = true and enteredTime = stayedTime = leaveTime = IS_GEO_PUSH_DEFAULT_EVENT_TIME.
 @param guid The guid that should be used for the new ISGeofenceArea. Guid can not be null or empty!
 @param center The center of the ISGeofenceArea.
 @param content  The content for the created ISGeofenceArea.
 @return The created ISGeofenceArea or null if it was not properly created.
 */
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andContent:(NSString *)content;

/*!
 Equivalent to addGeofenceAreaWithGUID:andCenter:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andSize: with the following values size = 4 * IS_GEO_PUSH_DEFAULT_CUSTOM_GEO_WIDTH, enteredEnabled = stayedEnabled = leaveEnabled = true and enteredTime = stayedTime = leaveTime = eventTime.
 @param guid The guid that should be used for the new ISGeofenceArea. Guid can not be null or empty!
 @param center The center of the ISGeofenceArea.
 @param content  The content for the created ISGeofenceArea.
 @param eventTime The time used to trigged the geofencing events.
 @return The created ISGeofenceArea or null if it was not properly created.
 */
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andContent:(NSString *)content andEventTime:(float)eventTime;

/*!
 Equivalent to addGeofenceAreaWithGUID:andCenter:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andSize: with the following values size = 4 * IS_GEO_PUSH_DEFAULT_CUSTOM_GEO_WIDTH.
 @param guid The guid that should be used for the new ISGeofenceArea. Guid can not be null or empty!
 @param center The center of the ISGeofenceArea.
 @param content The content for the created ISGeofenceArea.
 @param enteredEnabled True if entered event should be enabled.
 @param enteredTime The threshold time to trigger the entered event.
 @param stayedEnabled True if stayed event should be enabled.
 @param stayedTime The threshold time to trigger the stayed event.
 @param leaveEnabled True if leave event should be enabled.
 @param leaveTime The threshold time to trigger the leave event.
 @return The created ISGeofenceArea or null if it was not properly created.
 */
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andContent:(NSString *)content andEnterEnabled:(Boolean)enteredEnabled andEnteredTime:(float)enteredTime andStayedEnabled:(Boolean)stayedEnabled andStayedTime:(float)stayedTime andLeaveEnabled:(Boolean)leaveEnabled andLeaveTime:(float)leaveTime;

/*!
 Equivalent to addGeofenceAreaWithGUID:andCenter:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andSize: with the following values enteredEnabled = stayedEnabled = leaveEnabled = true and enteredTime = stayedTime = leaveTime = IS_GEO_PUSH_DEFAULT_EVENT_TIME.
 @param guid The guid that should be used for the new ISGeofenceArea. Guid can not be null or empty!
 @param center The center of the ISGeofenceArea.
 @param size The size for the square.
 @param content The content for the created ISGeofenceArea or null if it was not properly created.
 */
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andContent:(NSString *)content andSize:(float)size;

/*!
 Equivalent to addGeofenceAreaWithGUID:andCenter:andContent:andEnterEnabled:andEnteredTime:andStayedEnabled:andStayedTime:andLeaveEnabled:andLeaveTime:andSize: with the following values enteredEnabled = stayedEnabled = leaveEnabled = true and enteredTime = stayedTime = leaveTime = eventTime.
 @param guid The guid that should be used for the new ISGeofenceArea. Guid can not be null or empty!
 @param center The center of the ISGeofenceArea.
 @param size The size for the square.
 @param content The content for the created ISGeofenceArea.
 @param eventTime The time used to trigged the geofencing events.
 @return The created GeofenceArea or null if it was not properly created.
 */
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andContent:(NSString *)content andEventTime:(float)eventTime andSize:(float)size;

/*!
 Creates a new ISGeofenceArea around the given Position. The area will be a square constructed with the given size.
 @param guid The guid that should be used for the new GeofenceArea. Guid can not be nil or empty!
 @param center The center of the GeofenceArea.
 @param size The size for the square.
 @param content The content for the created GeofenceArea.
 @param enteredEnabled True if entered event should be enabled.
 @param enteredTime The threshold time to trigger the entered event.
 @param stayedEnabled True if stayed event should be enabled.
 @param stayedTime The threshold time to trigger the stayed event.
 @param leaveEnabled True if leave event should be enabled.
 @param leaveTime The threshold time to trigger the leave event.
 @return The created GeofenceArea or nil if it was not properly created.
 */
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andContent:(NSString *)content andEnterEnabled:(Boolean)enteredEnabled andEnteredTime:(float)enteredTime andStayedEnabled:(Boolean)stayedEnabled andStayedTime:(float)stayedTime andLeaveEnabled:(Boolean)leaveEnabled andLeaveTime:(float)leaveTime andSize:(float)size;

/*
 Intern method used to add a new ISGeofenceArea to the module.
 */
- (Boolean)addGeofenceArea:(ISGeofenceArea *)area;

/*!
 Method used to remove a ISGeofenceArea according to its guid.
 @param guid Corresponding area guid to remove.
 */
- (void)removeGeofenceAreaWithGuid:(NSString *)guid;

/*!
 Method used to remove a ISGeofenceArea according to a zone identifier.
 @param zoneId Corresponding zone identifier to remove from.
 */
- (void)removeGeofenceAreaWithZoneId:(int)zoneId;

/*!
 Method used to remove a ISGeofenceArea according to a Zone/Poi association.
 @param zonePoi Corresponding Zone/Poi association to remove from.
 */
- (void)removeGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi;

/*!
 Method used to remove a ISGeofenceArea.
 @param area Area to remove.
 */
- (void)removeGeofenceAreaWithArea:(ISGeofenceArea *)area;

@end
	