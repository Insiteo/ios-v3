//
//  ISCC3Zone.h
//  test3d
//
//  Created by dev_iphone on 29/10/13.
//  Copyright (c) 2013 INSITEO. All rights reserved.
//

/*!
 @header ISCC3Zone.h
 ISCC3Zone
 */

#import "CC3MeshNode.h"

@class ISGfxZone;

/*!
 3D zone representation.
 */
@interface ISCC3Zone : CC3MeshNode

/*!
 ISGfxZone zone to use for geometry.
 */
@property (assign) ISGfxZone * zone;

/*!
 Main constructor.
 @param zone ISGfxZone zone to use for geometry.
 @param tagName Cocos tag name to use.
 */
- (id)initWithZone:(ISGfxZone *)zone andTagName:(NSString *)tagName;

@end
