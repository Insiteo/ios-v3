//
//  ISGeoMatrix.h
//  ARKitDemo
//
//  Created by INSITEO on 02/05/11.
//  Copyright 2011 Zac White. All rights reserved.
//

/*!
 @header ISGeoMatrix.h
 ISGeoMatrix
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

/*!
 Class used to handle matrix conversion (meters to lat/long and lat/long to meters).
 */
@interface ISGeoMatrix : NSObject {
    
@protected
    
    //H11 matrix argument
    double m_h11;
    //H12 matrix argument
    double m_h12;
    //H21 matrix argument
    double m_h21;
    //H22 matrix argument
    double m_h22;
    //Matrix offset 1
    double m_offset1;
    //Matrix offset 2
    double m_offset2;
    //Matrix determinant
    double m_det;
}

/*!
 H11 matrix argument.
 */
@property (nonatomic, readwrite) double h11;

/*!
 H12 matrix argument.
 */
@property (nonatomic, readwrite) double h12;

/*!
 H21 matrix argument.
 */
@property (nonatomic, readwrite) double h21;

/*!
 H22 matrix argument.
 */
@property (nonatomic, readwrite) double h22;

/*!
 Matrix offset 1.
 */
@property (nonatomic, readwrite) double offset1;

/*!
 Matrix offset 2.
 */
@property (nonatomic, readwrite) double offset2;

/*!
 Matrix determinant.
 */
@property (nonatomic, readwrite) double det;

/*!
 Main constructor.
 @param h11 H11 matrix argument.
 @param h12 H12 matrix argument.
 @param h21 H21 matrix argument.
 @param h22 H22 matrix argument.
 @param offset1 Matrix offset 1.
 @param offset2 Matrix offset 2.
 */
- (id)initWithH11:(double)h11 andH12:(double)h12 andH21:(double)h21 andH22:(double)h22 andOffset1:(double)offset1 andOffset2:(double)offset2;

/*!
 Method used to convert X/Y meters coordinate in lat/long.
 @param x X meters coordinate.
 @param y Y meters coordinate.
 @return Converted lat/long coordinates.
 */
- (CGPoint)toLatLongWithX:(double)x andY:(double)y;

/*!
 Method used to convert lat/long coordinate in meters.
 @param latitude The latitude to convert.
 @param longitude The longitude to convert.
 @return Converted meters coordinates.
 */
- (CGPoint)toMeterWithLatitude:(double)latitude andLongitude:(double)longitude;

/*!
 Method used to convert lat/long span in meters.
 @param latSpan The latitude span to convert.
 @param lonSpan The longitude span to convert.
 @return Converted meters span.
 */
- (CGPoint)spanToMeterFromLatLongWithLatSpan:(double)latSpan andLonSpan:(double)lonSpan;

@end
