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
@interface ISMap2DView : ISMapView <UIGestureRecognizerDelegate>

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

#pragma mark - Extra

/*!
 @name Extra
 */

/*!
 Method called to get all the current "visible" zones.
 @return All "visible" zones.
 @warning If a tile is 1px visible, it will return all its zones.
 */
- (NSArray *)getVisibleZones;

@end
