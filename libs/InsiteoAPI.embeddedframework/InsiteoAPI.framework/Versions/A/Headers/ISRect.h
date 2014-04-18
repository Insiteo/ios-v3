//
//  ISRect.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 15/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISRect.h
 ISRect
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 Class used to represent a rectangle defined by 4 int values (left, top, right, bottom) (ex: 0/0/50/150).
 */
@interface ISRect : NSObject {
    
@protected
    
    //Left value
    int m_left;
    //Left value
    int m_top;
    //Left value
    int m_right;
    //Left value
    int m_bottom;
    
    //Center of the rectangle
    CGPoint m_center;
}

/*!
 Left value.
*/
@property (nonatomic, readwrite) int left;

/*!
 Top value.
 */
@property (nonatomic, readwrite) int top;

/*!
 Right value.
 */
@property (nonatomic, readwrite) int right;

/*!
 Bottom value.
 */
@property (nonatomic, readwrite) int bottom;

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
 @param left Left int value (X coordinate).
 @param top Top int value (Y coordinate).
 @param right Right int value (X coordinate).
 @param bottom Bottom int value (Y coordinate).
 */
- (id)initWithLeft:(int)left andTop:(int)top andRight:(int)right andBottom:(int)bottom;

/*!
 Constructor.
 @param left Left int value (X coordinate).
 @param top Top int value (Y coordinate).
 @param width Rect int width.
 @param height Rect int height.
 */
- (id)initWithLeft:(int)left andTop:(int)top andWidth:(int)width andHeight:(int)height;

/*!
 Constructor.
 @param centerX Rect center X int coordinate.
 @param centerY Rect center Y int coordinate.
 @param width Rect int width.
 @param height Rect int height.
 */
- (id)initWithCenterX:(int)centerX andCenterY:(int)centerY andWidth:(int)width andHeight:(int)height;

/*!
 Constructor.
 @param rect CGRect to use for instantiate the new one.
 */
- (id)initWithCGRect:(CGRect)rect;

/*!
 Static main constructor.
 @param left Left int value (X coordinate).
 @param top Top int value (Y coordinate).
 @param right Right int value (X coordinate).
 @param bottom Bottom int value (Y coordinate).
 */
+ (id)ISRectWithLeft:(int)left andTop:(int)top andRight:(int)right andBottom:(int)bottom;

/*!
 Static constructor.
 @param rect CGRect to use for instantiate the new one.
 */
+ (id)ISRectWithCGRect:(CGRect)rect;

/*!
 Method used to know if the ISRect contains the given point.
 @param point Point to test.
 @return <b>YES</b> if the ISRect contains the point, otherwise <b>NO</b>.
 */
- (Boolean)contains:(CGPoint)point;

/*!
 Method used to know if the ISRect contains the given coordinates.
 @param x X coordinate to test.
 @param y Y coordinate to test.
 @return <b>YES</b> if the ISRect contains the coordinates, otherwise <b>NO</b>.
 */
- (Boolean)containsWithX:(int)x andY:(int)y;

/*!
 Method used to convert the ISRect into CGRect.
 @return The related converted CGRect.
 */
- (CGRect)toCGRect;

/*!
 Method used to get the center x coordinate.
 @return The center x coordinate.
 */
- (int)centerX;

/*!
 Method used to get the center y coordinate.
 @return The center y coordinate.
 */
- (int)centerY;

/*!
 Method used to get ISRect width.
 @return The ISRect width.
 */
- (int)width;

/*!
 Method used to get ISRect height.
 @return The ISRect height.
 */
- (int)height;

/*!
 Method called to offset ISRect.
 @param offset The offset to apply.
 */
- (void)offset:(CGPoint)offset;

/*!
 Method used to know if the ISRect is equal to an specified ISRect.
 @param left Left value of the ISRect to compare.
 @param top Top value of the ISRect to compare.
 @param right Right value of the ISRect to compare.
 @param bottom Bottom value of the ISRect to compare.
 @return <b>YES</b> if the two ISRect are equals, otherwise <b>NO</b>.
 */
- (Boolean)isEqualToISRectWithLeft:(int)left andTop:(int)top andRight:(int)right andBottom:(int)bottom;

/*!
 Method used to know if the ISRect is equal to an specified ISRect.
 @param rect ISRect to compare.
 @return <b>YES</b> if the two ISRect are equals, otherwise <b>NO</b>.
 */
- (Boolean)isEqualToISRect:(ISRect *)rect;

/*!
 Method used to update the ISRect with 4 specified values.
 @param left Left use for update.
 @param top Top value use for update.
 @param right Right value use for update.
 @param bottom Bottom value use for update.
 */
- (void)updateWithLeft:(int)left andTop:(int)top andRight:(int)right andBottom:(int)bottom;

/*!
 Method used to update the ISRect with a specified ISRect.
 @param rect ISRect to use for update.
 */
- (void)updateWithISRect:(ISRect *)rect;

@end
