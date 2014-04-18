//
//  ISTouch.h
//  MapAPI
//
//  Created by Baptiste LE GUELVOUIT on 26/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISTouch.h
 ISTouch
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define CC3RayZero CC3RayMake(0, 0, 0, 0, 0, 0)

#import "ISLayer.h"
#import "CC3Foundation.h"

/*!
 Class used to store iOS touch information such as UIEvent and relative ISLayer.
 */
@interface ISTouch : NSObject {
    
@private
    
    //An array which contains all touches
    NSMutableArray * m_touches;
    //Original touchs (with no rotation or tilt computation)
    NSMutableArray * m_originalTouches;
    //Relative UIEvent
    UIEvent * m_event;
    //CC3Ray array
    NSMutableArray * m_touchRays;
    //CC3Vector array
    NSMutableArray * m_vectors;
}

/*!
 An array which contains all touches.
 */
@property (nonatomic, retain) NSMutableArray * touches;

/*!
 An array which contains all original touches (whithout transformation like rotation or tilt).
 */
@property (nonatomic, retain) NSMutableArray * originalTouches;

/*!
 Relative UIEvent.
 */
@property (nonatomic, retain) UIEvent * event;

/*!
 First (finger) touch point.
 */
@property (nonatomic, readonly) CGPoint firstPoint;

/*!
 Second (finger) touch point.
 */
@property (nonatomic, readonly) CGPoint secondPoint;

/*!
 First (finger) touch point.
 */
@property (nonatomic, readonly) CGPoint firstOriginalPoint;

/*!
 Second (finger) touch point.
 */
@property (nonatomic, readonly) CGPoint secondOriginalPoint;

#pragma mark - 3D

/*!
 First (finger) touch ray.
 */
@property (nonatomic, readonly) NSValue * firstRay;

/*!
 Second (finger) touch ray.
 */
@property (nonatomic, readonly) NSValue * secondRay;

/*!
 First (finger) touch ray.
 */
@property (nonatomic, readonly) NSValue * firstVector;

/*!
 Second (finger) touch ray.
 */
@property (nonatomic, readonly) NSValue * secondVector;

/*!
 Relative touched ISLayer.
 */
@property (assign) ISLayer * layer;

/*!
 All 3D touch rays.
 */
@property (nonatomic, retain) NSMutableArray * touchRays;

/*!
 All 3D touch vectors.
 */
@property (nonatomic, retain) NSMutableArray * vectors;

/*!
 Main constructor.
 @param event Relative UIEvent.
 @param view Relative touched UIView.
 @param layer Relative touched ISLayer.
 */
- (id)initWithEvent:(UIEvent *)event andView:(UIView *)view andLayer:(ISLayer *)layer;

/*!
 Second constructor.
 @param event Relative UIEvent.
 @param touches An array which contains all touches (finger).
 @param originalTouches An array which contains all original touches (finger).
 @param layer Relative touched ISLayer.
 @param touchRays An array which contains all 3D touch rays.
 @param vectors An array which contains all 3D touch vectors.
 */
- (id)initWithEvent:(UIEvent *)event andTouches:(NSMutableArray *)touches andOriginalTouches:(NSMutableArray *)originalTouches andLayer:(ISLayer *)layer andTouchRays:(NSMutableArray *)touchRays andVectors:(NSMutableArray *)vectors;

/*!
 Static copy constructor.
 @param touch ISTouch to copy.
 */
+ (id)ISTouchWithISTouch:(ISTouch *)touch;

/*!
 Method called to rotate all touch information.
 @param angle Angle to use to rotate.
 @param center Relative rotation center.
 */
- (ISTouch *)rotateWithAngle:(float)angle andCenter:(CGPoint)center;

/*!
 Static method used to convert a point in a tilt coordinates.
 @param layer Point related layer.
 @param point The point to convert.
 @return The tilted point
 */
+ (CGPoint)tiltPointWithLayer:(ISLayer *)layer andPoint:(CGPoint)point;

/*!
 Static method used to convert a tilted point in normal coordinates.
 @param layer Point related layer.
 @param point The point to convert.
 @return The untilted point
 */
+ (CGPoint)untiltPointWithLayer:(ISLayer *)layer andPoint:(CGPoint)point;

@end
