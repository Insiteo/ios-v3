//
//  ISAnalyticsThread.h
//  CommonAPI
//
//  Created by dev_iphone on 27/06/13.
//
//

/*!
 @header ISAnalyticsThread.h
 ISAnalyticsThread
 */

#import <Foundation/Foundation.h>

@class AnalyticsRequest;

/*!
 NSThread which handles analytics stuff.
 */
@interface ISAnalyticsThread : NSThread {
    
@private
    
    //Current ISAnalytics request
    AnalyticsRequest * m_currentRequest;
    //Number of events sent in one request
    int m_maxEvents;
    //Remote service URL (from ISInitProvider)
    NSString * m_serviceUrl;
    //Boolean used to know if the ISAnalyticsManager is started
    Boolean m_isStarted;
    //HTTP request frequency (in seconds)
    float m_frequency;
}

/*!
 Boolean used to know if the ISAnalyticsManager is started.
 */
@property(nonatomic, readwrite) Boolean isStarted;

/*!
 Main constructor.
 @param maxEvents Number of events sent in one request.
 @param serviceUrl Remote service URL.
 @param frequency HTTP request frequency (in seconds).
 */
- (id)initWithMaxEvents:(int)maxEvents andServiceUrl:(NSString *)serviceUrl andFrequency:(float)frequency;

@end
