//
//  ISPMapListener.h
//  expo_iphone
//
//  Created by INSITEO on 20/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPMapListener.h
 ISPMapListener
 */

#import <UIKit/UIKit.h>

#import "ISGfxZone.h"

/*!
 Protocol used to handle the ISMapViewController events.
 */
@protocol ISPMapListener <NSObject>

/*!
 Method called when an unsupported Zone is clicked.
 @param idZone Zone clicked id.
 @param actionType Related action type to execute.
 @param actionParameter Related action parameter to use.
 */
- (void)onZoneClickedWithZone:(int)idZone andActionType:(int)actionType andActionParameter:(NSString *)actionParameter;

/*!
 Method called when a new map was loaded.
 @param newMapId New map id.
 @param mapName New map name.
 */
- (void)onMapChangeWithNewMapId:(int)newMapId andMapName:(NSString *)mapName;

/*!
 Method called when the map moved.
 */
- (void)onMapMoved;

/*!
 Method called when the map was clicked.
 @param touchPosition Corresponding touched position (in meters).
 */
- (void)onMapClicked:(ISPosition *)touchPosition;

/*!
 Method called when a new zoomLevel is reached.
 @param newZoom New zoom level reached.
 */
- (void)onZoomEnd:(double)newZoom;

@optional

/*!
 Method called when the map was released.
 */
- (void)onMapReleased;

@end
