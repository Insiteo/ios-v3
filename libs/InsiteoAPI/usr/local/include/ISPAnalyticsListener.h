//
//  ISPAnalyticsListener.h
//  lbs
//
//  Created by dev_iphone on 04/08/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISPAnalyticsListener.h
 ISPAnalyticsListener
 */

#import <Foundation/Foundation.h>

#import "ISAnalyticsGenericEvent.h"

/*!
 Protocol used to handle analytics events.
 */
@protocol ISPAnalyticsListener <NSObject>

@optional

/*!
 Method called before sending an analytics event.
 @param event The analytics event that will be sent.
 @return <b>YES</b> if you want to send this event, otherwise <b>NO</b>.
 */
- (Boolean)analyticsManagerShouldSendGenericEvent:(ISAnalyticsGenericEvent *)event;

@end
