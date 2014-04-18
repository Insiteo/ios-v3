//
//  ISGfxItinerary.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 05/04/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISGfxItinerary.h
 ISGfxItinerary
 */

#import "ISItineraryStructures.h"
#import "ISPRTO.h"
#import "ISPItineraryRenderListener.h"

#import "cocos2d.h"
#import "CC3UtilityMeshNodes.h"

/*!
 Class used to represent an itinerary that could be displayed with our map engine.
 */
@interface ISGfxItinerary : CCNode <ISPRTO> {
    
@private
    
#pragma mark - Structure
    
    //Related itinerary data
    ISItinerary * m_itinerary;
    
#pragma mark - Render
    // set to NO to see itinerary immediately
    BOOL m_progressiveDrawing;
    //Current displayed map identifier
    int m_currentMapId;
    //Current rendering ratio
    double m_currentRatio;
    //Current rendering offset
    CGPoint m_currentOffset;
    //Unique RTO identifier
    int m_rtoId;
    //Current step identifier
    int m_currentStepId;
    //Count used to reveal the itinerary
    int m_revealCount;
    //Second count used to reveal the itinerary
    int m_nodeRevealCount;
    //A CCSPrite array that contains all node's pictures
    NSMutableArray * m_pictures;
    //Mutex
    NSLock * m_itineraryLock;
    
#pragma mark - Touch
    
    //Internal point used to handle touch events
    CGPoint m_referencePoint;
    //Last section touched (could be nil)
    ISSection * m_vertexTouched;
    //Listener reference for ISGfxItinerary special touch events
    id<ISPItineraryRenderListener> m_listener;
    //Index of the last instruction touched (could be -1)
    int m_instructionTouched;
    //Touched vertex related instruction index (could be -1)
    int m_vertexTouchedInstruction;
    //Potentionnaly next map position
    ISPosition * m_nextMapPos;
    //Current rendering mode
    ISERenderMode m_renderMode;

#pragma mark - 2D

    //Background node (background fill color)
    CCDrawNode * m_backgroundNode;
    //Foreground node (front fill color)
    CCDrawNode * m_foregroundNode;
    
#pragma mark - 3D
    
    //3D rendering node
    CC3Node * m_cocos3dNode;
    //3D itinerary spheres (used for path)
    NSMutableArray * m_spheres;
    //Start 3D sphere
    CC3SphereNode * m_startSphere;
    //End 3D sphere
    CC3SphereNode * m_endSphere;
}

/*!
 Related itinerary data.
 */
@property (nonatomic, retain) ISItinerary * itinerary;

/*!
 Current displayed map identifier.
 */
@property (nonatomic, readwrite) int currentMapId;

/*!
 Current step identifier.
 */
@property (nonatomic, readwrite) int currentStepId;

/*!
 Color of the itinerary route background.
 */
@property (nonatomic, retain) UIColor * backFillColor;

/*!
 Thickness of the itinerary route background.
 */
@property (nonatomic, readwrite) float backStrokeThickness;

/*!
 Color of the itinerary route foreground.
 */
@property (nonatomic, retain) UIColor * frontFillColor;

/*!
 Thickness of the itinerary route foreground.
 */
@property (nonatomic, readwrite) float frontStrokeThickness;

/*!
 Color of the itinerary route if selected.
 */
@property (nonatomic, retain) UIColor * selectedFillColor;

/*!
 Boolean used to know if the itinerary only draw its path and no additional overlays.
 */
@property (nonatomic, readwrite) Boolean onlyPath;

/*!
 Listener reference for ISGfxItinerary special touch events.
 */
@property (assign) id<ISPItineraryRenderListener> listener;

/*!
 Map view layer.
 */
@property (assign) ISLayer * layer;

/*!
 Main constructor.
 @param itinerary Related itinerary data.
 @param listener Listener reference for ISGfxItinerary special touch events.
 @param backFillColor Color of the itinerary route background.
 @param frontFillColor Color of the itinerary route foreground.
 @param selectedFillColor Color of the itinerary route if selected.
 @param frontStrokeThickness Thickness of the itinerary route foreground.
 @param backStrokeThickness Thickness of the itinerary route background.
 @param onlyPath Boolean used to know if the itinerary only draw its path and no additional overlays.
 @param progDraw Boolean used to know if the itinerary if drawed progressively or not.
 */
- (id)initWithItinerary:(ISItinerary *)itinerary andItineraryRenderListener:(id<ISPItineraryRenderListener>)listener andBackFillColor:(UIColor *)backFillColor andFrontFillColor:(UIColor *)frontFillColor andSelectedFillColor:(UIColor *)selectedFillColor andFrontStrokeThickness:(float)frontStrokeThickness andBackStrokeThickness:(float)backStrokeThickness andOnlyPath:(Boolean)onlyPath andProgressiveDrawing:(Boolean)progDraw;

@end
