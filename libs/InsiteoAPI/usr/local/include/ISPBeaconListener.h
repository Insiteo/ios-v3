//
//  ISPBeaconListener.h
//  lbs
//
//  Created by dev on 13/10/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISPBeaconListener.h
 ISPBeaconListener
 */

#import "ISBeaconRegion.h"

/*!
 Protocol used to handle Beacon events.
 */
@protocol ISPBeaconListener <NSObject>

@required

#pragma mark - On Beacon Detection

/*!
 Method called when the user enter in a monitored beacon region.
 @param beaconRegion The beacon region the user enters in.
 */
- (void)onEnterBeaconRegion:(ISBeaconRegion *)beaconRegion;

/*!
 Method called when the user quit a monitored beacon region.
 @param beaconRegion The beacon region the user exits.
 */
- (void)onExitBeaconRegion:(ISBeaconRegion *)beaconRegion;

@optional

#pragma mark - Beacon Region Notification management

/*!
 Method used to inform BeaconProvider to notify or not on beacon region entry.
 @param beaconRegion The beacon region the user enters in.
 @return If BeaconProvider should or not notify on entry. Return YES if not implemented, by default.
 */
- (BOOL)shouldPresentLocalNotificationOnBeaconRegionEntry:(ISBeaconRegion *)beaconRegion;

/*!
 Method used to customize the notification on beacon region entry.
 @param beaconRegion The beacon region the user enters in.
 @warning If not implemented, a UILocalNotification is send using the beacon region title and message, by default.
 */
- (void)customizeNotificationOnBeaconRegionEntry:(ISBeaconRegion *)beaconRegion;

/*!
 Method used to get the nearest CLBeacon in BeaconRegion on region entry.
 @param clBeacon The nearest beacon in region, if not error.
 @param beaconRegion The beacon region the user enters in.
 @param error If ranging has failed for region, else nil.
 */
- (void)firstRangedCLBeacon:(CLBeacon *)clBeacon onEntryforRegion:(ISBeaconRegion *)beaconRegion withError:(NSError *)error;

@end
