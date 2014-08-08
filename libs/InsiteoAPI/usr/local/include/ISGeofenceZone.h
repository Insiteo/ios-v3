//
//  ISGeofenceZone.h
//  LocationAPI
//
//  Created by INSITEO on 14/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISGeofenceZone.h
 ISGeofenceZone
 */

#import <Foundation/Foundation.h>

@class ISPosition;

/*!
 Enum used to represent a geofencing zone state.
 @constant UNDEFINED Default value.
 @constant ENTERING A position is entering a zone (a position was detected in the zone).
 @constant ENTERED After a custom time and if the state didn't changed, we consider that a position is entered.
 @constant STAY After a position was entered in a zone and after a custom time without state change, we consider that a position stayed in the zone.
 @constant LEAVING A position is leaving a zone. (a position was detected outside the zone).
 @constant LEFT After a position was considerer leaving and if no state change occured for a custom time, we consider that a position has left the zone.
 */
typedef enum {
	UNDEFINED = 0,
    ENTERING,
    ENTERED,    //2
    STAY,       //3
    LEAVING,
    LEFT        //5
} GeofenceEventType;

/*!
 Class holding data for a geofencing zone. It contains the GUID of the zone, and it's center.
 */
@interface ISGeofenceZone : NSObject {
    
@private
    
    //Geofencing zone identifier
    NSString * m_GUID;
    //The position representing the center of this zone
    ISPosition * m_center;
    //Extra data attribute
    NSString * m_extra1;
    //Extra data attribute
    NSString * m_extra2;
    //Extra data attribute
    NSString * m_extra3;  
    //Internal time used to know when this zone will be left, whithout needing corrsponding area (in milliseconds)
    NSTimeInterval m_timeToLeave;
    //Current geofencing zone state
    GeofenceEventType m_eventType;
    //Internal time used to update zone state
    NSTimeInterval m_eventTime;
    //Boolean used to know if we need to notify a listener
    Boolean m_notify;
    //Boolean used to know if we notify on left event
    Boolean m_isLeaveEnabled;
    //Boolean used to know if the area was automatically added to the provider
    Boolean m_autoStart;
}

/*!
 Geofencing zone identifier.
 */
@property (nonatomic, retain) NSString * GUID;

/*!
 The position representing the center of this zone.
 */
@property (nonatomic, retain) ISPosition * center;

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
 Internal time used to know when this zone will be left, whithout needing corrsponding area (in milliseconds).
 */
@property (nonatomic, readonly) NSTimeInterval timeToLeave;

/*!
 Current geofencing zone state.
 */
@property (nonatomic, readwrite) GeofenceEventType eventType;

/*!
 Internal time used to update zone state.
 */
@property (nonatomic, readwrite) NSTimeInterval eventTime;

/*!
 Boolean used to know if we need to notify a listener.
 */
@property (nonatomic, readwrite) Boolean notify;

/*!
 Boolean used to know if we notify on left event.
 */
@property (nonatomic, readwrite) Boolean isLeaveEnabled;

/*!
 Boolean used to know if the area was automatically added to the provider.
 */
@property (nonatomic, readwrite) Boolean autoStart;

/*!
 Static main constructor.
 @param GUID Geofencing zone identifier.
 @param center The position representing the center of this zone.
 @param timeToLeave Internal time used to know when this zone will be left, whithout needing corrsponding area (in milliseconds).
 @param extra1 Extra data attribute.
 @param extra2 Extra data attribute.
 @param extra3 Extra data attribute.
 @param isLeaveEnabled Boolean used to know if we notify on left event.
 */
+ (id)ISGeofenceZoneWithGUID:(NSString *)GUID andCenter:(ISPosition *)center andTimeToLeave:(NSTimeInterval)timeToLeave andExtra1:(NSString *)extra1 andExtra2:(NSString *)extra2 andExtra3:(NSString *)extra3 andIsLeaveEnabled:(Boolean)isLeaveEnabled;

/*!
 Main constructor.
 @param GUID Geofencing zone identifier.
 @param center The position representing the center of this zone.
 @param timeToLeave Internal time used to know when this zone will be left, whithout needing corrsponding area (in milliseconds).
 @param extra1 Extra data attribute.
 @param extra2 Extra data attribute.
 @param extra3 Extra data attribute.
 @param isLeaveEnabled Boolean used to know if we notify on left event.
 */
- (id)initWithGUID:(NSString *)GUID andCenter:(ISPosition *)center andTimeToLeave:(NSTimeInterval)timeToLeave andExtra1:(NSString *)extra1 andExtra2:(NSString *)extra2 andExtra3:(NSString *)extra3 andIsLeaveEnabled:(Boolean)isLeaveEnabled;

@end
