//
//  ISRectF.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 15/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISRectF.h
 ISRectF
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 Class used to represent a rectangle defined by 4 float values (left, top, right, bottom) (ex: 0.5/0.5/50.0/150.5).
 */
@interface ISRectF : NSObject

/*!
 Left value.
 */
@property (nonatomic, readwrite) float left;

/*!
 Top value.
 */
@property (nonatomic, readwrite) float top;

/*!
 Right value.
 */
@property (nonatomic, readwrite) float right;

/*!
 Bottom value.
 */
@property (nonatomic, readwrite) float bottom;

/*!
 Center of the rectangle.
 */
@property (nonatomic, readwrite) CGPoint center;

/*!
 Top left point.
 */
@property (nonatomic, readonly) CGPoint topLeft;

/*!
 Top right point.
 */
@property (nonatomic, readonly) CGPoint topRight;

/*!
 Bottom left point.
 */
@property (nonatomic, readonly) CGPoint bottomLeft;

/*!
 Bottom right point.
 */
@property (nonatomic, readonly) CGPoint bottomRight;

/*!
 Main constructor.
 @param left Left float value (X coordinate).
 @param top Top float value (Y coordinate).
 @param right Right float value (X coordinate).
 @param bottom Bottom float value (Y coordinate).
 */
- (id)initWithLeft:(float)left andTop:(float)top andRight:(float)right andBottom:(float)bottom;

/*!
 Constructor.
 @param left Left float value (X coordinate).
 @param top Top float value (Y coordinate).
 @param width Rect float width.
 @param height Rect float height.
 */
- (id)initWithLeft:(float)left andTop:(float)top andWidth:(float)width andHeight:(float)height;

/*!
 Static main constructor.
 @param left Left float value (X coordinate).
 @param top Top float value (Y coordinate).
 @param right Right float value (X coordinate).
 @param bottom Bottom float value (Y coordinate).
 */
+ (id)ISRectFWithLeft:(float)left andTop:(float)top andRight:(float)right andBottom:(float)bottom;

/*!
 Static constructor.
 @param rect CGRect to use for instantiate the new one.
 */
+ (id)ISRectFWithCGRect:(CGRect)rect;

/*!
 Method used to know if the ISRectF contains the given point.
 @param point Point to test.
 @return <b>YES</b> if the ISRectF contains the point, otherwise <b>NO</b>.
 */
- (Boolean)contains:(CGPoint)point;

/*!
 Method used to know if the ISRectF contains the given coordinates.
 @param x X coordinate to test.
 @param y Y coordinate to test.
 @return <b>YES</b> if the ISRectF contains the coordinates, otherwise <b>NO</b>.
 */
- (Boolean)containsWithX:(float)x andY:(float)y;

/*!
 Method used to convert the ISRectF into CGRect.
 @return The related converted CGRect.
 */
- (CGRect)toCGRect;

/*!
 Method used to get the center y coordinate.
 @return The center y coordinate.
 */
- (float)centerX;

/*!
 Method used to get the center y coordinate.
 @return The center y coordinate.
 */
- (float)centerY;

/*!
 Method used to get ISRectF width.
 @return The ISRect width.
 */
- (float)width;

/*!
 Method used to get ISRectF height.
 @return The ISRect height.
 */
- (float)height;

@end
