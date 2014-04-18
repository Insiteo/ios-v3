//
//  ISMapData.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 09/05/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMapData.h
 ISMapData
 */

#import <Foundation/Foundation.h>

#import "ISGeoMatrix.h"

/*!
 Class used to represent an INSITEO maps with its geoloc attributes and identifiers.
 */
@protocol ISPMapData <NSObject>

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

@end
