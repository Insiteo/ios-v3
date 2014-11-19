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
#import "ISPAnalyticsListener.h"

@class AnalyticsThread;
@class AnalyticsConfig;
@class AnalyticsUserEvent;

/*!
 Class that manages analytics events.
 */
@interface ISAnalyticsManager : NSObject

/*!
 Analytics configuration.
 */
@property (nonatomic, retain) AnalyticsConfig * config;

/*!
 Analytics listener.
 */
@property (assign) id<ISPAnalyticsListener> listener;

/*!
 Boolean used to know if the analytics manager is started.
 */
@property (nonatomic, readonly) Boolean isStarted;

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
- (Boolean)stopAnalytics;

/*!
 Method called to add an analytics generic event.
 @param event The related generic event.
 @result <b>YES</b> if the event was successfully added, otherwise <b>NO</b>.
 */
- (Boolean)addGenericEvent:(ISAnalyticsGenericEvent *)event;

/*!
 Method called to add an analytics location event.
 @param event The related location event.
 @result <b>YES</b> if the event was successfully added, otherwise <b>NO</b>.
 */
- (Boolean)addLocationEvent:(ISAnalyticsLocationEvent *)event;

@end
