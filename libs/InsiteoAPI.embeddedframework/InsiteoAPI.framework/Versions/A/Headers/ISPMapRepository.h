//
//  ISPMapRepository.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 08/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPMapRepository.h
 PTouchListener
 */

#import <Foundation/Foundation.h>

#import "ISPMapData.h"
#import "ISPZone.h"

/*!
 Protocol used to provide Map and Zone functions (storage, accessors).
 */
@protocol ISPMapRepository <NSObject>

/*!
 The current root map.
 */
@property (nonatomic, retain) id<ISPMapData> mapRoot;

/*!
 Method called to get a specific map with its identifier.
 @param mapId Wanted map identifier.
 @return The related ISPMapData.
 */
- (id<ISPMapData>)getMapWithMapId:(int)mapId;

/*!
 All the maps stored in an NSDictionnary (key <=> map identifier : NSNumber).
 */
@property (nonatomic, retain) NSDictionary * maps;

/*!
 An array containing all sorted maps.
 */
@property (nonatomic, readonly) NSArray * sortedMaps;

/*!
 All maps zones.
 */
@property (nonatomic, retain) NSDictionary * zones;

/*!
 Method called to get a specific zone with its identifier.
 @param zoneId Wanted zone identifier.
 @return The related id<ISPMap>.
 */
- (id<ISPZone>)getZoneWithId:(int)zoneId;

/*!
 Method called to get all the zones into a given map.
 @param mapId Wanted map identifier.
 @return An array of id<ISPZone>.
 */
- (NSArray *)getZonesWithMapId:(int)mapId;

@end
