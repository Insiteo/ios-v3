//
//  ISEmbeddedItineraryProvider.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 02/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISEmbeddedItineraryProvider.h
 ISEmbeddedItineraryProvider
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "ISPosition.h"
#import "ISItineraryStructures.h"

/*!
 Class used to handle embedded itinerary requests and instruction methods.
 @warning When using this class, you will need to tag your implementor as C++ class (*.mm extension).
 */

@interface ISEmbeddedItineraryProvider : NSObject {

@private
    
    //Last computed itinerary reference
    ISItinerary * m_lastItinerary;
    //Debug mode
    Boolean m_debug;
    //Last wanted language
    NSString * m_language;
    //Itinerary data path
    NSString * m_dataPath;
}

/*!
 Main constructor.
 @warning When instanciating this class, you will need to tag your implementor as C++ class (*.mm extension).
 @param debug Boolean used to know if we use it in DEBUG mode.
 @param language Language to use for instructions.
 @param pmr Boolean used to know if we compute routes for handicap persons.
 */
- (Boolean)initWithDebug:(Boolean)debug andLanguage:(NSString *)language andPMR:(Boolean)pmr;

/*!
 Method called to get a route between two points.
 @param startPositions Start position array.
 @param endPositions End position array.
 @param pmr Boolean used to know if we compute a route for disabled people.
 @return The computed road.
 */
- (ISItinerary *)executeRequestWithStartPositions:(NSMutableArray *)startPositions andEndPositions:(NSMutableArray *)endPositions andPMR:(Boolean)pmr;

/*!
 Method called to get a route between two points.
 @param startPosition Start position.
 @param endPosition End position.
 @param pmr Boolean used to know if we compute a route for disabled people.
 @return The computed road.
 */
- (ISItinerary *)executeRequestWithStartPosition:(ISPosition *)startPosition andEndPosition:(ISPosition *)endPosition andPMR:(Boolean)pmr;

/*!
 Method called to get a the last updated route.
 @return The updated road.
 */
- (ISItinerary *)getUpdatedItinerary;

/*!
 Method used to set the user current position.
 @param position Position to set.
 @return The distance to join the graph (in meters).
 */
- (double)setCurrentPosition:(ISPosition *)position;

/*!
 Method used to get an optimized route between several points.
 @param waypoints Waypoints to pass through.
 @param mode Algorithm optimization mode.
 @param keepFirstPosition Boolean used to know if we treat the first position.
 @param keepLastPosition Boolean used to know if we treat the last position.
 @param pmr Boolean used to know if we compute a route for disabled people.
 @return The computed routes.
 */
- (NSArray *)getOptimizedRouteWithWaypoints:(NSArray *)waypoints andOptimMode:(int)mode andKeepFirstPosition:(Boolean)keepFirstPosition andKeepLastPosition:(Boolean)keepLastPosition andPMR:(Boolean)pmr;

#pragma mark - Static methods

/*!
 Static method used to get the instruction index from a position in external coordinates.
 @param position External position to test.
 @return A point with x = instruction index (sould be cast to int) and y = distance in meters to the instruction edge.
 */
+ (CGPoint)getInstructionIdWithPosition:(ISPosition *)position;

/*!
 Static method used to get the current remaining distance (in meters).
 @return The current remaining distance.
 */
+ (double)getRemainingDistance;

/*!
 Static method used to get the current remaining time (in seconds).
 @return The current remaining distance.
 */
+ (double)getRemainingTime;

/*!
 Static method used to get the bounding rect of the current itinerary for a specified map identifier.
 @param mapId Wanted map identifier.
 @return The result bounding rect.
 */
+ (CGRect)getItineraryBoundingRect:(int)mapId;

@end
