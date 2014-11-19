//
//  ISItinerary.h
//  lbs
//
//  Created by dev_iphone on 17/10/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISItinerary.h
 ISItinerary
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 Class used to define an Itinerary with its instructions.
 */
@interface ISItinerary : NSObject

/*!
 Start point.
 */
@property (nonatomic, readwrite) CGPoint startPoint;

/*!
 Start map identifier.
 */
@property (nonatomic, readwrite) int startMapId;

/*!
 End point.
 */
@property (nonatomic, readwrite) CGPoint endPoint;

/*!
 End map identifier.
 */
@property (nonatomic, readwrite) int endMapId;

/*!
 An array that contains all the itinerary instructions (array of ISItineraryInstruction).
 */
@property (nonatomic, retain) NSMutableArray * instructions;

/*!
 The total distance (in meters) from departure to arrival.
 */
@property (nonatomic, readwrite) double totalDistance;

/*!
 The time (in seconds) from departure to arrival.
 */
@property (nonatomic, readwrite) double totalTime;

/*!
 A dictionnary which contains all bounding rect for a specified map (could be nil: offline mode).
 */
@property (nonatomic, retain) NSMutableDictionary * boundingRects;

/*!
 The remaining distance (in meters) from current location (or departure if no location is set) to arrival.
 */
@property (nonatomic, readwrite) double remainingDistance;

/*!
 The time (in seconds) from current location (or departure if no location is set) to arrival.
 */
@property (nonatomic, readwrite) double remainingTime;

/*!
 Method used to get the total amout of sections.
 @return The total amout of sections.
 */
- (int)getNbSections;

@end