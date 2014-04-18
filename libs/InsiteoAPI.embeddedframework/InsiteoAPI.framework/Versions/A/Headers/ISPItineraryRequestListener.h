//
//  ISPItineraryRequestListener.h
//  LocationAPI
//
//  Created by INSITEO on 26/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPItineraryRequestListener.h
 ISPItineraryRequestListener
 */

#import <Foundation/Foundation.h>

#import "ISInsiteoError.h"

@class ISItineraryBaseRequest;

/*!
 Protocol used to handle Itinerary request events.
 */
@protocol ISPItineraryRequestListener <NSObject>

/*!
 Method called when an Itinerary request succeeded.
 @param success A boolean used to know if the request succeeded.
 @param request The related request.
 @param error If failed, it contains the related error.
 */
- (void)onItineraryRequestDoneWithSuccess:(Boolean)success andRequest:(ISItineraryBaseRequest *)request andError:(ISInsiteoError *)error;

/*!
 Method called when the last itinerary changed (example: after user location changed).
 @param request The related request.
 @param distanceToItinerary The distance (in meters) between the last user location and the resulted itinerary (-1 if map changed).
 */
- (void)onItineraryChangedWithRequest:(ISItineraryBaseRequest *)request andDistanceToItinerary:(float)distanceToItinerary;

@end
