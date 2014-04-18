//
//  ISPCompassListener.h
//  LocationAPI
//
//  Created by developpeur iphone on 20/11/12.
//
//

/*!
 @header ISPCompassListener.h
 ISPCompassListener
 */

#import <Foundation/Foundation.h>

/*!
 Protocol used to handle compass events.
 */
@protocol ISPCompassListener <NSObject>

/*!
 Method called when the azimuth changed.
 @param azimuthInRad Last azimuth.
 */
- (void)onAzimuthChanged:(float)azimuthInRad;

@end
