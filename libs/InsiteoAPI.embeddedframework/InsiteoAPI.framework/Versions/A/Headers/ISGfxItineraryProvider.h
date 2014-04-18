//
//  ISGfxItineraryProvider.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 06/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISGfxItineraryProvider.h
 ISGfxItineraryProvider
 */

#import "ISItineraryProvider.h"

#import "ISItineraryRenderer.h"

/*!
 Class used to manage and RENDER Itinerary requests.
 */
@interface ISGfxItineraryProvider : ISItineraryProvider {
    
@private
    
    //Itinerary map renderer
	ISItineraryRenderer * m_itineraryRenderer;
    //Back fill color
    UIColor * m_backFillColor;
    //Back stroke thicknesss
    float m_backStrokeThickness;
    //Front fill color
    UIColor * m_frontFillColor;
    //Front stroke thickness
    float m_frontStrokeThickness;
    //Selected fill color
    UIColor * m_selectedFillColor;
    //Boolean used to know if only the path is drawn
    Boolean m_onlyPath;
}

/*!
 Color of the itinerary route background.
 */
@property (nonatomic, readwrite) Boolean progressiveDrawing;

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
 Boolean used to know if only the path is drawn.
 */
@property (nonatomic, readwrite) Boolean onlyPath;

/*!
 Itinerary Renderer.
 */
@property (nonatomic, retain) ISItineraryRenderer * renderer;

@end
