//
//  ISItineraryOptimizedRequest.h
//  LocationAPI
//
//  Created by dev_iphone on 06/01/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISItineraryOptimizedRequest.h
 ISItineraryOptimizedRequest
 */

#import "ISItineraryRequest.h"

/*!
 Enum used to choose route optimization algorithm.
 @constant ISEOptimizationModeFullRoute 1.
 @constant ISEOptimizationModeEuclidianDistance 2.
 @constant ISEOptimizationModeNearestNeighbourEuclidian 4.
 @constant ISEOptimizationModeNearestNeighbourShortestPath 5.
 @constant ISEOptimizationModeBestMethodPath 7.
 */
typedef enum {
	ISEOptimizationModeFullRoute = 1,
	ISEOptimizationModeEuclidianDistance = 2,
//	ISEOptimizationModeQuadAreas = 3,
	ISEOptimizationModeNearestNeighbourEuclidian = 4,
	ISEOptimizationModeNearestNeighbourShortestPath = 5,
//	ISEOptimizationModeHybridPath = 6,
	ISEOptimizationModeBestMethodPath = 7
} ISEOptimizationMode;

/*!
 Class used to represent an optimized itinerary request.
 */
@interface ISItineraryOptimizedRequest : ISItineraryRequest

/*!
 Waypoints to pass through.
 */
@property (nonatomic, retain) NSArray * waypoints;

/*!
 Return sorted input waypoints.
 */
@property (nonatomic, retain) NSMutableArray * sortedWaypoints;

/*!
 Return sorted input waypoints indexes.
 */
@property (nonatomic, retain) NSMutableArray * sortedWaypointsIndexes;

/*!
 Route optimization algorithm mode.
 */
@property (nonatomic, readwrite) ISEOptimizationMode optimMode;

/*!
 Boolean used to know if we treat the first position.
 */
@property (nonatomic, readwrite) Boolean keepFirstPosition;

/*!
 Boolean used to know if we treat the last position.
 */
@property (nonatomic, readwrite) Boolean keepLastPosition;

@end
