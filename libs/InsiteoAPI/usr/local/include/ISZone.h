//
//  ISZone.h
//  lbs
//
//  Created by dev_iphone on 02/07/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISZone.h
 ISZone
 */

#import <Foundation/Foundation.h>

#import "ISPosition.h"

/*!
 Class used to represent an INSITEO zone entity.
 */
@interface ISZone : NSObject

/*!
 Zone identifier.
 */
@property (nonatomic, readwrite) int idZone;

/*!
 Zone GUID.
 */
@property (nonatomic, retain) NSString * guid;

/*!
 Zone type identifier.
 */
@property (nonatomic, readwrite) int typeId;

/*!
 Zone label.
 */
@property (nonatomic, retain) NSString * label;

/*!
 Zone center in meters.
 */
@property (nonatomic, retain) ISPosition * center;

/*!
 ISZone * map identifier.
 */
@property (nonatomic, readonly) int mapId;

/*!
 Z value (to order rendering/touch).
 */
@property (nonatomic, readwrite) int z;

/*!
 ZoomLevel from which the zone is visible.
 */
@property (nonatomic, readwrite) int zoomMin;

/*!
 ZoomLevel from which the zone is hidden.
 */
@property (nonatomic, readwrite) int zoomMax;

/*!
 Zone node points.
 */
@property (nonatomic, retain) NSMutableArray * points;

/*!
 Zone tiles references.
 */
@property (nonatomic, retain) NSMutableArray * tiles;

/*!
 Zone action type (ZoomIn, ZoomOut etc...).
 */
@property (nonatomic, readwrite) int actionType;

/*!
 Zone action parameter (ZoomIn, ZoomOut etc...).
 */
@property (nonatomic, retain) NSString * actionParameter;

/*!
 Zone sort index.
 */
@property (nonatomic, readwrite) int sortIndex;

/*!
 Zone comments (if needed).
 */
@property (nonatomic, retain) NSString * comments;

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
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra4;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra5;

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
 Boolean used to know if the zone handle touch event and if it's displayed.
 */
@property (nonatomic, readwrite) Boolean isHidden;

/*!
 Shelf left side point.
 */
@property (nonatomic, retain) ISPosition * p1;

/*!
 Shelf right side point.
 */
@property (nonatomic, retain) ISPosition * p2;

/*
 Custom geofence width. Used to create custom geofence zones on the fly.
 */
@property (nonatomic, readwrite) float customGeoWidth;

/*!
 Boolean used to know if the zone is a display shelving.
 */
@property (nonatomic, readwrite) Boolean isDisplayShelving;

/*!
 3D zone height (in meters).
 */
@property (nonatomic, readwrite) float zoneHeight;

/*!
 Global zone position max index.
 */
@property (nonatomic, readwrite) int pMax;

/*!
 3D shelves count.
 */
@property (nonatomic, readwrite) int nbShelves;

@end
