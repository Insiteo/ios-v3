//
//  ISItineraryRenderer.h
//  LocationAPI
//
//  Created by INSITEO on 17/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISItineraryRenderer.h
 ISItineraryRenderer
 */

#import <Foundation/Foundation.h>

#import "ISPRenderer.h"
#import "ISPItineraryRenderListener.h"
#import "ISGfxItinerary.h"

/*!
 Class used to handle itinerary rendering.
 */
@interface ISItineraryRenderer : NSObject <ISPRenderer> {
    
@private
    
#pragma mark - General
    
    //Itinerary rendering priority
    int m_priority;
	
#pragma mark - Render
    
    //Boolean used to know if the rendering is activated
	Boolean m_displayEnabled;
    //Current displayed map
   	ISMap * m_currentMap;
    	
#pragma mark - Touch
    
    //Boolean used to know if the touch handling is activated
	Boolean m_touchEnabled;
    //RTO touch listener
    id<ISPRTOListener> m_touchItineraryListener;
    //Listener reference for ISGfxItinerary special touch events
    id<ISPItineraryRenderListener> m_renderListener;
    
#pragma mark - Specific
    
    //Internal semaphore used to handle multithreading issues on itinerary updates
    NSLock * m_itineraryLock;
    //Default itinerary
    ISGfxItinerary * m_itinerary;
    //ISGfxItinerary arrray
    NSMutableArray * m_itineraries;
    //Current itinerary step identifier
    int m_currentStepId;
    //Internal boolean used to know if the layer was moved
	Boolean m_hasMoved;
    //Current rendering mode
    ISERenderMode m_renderMode;
    
#pragma mark - 3D
    
    //3D rendering layer
    CC3Node * m_itinerary3DLayer;
}

/*!
 Current itinerary step identifier.
 */
@property (nonatomic, readwrite) int currentStepId;

/*!
 Listener reference for ISGfxItinerary special touch events.
 */
@property (assign) id<ISPItineraryRenderListener> renderListener;

/*!
 Boolean used to know if an itinerary is available (stored).
 */
@property (nonatomic, readonly) Boolean itineraryAvailable;

/*!
 Map view layer.
 */
@property (assign) ISLayer * layer;

/*!
 Method called to update the displayed itinerary.
 @param gfxItinerary New itinerary to display.
 */
- (void)updateItinerary:(ISGfxItinerary *)gfxItinerary;

/*!
 Method called to change the itinerary route background color.
 @param backFillColor New background color.
 */
- (void)setBackFillColor:(UIColor *)backFillColor;

/*!
 Method called to change the itinerary route background thickness.
 @param backStrokeThickness New background thickness.
 */
- (void)setBackStrokeThickness:(float)backStrokeThickness;

/*!
 Method called to change the itinerary route foreground color.
 @param frontFillColor New foreground color.
 */
- (void)setFrontFillColor:(UIColor *)frontFillColor;

/*!
 Method called to change the itinerary route foreground thickness.
 @param frontStrokeThickness New foreground thickness.
 */
- (void)setFrontStrokeThickness:(float)frontStrokeThickness;

/*!
 Method called to change the itinerary route selected color.
 @param selectedFillColor New selected color.
 */
- (void)setSelectedFillColor:(UIColor *)selectedFillColor;

/*!
 Method called to change the way the route is drawn.
 @param onlyPath Boolean used to know if the itinerary only draw its path and no additional overlays.
 */
- (void)setOnlyPath:(Boolean)onlyPath;

@end
