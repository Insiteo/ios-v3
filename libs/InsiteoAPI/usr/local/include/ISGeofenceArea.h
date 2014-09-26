//
//  ISGeofenceArea.h
//  LocationAPI
//
//  Created by INSITEO on 14/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISGeofenceArea.h
 ISGeofenceArea
 */

#import <Foundation/Foundation.h>

#import "ISPosition.h"

@class Zone;
@class ISZone;
@class ISZonePoi;

/*!
 Class used to represent a geofencing area.
 */
@interface ISGeofenceArea : NSObject {

@private
    
    //Geofencing area identifier
    NSString * m_GUID;
    //Area center (position in meters)
    ISPosition * m_center;
    //Area polygon (points in millimeters)
    NSMutableArray * m_polygon;
    //Zoom level index
    int m_indexZoomLevel;
    //Array containing all tile indexes where the area is present
    NSMutableArray * m_indexes;
    //Time needed to consider that we enter the area (in milliseconds)
    NSTimeInterval m_timeToEnter;
    //Time needed to consider that we leave the area (in milliseconds)
    NSTimeInterval m_timeToLeave;
    //Time needed to consider that we stay in the area (in milliseconds)
    NSTimeInterval m_timeToStay;
    //Boolean used to know if the enter event is enabled
    Boolean m_enterEnabled;
    //Boolean used to know if the stay event is enabled
    Boolean m_stayEnabled;
    //Boolean used to know if the leave event is enabled
    Boolean m_leaveEnabled;
    //Extra data attribute
    NSString * m_extra1;
    //Extra data attribute
    NSString * m_extra2;
    //Extra data attribute
    NSString * m_extra3;
    //Boolean used to know if the area was automatically added to the provider
    Boolean m_autoStart;
    //Related ISZone, could be nil
    ISZone * m_zone;
    //Related ISZonePOI, could be nil
    ISZonePoi * m_zonePoi;
}

/*!
 Geofencing area identifier.
 */
@property (nonatomic, retain) NSString * GUID;

/*!
 Area center (position in meters).
 */
@property (nonatomic, retain) ISPosition * center;

/*!
 Area polygon (points in millimeters).
 */
@property (nonatomic, retain) NSMutableArray * polygon;

/*!
 Zoom level index.
 */
@property (nonatomic, readonly) int indexZoomLevel;

/*!
 Array containing all tile indexes where the area is present.
 */
@property (nonatomic, retain) NSMutableArray * indexes;

/*!
 Time needed to consider that we enter the area.
 */
@property (nonatomic, readonly) NSTimeInterval timeToEnter;

/*!
 Time needed to consider that we leave the area.
 */
@property (nonatomic, readonly) NSTimeInterval timeToLeave;

/*!
 Time needed to consider that we stay in the area.
 */
@property (nonatomic, readonly) NSTimeInterval timeToStay;

/*!
 Boolean used to know if the enter event is enabled.
 */
@property (nonatomic, readonly) Boolean enterEnabled;

/*!
 Boolean used to know if the stay event is enabled.
 */
@property (nonatomic, readonly) Boolean stayEnabled;

/*!
 Boolean used to know if the leave event is enabled.
 */
@property (nonatomic, readonly) Boolean leaveEnabled;

/*!
 Extra data attribute.
 */
@property (nonatomic, retain) NSString * extra1;

/*!
 Extra data attribute.
 */
@property (nonatomic, retain) NSString * extra2;

/*!
 Extra data attribute.
 */
@property (nonatomic, retain) NSString * extra3;

/*!
 Boolean used to know if the area was automatically added to the provider.
 */
@property (nonatomic, readwrite) Boolean autoStart;

/*!
 Related ISZone. Could be nil.
 */
@property (nonatomic, retain) ISZone * zone;

/*!
 Related ISZonePoi. Could be nil.
 */
@property (nonatomic, retain) ISZonePoi * zonePoi;

/*!
 Static main constructor.
 @param pbzone Zone used to create the area.
 */
+ (id)ISGeofenceAreaWithPBZone:(Zone *)pbzone;

/*!
 Main constructor.
 @param pbZone Zone used to create the area.
 */
- (id)initWithPBZone:(Zone *)pbZone;

/*!
 Second constructor.
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
 */
- (id)initWithGUID:(NSString *)guid andPosition:(ISPosition *)center andSize:(float)size andContent:(NSString *)content andEnteredEnabled:(Boolean)enteredEnabled andEnteredTime:(float)enteredTime andStayedEnabled:(Boolean)stayedEnabled andStayedTime:(float)stayedTime andLeaveEnabled:(Boolean)leaveEnabled andLeaveTime:(float)leaveTime;

/*!
 Second constructor.
 @param zoneId Related zone identifier.
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
- (id)initWithZoneId:(int)zoneId andZonePoi:(ISZonePoi *)zonePoi andContent:(NSString *)content andEnterEnabled:(Boolean)enterEnabled andEnterTime:(float)enterTime andStayEnabled:(Boolean)stayEnabled andStayTime:(float)stayTime andLeaveEnabled:(Boolean)leaveEnabled andLeaveTime:(float)leaveTime andDefaultGeoWidth:(float)defaultGeoWidth;

/*!
 Method used to know if the area contains a specified position.
 @param position Position to test.
 @return <b>YES</b> if the area contains the position, otherwise <b>NO</b>.
 */
- (Boolean)containsPositionWithPosition:(ISPosition *)position;

/*!
 Static method used to get a geofence zone guid from a Zone/Poi association or a zone identifier.
 @param zonePoi Zone/Poi reference (could be nil).
 @param zoneId Corresponding zone identifier.
 */
+ (NSString *)getGuidWithZonePoi:(ISZonePoi *)zonePoi andZoneId:(int)zoneId;

@end
