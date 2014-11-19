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

#import "cocos2d.h"
#import "CC3UtilityMeshNodes.h"

@class ISItineraryProvider;

#import "ISItinerary.h"
#import "ISPRTO.h"
#import "ISPItineraryRenderListener.h"

/*!
 Class used to represent an itinerary that could be displayed with our map engine.
 */
@interface ISGfxItinerary : CCNode <ISPRTO>

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
@property (assign) CCLayer * layer;

/*!
 Current 3D scene (for 3D rendering only).
 */
@property (assign) CC3Scene * scene;

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
