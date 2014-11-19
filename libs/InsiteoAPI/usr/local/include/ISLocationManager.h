//
//  ISLocationManager.h
//  lbs
//
//  Created by dev on 13/10/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISLocationManager.h
 ISLocationManager
 */

#import <CoreLocation/CoreLocation.h>

/*!
 Class used to manage CLLocationManager.
 */
@interface ISLocationManager : NSObject <CLLocationManagerDelegate>
{
    
@protected
    
    // Core Location manager
    CLLocationManager * m_locationManager;
}

#pragma mark - Authorization

/*!
 Method used to ask requestWhenInUseAuthorization (for iOS8+).
 */
- (void)requestWhenInUseAuthorization;

/*!
 Method used to ask requestAlwaysAuthorization (for iOS8+).
 */
- (void)requestAlwaysAuthorization;

/*!
 Method used to know if CLAuthorizationStatus is Authorized (or AuthorizedWhenInUse for iOS8+).
 @return If Location is Authorized or not.
 */
- (BOOL)isLocationAuthorized;

@end
