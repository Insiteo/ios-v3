//
//  ISItinerarySection.h
//  lbs
//
//  Created by dev_iphone on 17/10/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISItinerarySection.h
 ISItinerarySection
 */

#import <Foundation/Foundation.h>

/*!
 Class used to define an itinerary Section.
 */
@interface ISItinerarySection : NSObject

/*!
 Section related map identifier.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 Section x coordinate.
 */
@property (nonatomic, readwrite) double x;

/*!
 Section y coordinate.
 */
@property (nonatomic, readwrite) double y;

/*!
 Section z coordinate (often 0).
 */
@property (nonatomic, readwrite) double z;

/*!
 Section related vertex identifier (DLL).
 */
@property (nonatomic, retain) NSString * vertexId;

/*!
 Section related edge identifier (DLL).
 */
@property (nonatomic, retain) NSString * edgeId;

/*!
 Section next edge type.
 */
@property (nonatomic, readwrite) int edgeType;

/*!
 Boolean used to know if the section corresponds to a map change.
 */
@property (nonatomic, readwrite) Boolean isMapChanger;

/*!
 Main constructor.
 @param mapId Section related map identifier.
 @param x Section x coordinate.
 @param y Section y coordinate.
 @param z Section z coordinate.
 @param vertexId Section related vertex identifier.
 @param edgeId Section related edge identifier.
 @param edgeType Section next edge type.
 @param isMapChanger Boolean used to know if the section corresponds to a map change.
 */
- (id)initWithMapId:(int)mapId andX:(double)x andY:(double)y andZ:(double)z andVertexId:(NSString *)vertexId andEdgeId:(NSString *)edgeId andEdgeType:(int)edgeType andIsMapChanger:(Boolean)isMapChanger;

@end
