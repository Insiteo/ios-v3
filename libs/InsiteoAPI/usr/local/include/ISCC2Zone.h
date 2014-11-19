//
//  ISCC2Zone.h
//  MapAPI
//
//  Created by dev_iphone on 17/01/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISCC2Zone.h
 ISCC2Zone
 */

#import "cocos2d.h"

@class ISGfxZone;

/*!
 2D zone representation.
 */
@interface ISCC2Zone : CCNode

/*!
 ISGfxZone zone to use for geometry.
 */
@property (assign) ISGfxZone * zone;

/*!
 Main constructor.
 @param zone ISGfxZone zone to use for geometry.
 */
- (id)initWithZone:(ISGfxZone *)zone;

/*
 Intern method used to remove the node from its parent layer.
 */
- (void)remove2DFromLayer:(CCLayer *)layer;

@end
