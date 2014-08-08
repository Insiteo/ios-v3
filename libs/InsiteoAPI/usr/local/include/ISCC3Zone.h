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

#import "cocos2d.h"
#import "ISMap.h"

@class ISGfxZone;

/*!
 3D zone representation.
 */
@interface ISCC3Zone : CC3MeshNode {
    
@private
    
    //3D rendering color
    ccColor3B m_zoneColor;
}

/*!
 ISGfxZone zone to use for geometry.
 */
@property (assign) ISGfxZone * zone;

/*!
 3D rendering color.
 */
@property (nonatomic, readwrite) ccColor3B zoneColor;

/*!
 Main constructor.
 @param zone ISGfxZone zone to use for geometry.
 @param tagName Cocos tag name to use.
 @param zoneColor 3D rendering color.
 */
- (id)initWithZone:(ISGfxZone *)zone andTagName:(NSString *)tagName andColor:(ccColor3B)zoneColor;

@end
