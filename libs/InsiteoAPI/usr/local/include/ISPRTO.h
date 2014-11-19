//
//  ISRenderTouchObject.h
//  CommonAPI
//
//  Created by INSITEO on 11/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPRTO.h
 ISPRTO
 */

#import <UIKit/UIKit.h>

#define SET_GLCOLOR_4 ccDrawColor4B

#import "ISTouch.h"
#import "ISMap.h"
#import "ISZonePoi.h"
#import "ISTypes.h"

@class CCLayer;
@class CC3Scene;
@class CC3Node;

/*!
 Enum used to handle Renderer management results.
 @constant NO_MAP_ID The RTO is never displayed.
 @constant ALL_MAP_ID The RTO is always displayed.
 */
typedef enum {
	NO_MAP_ID= -100,
	ALL_MAP_ID,
} ISERTOMapId;

/*!
 Enum used to manage touch event handling results.
 @constant RESULT_NOTHING The object do nothing.
 @constant RESULT_CONSUME The object consume the event.
 @constant RESULT_NOTIFY The object only notify its listeners.
 @constant RESULT_CONSUME_NOTIFY The object consume and notify its listeners.
 */
typedef enum {
	RESULT_CONSUME,
	RESULT_NOTIFY,
	RESULT_CONSUME_NOTIFY,
	RESULT_NOTHING,
} ISETouchObjectResult;

/*!
 Protocol used to represent the beahviour of an RTO (rendering and touch).
 @warning In order to create an RTO with bitmaps, Cocos2d needs to be initialized, otherwise the application will crash.
 @warning In order to use Cocos2d and your own RTO (add to the current CCLayer), you will need to give it a unique identifier which you can get by calling [ISMapView generateCocos2dUniqueId].
 */
@protocol ISPRTO <NSObject>

#pragma mark - General

/*!
 @name General
 */

/*!
 A RTO unique identifier for the current class.
 */
@property (nonatomic, readonly) int rtoId;

/*!
 Related zone association (could be nil).
 */
@property (nonatomic, retain) ISZonePoi * zonePoi;

/*!
 RTO related map identifier (@see ISERTOMapId for general).
 */
@property (nonatomic, readonly) int mapId;

/*!
 Method called to clone an RTO (used when adding an RTO in several zones).
 @return The result cloned RTO.
 */
- (id<ISPRTO>)cloneRTO;

/*!
 Method called show or hide an RTO.
 @param displayEnabled <b>YES</b> for a visible RTO, otherwise <b>NO</b>.
 */
- (void)setDisplayEnabled:(Boolean)displayEnabled;

#pragma mark - Render 2D

/*!
 @name Render 2D
 */

/*!
 Method called to draw an RTO with a ratio and an offset.
 To obtain object position on screen, do (object_position_in_meter.x * aRatio + aOffset.x <b>AND</b> aOffset.y - object_position_in_meter.x * aRatio).
 If this object has no position (ie: ISPRTO is put in a zone), simply draw it at aOffset.
 @param layer The destination Cocos2d layer where this object should be added to.
 @param ratio The real/screen coord ratio, this is used to transform the object's real coords into screen coords.
 @param offset In pixels, the offset from the (0, 0) of the drawing Cocos2d layer that should be added to this object coords.
 @param angle The offset angle in case a rotation should be done. The rotation is relative to the screen center (clockwise).
 @param priority The renderer priority, used as Z by Cocos2d.
 @warning Cocos2d coordinates system is reversed.
 */
- (void)render2DWithLayer:(CCLayer *)layer andRatio:(double)ratio andOffset:(CGPoint)offset andAngle:(float)angle andPriority:(int)priority;

/*!
 Method called to remove an RTO from the Cocos2d layer.
 @param layer The current Cocos2d layer used.
 */
- (void)remove2DFromLayer:(CCLayer *)layer;

/*!
 Method called to initialize RTO resources such as images, labels etc...
 @warning This method will be called on the main thread (UI Thread).
 */
- (void)setResources;

#pragma mark - Touch

/*! 
 @name Touch 
 */

/*!
 Method called when an RTO was touched down.
 @param touch Object that contains iOS touch information.
 @return Touch event handling result.
 @warning Cocos2d coordinates system is reversed.
 */
- (ISETouchObjectResult)onTouchDown:(ISTouch *)touch;

/*!
 Method called when an RTO was touch-moved.
 @param touch Object that contains iOS touch information.
 @return Touch event handling result.
 @warning Cocos2d coordinates system is reversed.
 */
- (ISETouchObjectResult)onTouchMove:(ISTouch *)touch;

/*!
 Method called when an RTO was touched up.
 @param touch Object that contains iOS touch information.
 @return Touch event handling result.
 @warning Cocos2d coordinates system is reversed.
 */
- (ISETouchObjectResult)onTouchUp:(ISTouch *)touch;

@optional

#pragma mark - Render 3D

/*!
 @name Render 3D
 */

/*!
 Current map render mode (2D or 3D).
 */
@property (nonatomic, assign) ISERenderMode renderMode;

/*!
 Zone offset in meters
 */
@property (nonatomic, readwrite) CC3Vector zoneOffset;

/*!
 3D Object to handle in case of 3D rendering.
 */
@property (nonatomic, readonly) CC3Node * object3d;

/*!
 Method called to handle 3D rendering stuff.
 @param scene Current 3D scene.
 @param layer Layer where the RTO is.
 @param map Current displayed map.
 @param ratio Current ratio (depending on the current zoom level).
 @param angle Current angle.
 @param priority The renderer priority, used as Z by Cocos2d.
 */
- (void)render3DWithScene:(CC3Scene *)scene andLayer:(CC3Node *)layer andCurrentMap:(ISMap *)map andRatio:(float)ratio andAngle:(float)angle andPriority:(int)priority;

/*!
 Method called to remove an RTO from the Cocos3d layer.
 @param layer The current Cocos3d layer used.
 */
- (void)remove3DFromLayer:(CC3Node *)layer;

@end
