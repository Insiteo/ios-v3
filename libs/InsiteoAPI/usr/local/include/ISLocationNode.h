//
//  ISLocationNode.h
//  lbs
//
//  Created by dev_iphone on 24/07/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISLocationNode.h
 ISLocationNode
 */


#import "cocos2d.h"

#import <CoreLocation/CoreLocation.h>

/*!
 Class used to handle cocos2d rendering of an ISGfxLocation.
 */
@interface ISLocationNode : CCNode {
    
@private
    
    //Dot sprite
    CCSprite * m_dot;
    //Compass sprite
    CCSprite * m_compass;
}

/*!
 Location dot cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * dot;

/*!
 Location compass cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * compass;

@end
