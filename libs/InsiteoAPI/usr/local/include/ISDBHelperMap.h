//
//  ISDBHelperMap.h
//  CartoAPI
//
//  Created by INSITEO on 06/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISDBHelperMap.h
 ISDBHelperMap
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "ISRODBHelper.h"
#import "ISMap.h"

/*!
 Static class used to handle map SQL requests.
 */
@interface ISDBHelperMap : ISRODBHelper

/*!
 Static method used to get the unique instance of the ISDBHelperMap.
 @return ISDBHelperMap unique instance.
 */
+ (ISDBHelperMap *)instance;

/*!
 Method called to get all zoom levels relative to a specified map identifier and map scale.
 @param map Related map.
 @return An array that contains all concerned zoom levels.
 */
+ (NSMutableArray *)getZoomLevelsWithMap:(ISMap *)map;

/*!
 Method called to get all maps. The debug parameter is used to filter or not the DEBUG maps.
 @param debug A boolean used to know if we filter DEBUG maps.
 @return An array that contains all concerned maps.
 */
+ (NSDictionary *)getMapsWithDebug:(Boolean)debug;

/*!
 Method called to get a specific map.
 @param mapId The map identifier.
 @return The concerned map. Could be nil.
 */
+ (ISMap *)getMapWithMapId:(int)mapId;

/*!
 Method called to the root map identifier.
 @return The root map identifier (int).
 */
+ (int)getMapRootId;

#pragma mark - ZonePoi

/*!
 Method called to get ZonePois related to a specified zone id.
 @param idZone Zone identifier to consider.
 @param external A boolean used to know if associations are external.
 @return All concerned ISZonePoi associations.
 */
+ (NSMutableArray *)getZonePoisForIdZone:(int)idZone andExternal:(Boolean)external;

/*!
 Method called to get ZonePois related to a specified poi id.
 @param idPoi Poi identifier to consider.
 @return All concerned ISZonePoi associations.
 */
+ (NSMutableArray *)getZonePoisForIdPoi:(int)idPoi;

/*!
 Method called to get ZonePois related to a specified poi external id.
 @param extIdPoi Poi external identifier to consider.
 @return All concerned ISZonePoi associations.
 */
+ (NSMutableArray *)getExternalZonePoisForExtIdPoi:(NSString *)extIdPoi;

#pragma mark - ZoneCategory

/*!
 Method called to get ZoneCategory related to a specified zone id.
 @param idZone Zone identifier to consider.
 @param external A boolean used to know if associations are external.
 @return All concerned ISZoneCategory associations.
 */
+ (NSMutableArray *)getZoneCategoriesForIdZone:(int)idZone andExternal:(Boolean)external;

/*!
 Method called to get ZoneCategory related to a specified category id.
 @param idCategory Category identifier to consider.
 @return All concerned ISZoneCategory associations.
 */
+ (NSMutableArray *)getZoneCategoriesForIdCategory:(int)idCategory;

/*!
 Method called to get ZoneCategory related to a specified external category id.
 @param extIdCategory Category external identifier to consider.
 @return All concerned ISZoneCategory associations.
 */
+ (NSMutableArray *)getExternalZoneCategoriesForExtIdCategory:(NSString *)extIdCategory;

@end
