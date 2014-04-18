//
//  ISPosition.h
//  CommonAPI
//
//  Created by INSITEO on 28/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPosition.h
 ISPosition
 */

#import <UIKit/UIKit.h>

/*!
 @"INSTEO_UNKNOW_MAP"
 */
extern NSString * const INSITEO_UNKNOWN_MAP;

/*!
 Class used to represent a position in our map api.
 */
@interface ISPosition : NSObject {
    
@private
    
    //Position coordinates (in meters)
    CGPoint m_coordinates;
    //Relative map id
    int m_mapId;
}

/*!
 Position coordinates (in meters).
 */
@property (nonatomic, readwrite) CGPoint coordinates;

/*!
 Relative map id.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 Main constructor.
 @param x X double coordinate.
 @param y Y double coordinate.
 @param mapId Map identifier to use.
 */
- (id)initWithX:(double)x andY:(double)y andMapId:(int)mapId;

/*!
 Constructor.
 @param position ISPosition to use for instantiate the new one.
 */
- (id)initWithISPosition:(ISPosition *)position;

/*!
 Static main constructor.
 @param x X double coordinate.
 @param y Y double coordinate.
 @param mapId Map identifier to use.
 */
+ (id)ISPositionWithX:(double)x andY:(double)y andMapId:(int)mapId;

/*!
 copy values from position, without new allocation.
 @param position ISPosition to use for update current values.
 */
- (void)setValuesWithPosition:(ISPosition *)position;

/*!
 Method used to offset the ISPosition.
 @param offset CGPoint use to offset the position on X/Y axis.
 */
- (void)offsetWithOffset:(CGPoint)offset;

/*!
 X coordinate accessor.
 */
- (double)x;

/*!
 Y coordinate accessor.
 */
- (double)y;

@end
