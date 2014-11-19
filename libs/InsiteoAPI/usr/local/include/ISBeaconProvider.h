//
//  BeaconProvider.h
//  LocationAPI
//
//  Created by dev_iphone on 10/12/13.
//  Copyright (c) 2013 INSITEO. All rights reserved.
//

/*!
 @header BeaconProvider.h
 BeaconProvider
 */

#import "ISLocationManager.h"

#import "ISBeaconRegion.h"
#import "ISPBeaconListener.h"
#import "ISCommonConstants.h"

#ifdef __IPHONE_7_0
#define USE_IBEACONS
#endif

/*!
 Class used to manage Insiteo Beacon and generic iBeacon.
 */
@interface ISBeaconProvider : ISLocationManager

#pragma mark - Singleton

/*!
 ISBeaconProvider singleton instance.
 */
+ (ISBeaconProvider *)sharedInstance;

#pragma mark - Properties

/*!
 Beacon Regions to monitor.
 */
@property (nonatomic, retain) NSArray * beaconRegions;

/*!
 Beacon listener.
 */
@property (nonatomic, retain) id<ISPBeaconListener> listener;

#pragma mark - Load Beacon Regions

/*!
 Method used to load Beacon Regions from new configuration file.
 */
- (void)refreshBeacons;

#pragma mark - Add Monitoring Regions

/*!
 Method used to start monitoring Beacon Regions.
 */
- (void)start;

/*!
 Method used to add a Beacon Region to monitor.
 @param beaconRegion Beacon Region to monitor.
 */
- (void)addRegion:(ISBeaconRegion *)beaconRegion;

/*!
 Method used to add a Beacon Region to monitor.
 @param beaconRegion Beacon Region to monitor.
 @param shouldDisplay Boolean used to know if app will start and delegate will be notified when user turn on the screen (cf. notifyEntryStateOnDisplay in CLBeaconRegion).
 */
- (void)addRegion:(ISBeaconRegion *)beaconRegion andNotifyEntryStateOnDisplay:(BOOL)shouldDisplay;

#pragma mark - Remove Monitoring Regions

/*!
 Method used to stop monitoring regions.
 */
- (void)stop;

/*!
 Method used to manually remove a Beacon Region.
 @param beaconRegion Beacon Region to remove (i.e. stop monitoring).
 */
- (void)removeRegion:(ISBeaconRegion *)beaconRegion;

@end
