//
//  ISMapSettings.h
//  LocationAPI
//
//  Created by INSITEO on 15/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMapSettings.h
 ISMapSettings
 */

#import <Foundation/Foundation.h>

#import "ISGeoMatrix.h"

/*!
 Enum used to represent a geofencing coordinate mode.
 @constant XY X/Y coordinate mode (could be meters or pixels etc.).
 @constant WGS84 GPS coordinate mode.
 */
typedef enum CoordinatesMode {
    XY = 0,
    WGS84 = 1
} CoordinatesMode;

/*!
 Class used to represent INSITEO map settings. It contains Geomatrix, scale and map identifier.
 */
@interface ISMapSettings : ISGeoMatrix {
    
@private
    
    //Relative map identifier
    int m_mapId;
    //Relative scale (used for coordinate conversion)
    double m_scaleToMeter;
}

/*!
 Relative map identifier.
 */
@property (nonatomic, readonly) int mapId;

/*!
 Static main constructor.
 @param mapId Relative mapId.
 @param h11 H11 matrix argument.
 @param h12 H12 matrix argument.
 @param h21 H21 matrix argument.
 @param h22 H22 matrix argument.
 @param offset1 Matrix offset 1.
 @param offset2 Matrix offset 2.
 @param scaleToMeter Relative scale (used for coordinate conversion).
 */
+ (id)ISMapSettingsWithMapId:(int)mapId andH11:(double)h11 andH12:(double)h12 andH21:(double)h21 andH22:(double)h22 andOffset1:(double)offset1 andOffset2:(double)offset2 andScaleToMeter:(double)scaleToMeter;

/*!
 Main constructor.
 @param mapId Relative mapId.
 @param h11 H11 matrix argument.
 @param h12 H12 matrix argument.
 @param h21 H21 matrix argument.
 @param h22 H22 matrix argument.
 @param offset1 Matrix offset 1.
 @param offset2 Matrix offset 2.
 @param scaleToMeter Relative scale (used for coordinate conversion).
 */
- (id)initWithMapId:(int)mapId andH11:(double)h11 andH12:(double)h12 andH21:(double)h21 andH22:(double)h22 andOffset1:(double)offset1 andOffset2:(double)offset2 andScaleToMeter:(double)scaleToMeter;

/*!
 Method called to convert X/Y coordinate (in pixels) in meters.
 @param x X pixel coordinate.
 @param y Y pixel coordinate.
 @return A CGPoint containing X/Y meters coordinates.
 */
- (CGPoint)toMeterWithXpx:(float)x andYpx:(float)y;

/*!
 Method called to convert X/Y coordinate (in meters) in pixels.
 @param x X meters coordinate.
 @param y Y meters coordinate.
 @return A CGPoint containing X/Y pixels coordinates.
 */
- (CGPoint)toPixelsWithXm:(float)x andYm:(float)y;

/*!
 Method called to convert X/Y coordinate (in meters) in a specified coordinate mode.
 @param coordMode Wanted coordinate mode to convert to.
 @param x X meters coordinate.
 @param y Y meters coordinate.
 @return A CGPoint containing X/Y coordinates (converted in specified coordinate mode).
 */
- (CGPoint)toExternalCoordsWithCoordMode:(CoordinatesMode)coordMode andXm:(float)x andYm:(float)y;

/*!
 Method called to convert X/Y coordinate (in pixels) in a specified coordinate mode.
 @param coordMode Wanted coordinate mode to convert to.
 @param x X pixel coordinate.
 @param y Y pixel coordinate.
 @return A CGPoint containing X/Y coordinates (converted in specified coordinate mode).
 */
- (CGPoint)toInternalCoordsWithCoordMode:(CoordinatesMode)coordMode andX:(float)x andY:(float)y;

@end
