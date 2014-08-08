//
//  ISMap2DView.h
//  MapAPI
//
//  Created by dev_iphone on 04/12/13.
//  Copyright (c) 2013 INSITEO. All rights reserved.
//

/*!
 @header ISMap2DView.h
 ISMap2DView
 */

#import "ISMapView.h"

/*!
 Class used to handle 2D map rendering (using Cocos2d).
 */
@interface ISMap2DView : ISMapView <UIGestureRecognizerDelegate> {
    
@private
    
#pragma mark - Cocos
    
    //Cocos rendering scene
    CCScene * m_scene;
    
#pragma mark - Rendering
    
    //Last computed offset
    CGPoint m_currentOffset;
    //Intern last rotation angle
    float m_lastRotationAngle;
}

/*!
 Last computed offset.
 */
@property (nonatomic, readonly) CGPoint currentOffset;

/*!
 Intern last rotation angle.
 */
@property (nonatomic, readonly) float lastRotationAngle;

/*!
 Static constructor.
 @param frame Wanted rendering frame.
 @param mapListener Listener used to handle map events.
 */
+ (ISMap2DView *)map2DViewWithFrame:(CGRect)frame andMapListener:(id<ISPMapListener>)mapListener;

@end
