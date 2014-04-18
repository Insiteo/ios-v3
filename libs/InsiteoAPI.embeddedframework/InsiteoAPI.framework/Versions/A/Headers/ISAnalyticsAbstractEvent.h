//
//  ISAnalyticsAbstractEvent.h
//  CommonAPI
//
//  Created by dev_iphone on 11/02/13.
//
//

/*!
 @header ISAnalyticsAbstractEvent.h
 ISAnalyticsAbstractEvent
 */

#import <Foundation/Foundation.h>

/*!
 @"IS_GUID_PREF_KEY"
 */
extern NSString * const IS_GUID_PREF_KEY;

#import "ISPProtoEventBuilder.h"

/*!
 Class used to represent an analytics abstract event.
 */
@interface ISAnalyticsAbstractEvent : NSObject <ISPProtoEventBuilder> {
    
@protected
    
#pragma mark - Structure
    
    //Timestamp
    int64_t m_timeStamp;
    //User GUID
    NSString * m_guid;
    
#pragma mark - Database
    
    //Database event identifier
    int m_eventId;
}

/*!
 Event timestamp.
 */
@property (nonatomic, readwrite) int64_t timeStamp;

/*!
 Event related GUID.
 */
@property (nonatomic, retain) NSString * guid;

/*!
 Event database identifier.
 */
@property (nonatomic, readwrite) int eventId;

/*
 Static method used to get an unique identifier.
 */
+ (NSString *)getUUID;

/*
 Intern method used to get the suitable current site identifier.
 */
- (int)getSiteId;

@end
