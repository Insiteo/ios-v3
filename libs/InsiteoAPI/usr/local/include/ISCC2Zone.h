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

#import "CCNode.h"

#import "CCDrawNode.h"
#import "ISLayer.h"

@class ISGfxZone;

/*!
 2D zone representation.
 */
@interface ISCC2Zone : CCNode {
    
@private
    
    //Drawnode for lines and dots
    CCDrawNode * m_backgroundNode;
    //Zone line width
    float m_zoneLineWidth;
    //Zone circle width
    float m_zoneCircleWidth;
}

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
- (void)removeFromLayer:(ISLayer *)layer;

@end
