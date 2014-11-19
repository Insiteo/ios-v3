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
#import <UIKit/UIKit.h>

@class ISZoomLevel;
@class ISRect;
@class ISRectF;
@class ISGeoMatrix;

typedef enum {
    ISEMapStartViewModeFitToScreen = 1,
    ISEMapStartViewModePosition
} ISEMapStartViewMode;

/*!
 Class used to represent an INSITEO map entity.
 */
@interface ISMap : NSObject

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

/*
 Intern method used to clear map zoom levels (use on resetMap).
 */
- (void)clearZoomLevelsIndexes;

@end
