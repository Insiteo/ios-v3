//
//  ISPZone.h
//  CommonAPI
//
//  Created by INSITEO on 27/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPZone.h
 ISPZone
 */

#import <UIKit/UIKit.h>

#import "ISPRTO.h"

/*!
 Protocol used to define a render Zone.
 */
@protocol ISPZone <NSObject>

/*!
 id<ISPZone> map identifier.
 */
@property (nonatomic, readonly) int mapId;

/*!
 id<ISPZone> map scale.
 */
@property (nonatomic, readonly) float zoneHeight;

/*!
 Method called to draw a RTO according to the Zone context.
 @param layer Current Cocos2d layer.
 @param ratio Current map ratio.
 @param offset Current map offset.
 @param angle Current map angle (clockwise).
 @param priority Renderer priority, used to set Z property in Cocos2d.
 @param rto RTO to draw in.
 */
- (void)invalidateWithLayer:(ISLayer *)layer andRatio:(double)ratio andOffset:(CGPoint)offset andAngle:(float)angle andPriority:(int)priority andRTO:(id<ISPRTO>)rto;

@optional

/*!
 Method called to render in 3D a RTO according to the Zone context.
 @param scene Current 3D scene.
 @param layer Layer where the RTO is.
 @param map Current displayed map.
 @param ratio Current ratio (depending on the current zoom level).
 @param rto RTO to draw in.
 @param angle Current angle.
 */
- (void)render3DWithScene:(CC3Scene *)scene andLayer:(CC3Node *)layer andCurrentMap:(id<ISPMapData>)map andRatio:(float)ratio andRTO:(id<ISPRTO>)rto andAngle:(float)angle;

@end
