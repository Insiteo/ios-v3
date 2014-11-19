//
//  ISBeaconRegion.h
//  lbs
//
//  Created by dev on 13/10/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISBeaconRegion.h
 ISBeaconRegion
 */

#import <CoreLocation/CLBeaconRegion.h>

/*!
 Insiteo Beacon UUID.
 */
extern NSString * const INSITEO_BEACON_UUID;

/*!
 Insiteo Beacon Region Identifier.
 */
extern NSString * const INSITEO_BEACON_REGION_IDENTIFIER;

/*!
 Class used to represent a Beacon Region.
 */
@interface ISBeaconRegion : CLBeaconRegion

#pragma mark - Properties

/*!
 Custom Beacon Region label.
 */
@property (nonatomic, retain, readonly) NSString * label;

/*!
 Custom Beacon Region message.
 */
@property (nonatomic, retain) NSString * message;

/*!
 Beacon Region site ID.
 */
@property (nonatomic, assign, readonly) int siteId;

/*!
 Beacon Region time before next entry notification.
 */
@property (nonatomic, assign, readonly) float timer;

#pragma mark - Init

/*!
 Initialize a Beacon Region identified by an proximityUUID, an identifier, a label, a message and a timer.
 @param proximityUUID The unique ID of the beacon being targeted. This value must not be nil.
 @param identifier A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 @param label Custom Beacon Region label.
 @param message Custom Beacon Region message.
 @param timer Timer used to limit on beacon region entry notification if user is in the same beacon region.
 @param siteId The site ID associated with the beacon region.
 */
- (id)initWithProximityUUID:(NSUUID *)proximityUUID identifier:(NSString *)identifier label:(NSString *)label message:(NSString *)message timer:(float)timer siteId:(int)siteId;

/*!
 Initialize a Beacon Region identified by an proximityUUID, an identifier, a major value, a label, a message and a timer.
 @param proximityUUID The unique ID of the beacon being targeted. This value must not be nil.
 @param major The major value that you use to identify one or more beacons.
 @param identifier A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 @param label Custom Beacon Region label.
 @param message Custom Beacon Region message.
 @param timer Timer used to limit on beacon region entry notification if user is in the same beacon region.
 @param siteId The site ID associated with the beacon region.
 */
- (id)initWithProximityUUID:(NSUUID *)proximityUUID major:(CLBeaconMajorValue)major identifier:(NSString *)identifier label:(NSString *)label message:(NSString *)message timer:(float)timer siteId:(int)siteId;

/*!
 Initialize a Beacon Region identified by an proximityUUID, an identifier, a major value, a minor value, a label, a message and a timer.
 @param proximityUUID The unique ID of the beacon being targeted. This value must not be nil.
 @param major The major value that you use to identify one or more beacons.
 @param minor The minor value that you use to identify a specific beacon.
 @param identifier A unique identifier to associate with the returned region object. You use this identifier to differentiate regions within your application. This value must not be nil.
 @param label Custom Beacon Region label.
 @param message Custom Beacon Region message.
 @param timer Timer used to limit on beacon region entry notification if user is in the same beacon region.
 @param siteId The site ID associated with the beacon region.
 */
- (id)initWithProximityUUID:(NSUUID *)proximityUUID major:(CLBeaconMajorValue)major minor:(CLBeaconMinorValue)minor identifier:(NSString *)identifier label:(NSString *)label message:(NSString *)message timer:(float)timer siteId:(int)siteId;

@end
