//
//  ISPRenderer.h
//  CommonAPI
//
//  Created by INSITEO on 29/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPRenderer.h
 ISPRenderer
 */

#import <UIKit/UIKit.h>

#import "ISPRTO.h"
#import "ISPRTOListener.h"
#import "ISTouch.h"
#import "ISMap.h"

@class CCLayer;
@class CC3Scene;

/*!
 Protocol used to represent a map Renderer.
 */
@protocol ISPRenderer <NSObject>

#pragma mark - General
/*!
 @name group General
 */

/*!
 The Renderer key (depending of the RTO classe).
 */
@property (nonatomic, readonly) NSString * rtoClass;

/*!
 The current renderer priority (vertexZ equivalent in Cocos2d).
 */
@property (nonatomic, readwrite) int priority;

/*!
 Current map setter.
 */
@property (nonatomic, retain) ISMap * currentMap;

#pragma mark - RTO Management
/*!
 @name RTO Management
 */

/*!
 Method called to add an RTO.
 @param rto RTO to add.
 @return A boolean if the RTO was successfully added.
 */
- (Boolean)addRTO:(id<ISPRTO>)rto;

/*!
 Method called to add a RTO to a specific Zone.
 @param rto RTO to add.
 @param zoneId Zone identifier to clear.
 @return A boolean if the RTO was successfully added.
 */
- (Boolean)addRTO:(id<ISPRTO>)rto inZone:(int)zoneId;

/*!
 Method called to remove an RTO.
 @param rto RTO to remove.
 */
- (void)removeRTO:(id<ISPRTO>)rto;

/*!
 Method called to remove a RTO from a specific Zone.
 @param rto RTO to remove.
 @param zoneId Zone identifier to clear.
 */
- (void)removeRTO:(id<ISPRTO>)rto fromZone:(int)zoneId;

/*!
 Method called to clear the Renderer.
 */
- (void)clear;

/*!
 Method called to clear all the RTO of a specific Zone.
 @param zoneId Zone identifier to clear.
 */
- (void)clearZone:(int)zoneId;

#pragma mark - Rendering
/*!
 @name Rendering
 */

/*!
 Method called to draw the Renderer content (ie: ISPRTO for more information).
 To obtain object position on screen, do (object_position_in_meter.x * aRatio + aOffset.x <b>AND</b> aOffset.y - object_position_in_meter.x * aRatio).
 @param layer The destination Cocos2d layer where this object should be added to.
 @param ratio The real/screen coord ratio, this is used to transform the object's real coords into screen coords.
 @param offset In pixels, the offset from the (0, 0) of the drawing Cocos2d layer that should be added to this object coords.
 @param angle The offset angle in case a rotation should be done. The rotation is relative to the screen center (clockwise).
 @warning Cocos2d coordinates system is reversed.
 */
- (void)render2DWithLayer:(CCLayer *)layer andRatio:(double)ratio andOffset:(CGPoint)offset andAngle:(float)angle;

/*!
 Boolean used to know if the Renderer rendering is activated.
 */
@property (nonatomic, readwrite) Boolean displayEnabled;

#pragma mark - Touch

/*!
 @name Touch
 */

/*!
 Boolean used to know if the Renderer touch is activated.
 */
@property (nonatomic, readwrite) Boolean touchEnabled;

/*!
 Related renderer touch listener.
 */
@property (assign) id<ISPRTOListener> rtoListener;

/*!
 Method called when a touch down event occured.
 @param touch Object that contains iOS touch information.
 @return <b>YES</b> if it consume the event, else <b>NO</b>.
 @warning Cocos2d coordinates system is reversed.
 */
- (Boolean)onTouchDown:(ISTouch *)touch;

/*!
 Method called when a move event occured.
 @param touch Object that contains iOS touch information.
 @return <b>YES</b> if it consume the event, else <b>NO</b>.
 @warning Cocos2d coordinates system is reversed.
 */
- (Boolean)onTouchMove:(ISTouch *)touch;

/*!
 Method called when a touch up event occured.
 @param touch Object that contains iOS touch information.
 @return <b>YES</b> if it consume the event, else <b>NO</b>.
 @warning Cocos2d coordinates system is reversed.
 */
- (Boolean)onTouchUp:(ISTouch *)touch;

#pragma mark - 3D

/*!
 @name 3D
 */

@optional

/*!
 Current map render mode (2D or 3D).
 */
@property (nonatomic, assign) ISERenderMode renderMode;

/*!
 Method called to handle 3D rendering stuff.
 @param scene Current 3D scene.
 @param ratio Current ratio (depending on the current zoom level).
 @param angle Current angle.
 */
- (void)render3DWithScene:(CC3Scene *)scene andRatio:(float)ratio andAngle:(float)angle;

/*!
 Method used to get all RTO from a given zone identifier.
 @param zoneId Corresponding zone identifier.
 @return An array of all linked RTO (could be nil).
 */
- (NSArray *)getRTOsWithZoneId:(int)zoneId;

@end
