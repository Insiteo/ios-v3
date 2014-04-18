//
//  ISLocation.h
//  LocationAPI
//
//  Created by INSITEO on 06/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISLocation.h
 ISLocation
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#import "ISPosition.h"

/*!
 Class used to represent a location result.
 */
@interface ISLocation : NSObject {
    
@private
    
    //Location position (x, y, mapId)
    ISPosition * m_position;            //see ISPosition.h for more details
	//Location accuracy
	double m_accuracy;
    //Location type
    int m_locationType;    //see ISLocationProvider for more details
}

/*!
 Location position (x, y, mapId).
 */
@property (nonatomic, retain) ISPosition * position;

/*!
 Location accuracy.
 */
@property (nonatomic, readwrite) double accuracy;

/*!
 Location type.
 */
@property (nonatomic, readwrite) int locationType;

/*!
 Main constructor.
 @param locationType Location type (used modules).
 @param mapId Location map id.
 @param x X coordinate (in meters).
 @param y Y coordinate (in meters).
 @param accuracy Location accuracy.
 */
- (id)initWithLocationType:(int)locationType andMapId:(int)mapId andX:(double)x andY:(double)y andAccuracy:(double)accuracy;

/*!
 Second constructor.
 @param location Location to copy.
 */
- (id)initWithLocation:(ISLocation *)location;

/*!
 Method used to update the location with another location.
 @param location Location to use.
 */
- (void)updateWithLocation:(ISLocation *)location;

/*!
 Accessor used to get the x coordinate.
 */
- (double)x;

/*!
 Accessor used to get the y coordinate.
 */
- (double)y;

/*!
 Accessor used to get the map identifier.
 */
- (int)mapId;


@end
