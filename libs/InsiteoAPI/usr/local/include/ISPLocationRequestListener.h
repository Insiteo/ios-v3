//
//  ISPLocationRequestListener.h
//  LocationAPI
//
//  Created by dev_iphone on 05/11/12.
//
//

/*!
 @header ISPLocationRequestListener.h
 ISPLocationRequestListener
 */

#import <Foundation/Foundation.h>

#import "ISInsiteoError.h"

@class ISLocationRequest;

/*!
 Protocol used to handle one shot location events.
 */
@protocol ISPLocationRequestListener <NSObject>

/*!
 Method called when a one shot location was computed.
 @param locationRequest Related location request (used to identify callers).
 */
- (void)onUniqueLocationReceivedWithRequest:(ISLocationRequest *)locationRequest;

/*!
 Method called when a one shot location request failed.
 @param locationRequest Related location request (used to identify callers).
 @param error Related Insiteo error.
 */
- (void)onUniqueLocationFailedWithRequest:(ISLocationRequest *)locationRequest andError:(ISInsiteoError *)error;

@end
