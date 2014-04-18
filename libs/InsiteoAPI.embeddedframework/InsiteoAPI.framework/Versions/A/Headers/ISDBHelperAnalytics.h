//
//  ISDBHelperAnalytics.h
//  CommonAPI
//
//  Created by dev_iphone on 11/02/13.
//
//

/*!
 @header ISDBHelperAnalytics.h
 ISDBHelperAnalytics
 */

#import <Foundation/Foundation.h>

#import "ISRWDBHelper.h"
#import "ISAnalyticsUserEvent.h"
#import "ISAnalyticsGenericEvent.h"
#import "ISAnalyticsLocationEvent.h"
#import "ISPosition.h"

@class AnalyticsRequest;

/*!
 Intern class used to represent an analytics abstract database element.
 */
@interface ISAbstractElem : NSObject {
    
@private
    
    //The related databse event identifier
    int m_eventId;
    //The event type
    int m_eventType;
}

/*!
 The related databse event identifier.
 */
@property (nonatomic, readwrite) int eventId;

/*!
 The event type.
 */
@property (nonatomic, readwrite) int eventType;

/*!
 Main constructor.
 @param eventId The related databse event identifier.
 @param eventType The event type.
 */
- (id)initWithEventId:(int)eventId andEventType:(int)eventType;

/*!
 Static constructor.
 @param eventId The related databse event identifier.
 @param eventType The event type.
 */
+ (ISAbstractElem *)ISAbstractElemWithEventId:(int)eventId andEventType:(int)eventType;

@end

/*!
 Class that handles analytics database stuff.
 */
@interface ISDBHelperAnalytics : ISRWDBHelper {
    
}

/*!
 Method used to get the ISDBHelperAnalytics unique instance.
 @result The ISDBHelperAnalytics unique instance.
 */
+ (ISDBHelperAnalytics *)instance;

/*!
 Method used to send a analytics user event.
 @param event The event to send.
 */
+ (void)addUserEvent:(ISAnalyticsUserEvent *)event;

/*!
 Method used to send a analytics generic event.
 @param event The event to send.
 */
+ (void)addGenericEvent:(ISAnalyticsGenericEvent *)event;

/*!
 Method used to send a analytics location event.
 @param event The event to send.
 */
+ (void)addLocationEvent:(ISAnalyticsLocationEvent *)event;

/*
 Method used to get an array of events that needs to be sent.
 @param request The related request (used for its request identifier).
 @param maxEvents The max number of events returned.
 @return The events array that needs to be sent.
 */
+ (NSMutableArray *)getEventsToSendWithRequest:(AnalyticsRequest *)request andMaxEvents:(int)maxEvents;

/*
 Method called to reset all database request identifiers.
 */
+ (void)resetRequestIds;

/*
 Method called to clear a request in the database (remove all related content).
 @param request The related request to clear.
 */
+ (void)clearRequest:(AnalyticsRequest *)request;

@end
