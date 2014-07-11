//
//  ISItineraryBaseRequest.h
//  LocationAPI
//
//  Created by dev_iphone on 06/01/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISItineraryBaseRequest.h
 ISItineraryBaseRequest
 */

#import <Foundation/Foundation.h>

#import "ISPCancelable.h"
#import "ISItineraryStructures.h"
#import "ISPItineraryRequestListener.h"

@class ISItineraryProvider;

/*!
 Class used to represent a base itinerary request.
 */
@interface ISItineraryBaseRequest : NSObject <ISPCancelable> {

@protected

    //Boolean used to know if we compute the route for disabled people
    Boolean m_pmr;
    
#pragma mark - Itinerary
    
    //Request itinerary (will be filled by the ISItineraryProvider)
    ISItinerary * m_itinerary;
    //Itinerary request listener
    id<ISPItineraryRequestListener> m_listener;
    //ISItineraryProvider reference
    ISItineraryProvider * m_itineraryProvider;
    
#pragma mark - ISPCancelable
    
    //Internal boolean for cancel handling
    volatile Boolean m_cancelBool;
}

@property (nonatomic, readonly) Boolean cancelBool;

/*!
 Request itinerary (will be filled by the ISItineraryProvider).
 */
@property (nonatomic, retain) ISItinerary * itinerary;

/*!
 Itinerary request listener.
 */
@property (nonatomic, retain) id<ISPItineraryRequestListener> listener;

/*!
 Itinerary provider reference.
 */
@property (assign) ISItineraryProvider * itineraryProvider;

/*!
 Boolean used to know if we compute the route for disabled people.
 */
@property (nonatomic, readwrite) Boolean pmr;

/*!
 Main constructor.
 @param itineraryProvider Itinerary provider reference.
 @param listener Object to notify when the request succeeded or failed.
 */
- (id)initWithItineraryProvider:(ISItineraryProvider *)itineraryProvider andListener:(id<ISPItineraryRequestListener>)listener;

/*!
 Method called to execute the Itinerary request.
 @return A boolean used to know if the request succeeded.
 */
- (Boolean)getRoute;

/*!
 Method called to recompute the same itinerary request.
 */
- (void)recompute;

@end
