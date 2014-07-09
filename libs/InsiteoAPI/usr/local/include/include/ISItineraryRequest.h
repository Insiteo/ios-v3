//
//  ISItineraryRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISItineraryRequest.h
 ISItineraryRequest
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "ISPosition.h"
#import "ISConfig.h"
#import "ISItineraryBaseRequest.h"

#define ERR_ITI_CHECK_LOCATION_CODE     [ISConfig realLocalizedString:@"STR_ITI_CHECK_LOCATION_TITLE"]
#define ERR_ITI_CHECK_LOCATION_MESSAGE  [ISConfig realLocalizedString:@"STR_ITI_CHECK_LOCATION_DETAIL"]
#define ERR_ITI_GET_ROUTE_CODE          [ISConfig realLocalizedString:@"STR_ITI_GET_ROUTE_TITLE"]
#define ERR_ITI_GET_ROUTE_MESSAGE       [ISConfig realLocalizedString:@"STR_ITI_GET_ROUTE_DETAIL"]

/*!
 Class used to represent an itinerary request.
 */
@interface ISItineraryRequest : ISItineraryBaseRequest {
    
@private
    
#pragma mark - Request variables
    
    //Itinerary start position array
    NSMutableArray * m_startPositions;
    //Itinerary end position array
    NSMutableArray * m_endPositions;
    
#pragma mark - Internal
    
    //Start date
    NSDate * m_startDate;
    //Timer used to check if a location is available
    NSTimer * m_locationTimer;
    //Location id used to know if a new location is available
    int m_locationId;
    //Boolean used to know if the request is from user location
    Boolean m_isFromUserLocation;
}

/*!
 Itinerary start position array.
 */
@property (nonatomic, retain) NSMutableArray * startPositions;

/*!
 Itinerary end position array.
 */
@property (nonatomic, retain) NSMutableArray * endPositions;

/*!
 Secondary constructor.
 @param itineraryProvider Itinerary provider reference.
 @param locationId Itinerary request location id (used to check if a valid location is available).
 @param listener Object to notify when the request succeeded or failed.
 */
- (id)initWithItineraryProvider:(ISItineraryProvider *)itineraryProvider andLocationId:(int)locationId andListener:(id<ISPItineraryRequestListener>)listener;

@end
