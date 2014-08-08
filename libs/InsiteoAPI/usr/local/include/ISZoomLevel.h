//
//  ISZoomLevel.h
//  MapAPI
//
//  Created by INSITEO on 22/10/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISZoomLevel.h
 ISZoomLevel
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "ISRect.h"
#import "ISRectF.h"
#import "ISGfxZone.h"

/*!
 Class used to represent a map zoom level.
 */
@interface ISZoomLevel : NSObject {
    
@private
    
	//ZoomLevel identifier
	int m_level;
    //Tile width to consider
    double m_tileWidthAtZ0;
    //Tile index bounds
    ISRect * m_tilesBounds;
    //Map bounds (in meters)
    ISRectF * m_mapBounds;
    //Map center (in meters)
    CGPoint m_mapCenter;
    //Zones index array
    NSMutableDictionary * m_zonesIndex;
}

/*!
 ZoomLevel identifier.
 */
@property (nonatomic, readwrite) int level;

/*!
 Tile width to consider.
 */
@property (nonatomic, readwrite) double tileWidthAtZ0;

/*!
 Tile index bounds.
 */
@property (nonatomic, retain) ISRect * tilesBounds;

/*!
 Map bounds (in meters).
 */
@property (nonatomic, retain) ISRectF * mapBounds;

/*!
 Map center (in meters).
 */
@property (nonatomic, readwrite) CGPoint mapCenter;

@property (nonatomic, readonly) NSDictionary * zonesIndex;

/*!
 Left value of the tile index bounds.
 */
@property (nonatomic, readonly) int left;

/*!
 Top value of the tile index bounds.
 */
@property (nonatomic, readonly) int top;

/*!
 Right value of the tile index bounds.
 */
@property (nonatomic, readonly) int right;

/*!
 Bottom value of the tile index bounds.
 */
@property (nonatomic, readonly) int bottom;

/*!
 Main constructor.
 @param level Zoom level identifier.
 @param tileBounds Tile index bounds.
 */
- (id)initWithLevel:(int)level andTileBounds:(ISRect *)tileBounds;

/*!
 Method called to add a zone index for this zoom level.
 @param tilePosition The zone index (tile position X/Y).
 @param zone The related zone.
 */
- (void)addZoneIndexWithTilePosition:(CGPoint)tilePosition andZone:(ISGfxZone *)zone;

/*!
 Method called to get the list of zones that are contained in a tile, belonging to this zoomLevel.
 @param x The x index of the tile, starting at 0.
 @param y The y index of the tile, starting at 0.
 @return A list of Zone, or null if no zone is defined for given args.
 */
- (NSArray *)getZonesOnTileWithX:(int)x andY:(int)y;

@end
