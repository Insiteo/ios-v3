//
//  ISTileIndex.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 22/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 Class used to represent a Tile index (mapId, zoomLevel, x, y).
 */
@interface ISTileIndex : NSObject {
    
@private
    
    //Tile map identifier
    int m_mapId;
    //Tile zoom level
    int m_zoomLevel;
    //Tile X coodinate
    int m_x;
    //Tile Y coordinate
    int m_y;
}

/*!
 Tile map identifier.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 Tile zoom level.
 */
@property (nonatomic, readwrite) int zoomLevel;

/*!
 Tile X coordinate.
 */
@property (nonatomic, readwrite) int x;

/*!
 Tile Y coordinate.
 */
@property (nonatomic, readwrite) int y;

/*!
 Main constructor.
 @param mapId Tile map identifier.
 @param zoomLevel Tile zoom level.
 @param x Tile X coodinate.
 @param y Tile Y coodinate.
 */
- (id)initWithMapId:(int)mapId andZoomLevel:(int)zoomLevel andX:(int)x andY:(int)y;

/*!
 Static constructor.
 @param mapId Tile map identifier.
 @param zoomLevel Tile zoom level.
 @param x Tile X coodinate.
 @param y Tile Y coodinate.
 */
+ (id)ISTileIndexWithMapId:(int)mapId andZoomLevel:(int)zoomLevel andX:(int)x andY:(int)y;

@end
