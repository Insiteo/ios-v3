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

#define SET_GLCOLOR_4       ccDrawColor4B
#define SET_GLPOINT_SIZE    ccPointSize
#define OPENGL_VIEW         view
#define OPENGL_DEPTH        GL_DEPTH_COMPONENT16
#define OPENGL_HWVIEW       CC3GLView

#import "ISTouch.h"
#import "ISMap.h"

@class ISLayer;
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
 Enum used to handle different map rendering mod.
 @constant ISERenderMode2D 2D rendering.
 @constant ISERenderMode3D 3D rendering.
 */
typedef enum {
	ISERenderMode2D,
	ISERenderMode3D,
} ISERenderMode;

/*!
 Protocol used to represent the beahviour of an RTO (rendering and touch).
 @warning In order to create an RTO with bitmaps, Cocos2d needs to be initialized, otherwise the application will crash.
 @warning In order to use Cocos2d and your own RTO (add to the current ISLayer), you will need to give it a unique identifier which you can get by calling [ISLayer generateCocos2dUniqueId].
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
 RTO related map identifier (@see ISERTOMapId for general).
 */
@property (nonatomic, readonly) int mapId;

/*!
 Method called to clone an RTO (used when adding an RTO in several zones).
 @return The result cloned RTO.
 */
- (id<ISPRTO>)cloneRTO;

#pragma mark - Rendering
/*!
 @name Rendering
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
- (void)invalidateWithLayer:(ISLayer *)layer andRatio:(double)ratio andOffset:(CGPoint)offset andAngle:(float)angle andPriority:(int)priority;

/*!
 Method called to initialize RTO resources such as images, labels etc...
 @warning This method will be called on the main thread (UI Thread).
*/
- (void)setResources;

/*!
 Method called to remove an RTO from the Cocos2d layer.
 @param layer The current Cocos2d layer used.
 */
- (void)removeFromLayer:(ISLayer *)layer;

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
 Related zone identifier (-1 if no zone).
 */
@property (nonatomic, readwrite) int zoneId;

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
 */
- (void)render3DWithScene:(CC3Scene *)scene andLayer:(CC3Node *)layer andCurrentMap:(ISMap *)map andRatio:(float)ratio andAngle:(float)angle;

@end
