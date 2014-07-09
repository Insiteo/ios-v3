//
//  ISAnalyticsManager.h
//  CommonAPI
//
//  Created by dev_iphone on 11/02/13.
//
//

/*!
 @header ISAnalyticsManager.h
 ISAnalyticsManager
 */

#import <Foundation/Foundation.h>

#import "ISAnalyticsGenericEvent.h"
#import "ISAnalyticsLocationEvent.h"

@class AnalyticsThread;
@class AnalyticsConfig;
@class AnalyticsUserEvent;

/*!
 Class that manages analytics events.
 */
@interface ISAnalyticsManager : NSObject {
    
@private
    
#pragma mark - Config
    
    //Analytics configuration
    AnalyticsConfig * m_config;
    
#pragma mark - Structure
    
    //Last user event (used to test changes)
    AnalyticsUserEvent * m_lastUserEvent;
    
#pragma mark - Behavior
    
    //Boolean used to know if the ISAnalyticsManager is well initialized
    Boolean m_isReady;
    //Intern date to know when the last location event was sent
    NSDate * m_lastLocationDate;
    //Request thread
    AnalyticsThread * m_thread;
}

/*!
 Analytics configuration.
 */
@property (nonatomic, retain) AnalyticsConfig * config;

/*!
 Static method called to get the ISAnalyticsManager unique instance.
 @result The ISAnalyticsManager unique instance.
 */
+ (ISAnalyticsManager *)instance;

/*
 Internal static method called to start the ISAnalyticsManager.
 @result Return <b>YES</b> if the ISAnalyticsManager is started, otherwise <b>NO</b>.
 */
- (Boolean)startAnalytics;

/*
 Internal static method called to stop the ISAnalyticsManager.
 */
- (void)stopAnalytics;

/*!
 Method called to add an analytics generic event.
 @param event The related generic event.
 */
- (void)addGenericEvent:(ISAnalyticsGenericEvent *)event;

/*!
 Method called to add an analytics location event.
 @param event The related location event.
 */
- (void)addLocationEvent:(ISAnalyticsLocationEvent *)event;

@end
