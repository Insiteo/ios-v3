//
//  ISItineraryStructures.h
//  EmbeddedItineraryCompiler
//
//  Created by Baptiste LE GUELVOUIT on 11/05/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISItineraryStructures.h
 ISItineraryStructures
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 Class used to define an itinerary Section.
 */
@interface ISSection : NSObject {
    
@private
    
    //Section related map identifier
    int m_mapId;
    //Section x coordinate
    double m_x;
    //Section y coordinate
    double m_y;
    //Section z coordinate (often 0)
    double m_z;
    //Section related vertex identifier (DLL)
	NSString * m_vertexId;
    //Section related edge identifier (DLL)
	NSString * m_edgeId;
    //Section next edge type
	int m_edgeType;
    //Boolean used to know if the section corresponds to a map change
    Boolean m_isMapChanger;
}

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

/*!
 Class used to define an itinerary Instruction.
 */
@interface ISInstruction : NSObject {
    
@private
    
    //Instruction identifier
    NSString * m_instructionId;
    //Instruction label
    NSString * m_instructionInformation;
    //Instruction bounding rect (in ext coordinates)
    CGRect m_boundingRect;
    //Instruction related map identifier
    int m_mapId;
    //An array that contains all the instruction steps (array of ISSection)
    NSMutableArray * m_steps;
    //Related picture url
    NSString * m_pictureUrl;
    //Related overlay url (image to put on top of the picture: could be nil)
    NSString * m_overlayUrl;
    //Distance to arrival
    float m_remainingDistance;
    //Length in meters
    float m_lengthInMeters;
    //Time to arrival
    float m_remainingTime;
    //Duration in seconds
    float m_durationInSeconds;
    //Boolean used to know if the section corresponds to a map change
    Boolean m_isMapChanger;
}

/*!
 Instruction identifier.
 */
@property (nonatomic, retain) NSString * instructionId;

/*!
 Instruction label.
 */
@property (nonatomic, retain) NSString * instructionInformation;

/*!
 Instruction bounding rect (in ext coordinates).
 */
@property (nonatomic, readwrite) CGRect boundingRect;

/*!
 Instruction related map identifier.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 An array that contains all the instruction steps (array of ISSection).
 */
@property (nonatomic, retain) NSMutableArray * steps;

/*!
 Related picture url.
 */
@property (nonatomic, retain) NSString * pictureUrl;

/*!
 Related overlay url (image to put on top of the picture: could be nil).
 */
@property (nonatomic, retain) NSString * overlayUrl;

/*!
 Distance to arrival.
 */
@property (nonatomic, readwrite) float remainingDistance;

/*!
 Length in meters.
 */
@property (nonatomic, readwrite) float lengthInMeters;

/*!
 Time to arrival.
 */
@property (nonatomic, readwrite) float remainingTime;

/*!
 Duration in seconds.
 */
@property (nonatomic, readwrite) float durationInSeconds;

/*!
 Boolean used to know if the section corresponds to a map change.
 */
@property (nonatomic, readwrite) Boolean isMapChanger;

/*!
 Method used to know if the instruction has a related picture.
 @return <b>YES</b> if the instruction has a related picture, otherwise <b>NO</b>.
 */
- (Boolean)hasPicture;

/*!
 Method used to know if the instruction has a related picture url.
 @return <b>YES</b> if the instruction has a related picture url, otherwise <b>NO</b>.
 */
- (Boolean)hasPictureUrl;

@end

/*!
 Class used to define an Itinerary with its instructions.
 */
@interface ISItinerary : NSObject {
    
@private
    
    //Start point
    CGPoint m_startPoint;
    //Start map identifier
    int m_startMapId;
    //End point
    CGPoint m_endPoint;
    //End map identifier
    int m_endMapId;
    //An array that contains all the itinerary instructions (array of ISInstruction)
    NSMutableArray * m_instructions;
    
#pragma mark - Connected
    
    //Time cost
    NSNumber * m_costTime;
    //Distance cost
    NSNumber * m_costDist;
    //Bounding rects
    NSMutableDictionary * m_boundingRects;
    
#pragma mark - Extra
    
    int m_nbSections;
}

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
 An array that contains all the itinerary instructions (array of ISInstruction).
 */
@property (nonatomic, retain) NSMutableArray * instructions;

/*!
 Time cost.
 */
@property (nonatomic, retain) NSNumber * costTime;

/*!
 Distance cost.
 */
@property (nonatomic, retain) NSNumber * costDist;

/*!
 A dictionnary which contains all bounding rect for a specified map (could be nil: offline mode).
 */
@property (nonatomic, retain) NSMutableDictionary * boundingRects;

/*!
 Method used to get the total amout of sections.
 @return The total amout of sections.
 */
- (int)getNbSections;

@end
