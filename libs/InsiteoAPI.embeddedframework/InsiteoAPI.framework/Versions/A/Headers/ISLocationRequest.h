//
//  ISLocationRequest.h
//  LocationAPI
//
//  Created by dev_iphone on 05/11/12.
//
//

/*!
 @header ISLocationRequest.h
 ISLocationRequest
 */

#import <Foundation/Foundation.h>

#import "ISLocation.h"
#import "ISPLocationRequestListener.h"

/*!
 Class used to compute one unique location.
 */
@interface ISLocationRequest : NSObject {
    
@private
    
    //Location request listener
    id<ISPLocationRequestListener> m_locationRequestListener;
    //Computed location
    ISLocation * m_location;
    //Timer used to handle location time out
    NSTimer * m_timer;
}

/*!
 Listener to notify of location events.
 */
@property (assign) id<ISPLocationRequestListener> locationRequestListener;

/*!
 Computed location (could be nil).
 */
@property (nonatomic, retain) ISLocation * location;

/*!
 Intern timer used to simulate a request timeout.
 */
@property (nonatomic, retain) NSTimer * timer;

/*!
 Main constructor.
 @param locationRequestListener Listener to notify of location events.
 */
- (id)initWithLocationRequestListener:(id<ISPLocationRequestListener>)locationRequestListener;

/*!
 Method called when a new location was computed.
 @param location New computed location.
 */
- (void)onLocationComputed:(ISLocation *)location;

/*!
 Method called when an error occurred.
 @param error Related error.
 */
- (void)onLocationFailed:(ISInsiteoError *)error;

@end
