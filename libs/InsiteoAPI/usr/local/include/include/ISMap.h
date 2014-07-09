//
//  Map.h
//  MapAPI
//
//  Created by INSITEO on 22/10/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISMap.h
 ISMap
 */

#import <Foundation/Foundation.h>

@class ISZoomLevel;
@class ISRect;
@class ISRectF;

#import "ISGeoMatrix.h"

typedef enum {
    ISEMapStartViewModeFitToScreen = 1,
    ISEMapStartViewModePosition
} ISEMapStartViewMode;

/*!
 Class used to represent an INSITEO map entity.
 */
@interface ISMap : NSObject  {
    
@private
    
#pragma mark - Structure
    
    //Map identifier
    int m_mapId;
    //Map type identifier
    int m_typeId;
    //Map name
    NSString * m_name;
    //Floor identifier
    int m_floor;
    //Floor name
    NSString * m_floorName;
    
    //Map scale
	float m_scale;
	//Map zoom levels
	NSMutableArray * m_zoomLevels;
    //Zoom min value
    int m_zoomMin;
    //Zoom max value
    int m_zoomMax;
    
#pragma mark - Behaviour
    
    //Boolean used to know if the map is used only in debug mode (cf Constants.getDebugMode)
    Boolean m_isDebugMap;
    //Index used to sort maps
    int m_sortIndex;
    
#pragma mark - Rendering
    //When launching a map, do we fit to screen or use a certain position ?
    //ISEMapStartViewMode m_startViewMode;
    //Default zoom level
    int m_defaultZoomLevel;
    //Start center position (in meters)
    CGPoint m_startCenterPosition;
    //Map background color
    UIColor * m_backgroundColor;
    //Color for zones border
    UIColor * m_zoneColor;
    //Boolean used to know if we display a background tile to improve the rendering
    Boolean m_displayBackgroundTile;
    //Boolean used to know if we need to fit to screen on load
    Boolean m_fitToScreen;
    
#pragma mark - Rendering Helper
    
    //Boolean used to know if the map is oriented
    Boolean m_isOriented;
    //Map azimuth
	float m_azimuth;
    
    //Boolean used to know if the map is geo referenced
    Boolean m_isGeoReferenced;
    //Map geoMatrix
    ISGeoMatrix * m_geoMatrix;
    
#pragma mark - Touch
    
    //Boolean used to activate auto-slide on the map (slide when flinging map)
    Boolean m_isSlideActive;
    
#pragma mark - Extra
    
    //String extra parameter
    NSString * m_extra1;
    //String extra parameter
    NSString * m_extra2;
    //String extra parameter
    NSString * m_extra3;
    //Float extra parameter
    float m_fExtra1;
    
    //String extra parameter
    NSString * m_dispExtra1;
    //String extra parameter
    NSString * m_dispExtra2;
    //String extra parameter
    NSString * m_dispExtra3;
    //Float extra parameter
    float m_dispFExtra1;
}

/*!
 INSITEO map identifier.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 INSITEO map type identifier.
 */
@property (nonatomic, readwrite) int typeId;

/*!
 INSITEO map name.
 */
@property (nonatomic, retain) NSString * name;

/*!
 INSITEO map floor identifier.
 */
@property (nonatomic, readwrite) int floor;

/*!
 INSITEO map floor name.
 */
@property (nonatomic, retain) NSString * floorName;

/*!
 Boolean used to know if the map is used only in debug mode (cf. ISCommonConstants.h).
 */
@property (nonatomic, readwrite) Boolean isDebugMap;

/*!
 Index used to sort maps.
 */
@property (nonatomic, readwrite) int sortIndex;

/*!
 INSITEO map azimuth.
 */
@property (nonatomic, readwrite) float azimuth;

/*!
 Boolean used to know if the map is oriented.
 */
@property (nonatomic, readwrite) Boolean isOriented;

/*!
 Boolean used to know if the map is geo referenced.
 */
@property (nonatomic, readwrite) Boolean isGeoReferenced;

/*!
 INSITEO map geoMatrix.
 */
@property (nonatomic, retain) ISGeoMatrix * geoMatrix;

/*!
 Map scale.
 */
@property (nonatomic, readwrite) float scale;

/*!
 Map zoom levels.
 */
@property (nonatomic, retain) NSMutableArray * zoomLevels;

/*!
 Zoom min value.
 */
@property (nonatomic, readwrite) int zoomMin;

/*!
 Zoom max value.
 */
@property (nonatomic, readwrite) int zoomMax;

/*!
 When launching a map, do we fit to screen or use a certain position ?
 */
//@property (nonatomic, readwrite) ISEMapStartViewMode startViewMode;

/*!
 Default zoom level.
 */
@property (nonatomic, readwrite) int defaultZoomLevel;

/*!
 Start center position (in meters).
 */
@property (nonatomic, readwrite) CGPoint startCenterPosition;

/*!
 Map background color.
 */
@property (nonatomic, retain) UIColor * backgroundColor;

/*!
 Color for zones border.
 */
@property (nonatomic, retain) UIColor * zoneColor;

/*!
 Boolean used to know if we display a background tile to improve the rendering.
 */
@property (nonatomic, readwrite) Boolean displayBackgroundTile;

/*!
 Boolean used to know if we need to fit to screen on load.
 */
@property (nonatomic, readwrite) Boolean fitToScreen;

/*!
 Boolean used to activate auto-slide on the map (slide when flinging map).
 */
@property (nonatomic, readwrite) Boolean isSlideActive;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra1;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra2;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra3;

/*!
 Float extra parameter.
 */
@property (nonatomic, readwrite) float fExtra1;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * dispExtra1;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * dispExtra2;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * dispExtra3;

/*!
 Float extra parameter.
 */
@property (nonatomic, readwrite) float dispFExtra1;

/*!
 Method used to get a specific map zoom level.
 @param level Zoom level identifer.
 @return Related zoom level.
 */
- (ISZoomLevel *)getZoomLevelWithId:(int)level;

/*!
 Method used to get the map center (in meters) relative to a specific zoom level.
 @param level Zoom level identifer.
 @return Related map center (in meters).
 */
- (NSValue *)getMapCenterWithZoomLevel:(int)level;

/*!
 Method used to get the tile index bounds center relative to a specific zoom level.
 @param level Zoom level identifer.
 @return Related tiles index bounds.
 */
- (ISRect *)getTileBoundsWithZoomLevel:(int)level;

/*!
 Method used to get the map bounds center relative to a specific zoom level.
 @param level Zoom level identifer.
 @return Related map bounds.
 */
- (ISRectF *)getMapBoundsWithZoomLevel:(int)level;

@end
