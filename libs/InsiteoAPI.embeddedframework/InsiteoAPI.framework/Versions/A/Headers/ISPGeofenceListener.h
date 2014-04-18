//
//  ISGeofenceListener.h
//  LocationAPI
//
//  Created by INSITEO on 16/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPGeofenceListener.h
 ISPGeofenceListener
 */

#import <Foundation/Foundation.h>

/*!
 Protocol that describes all geofencing events.
 */
@protocol ISPGeofenceListener <NSObject>

/*!
 Method called when geofencing module has new data available.
 @param enteredZones All zones detected as entered.
 @param stayedZones All zones detected as stayed.
 @param leftZones All zones detected as left.
 */
- (void)onGeofenceDataUpdateWithEnteredZones:(NSArray *)enteredZones andStayedZones:(NSArray *)stayedZones andLeftZones:(NSArray *)leftZones;

/*!
 Method called when geofencing data is reset. This happens when no location was received for a long duration, thus zone detection is not valid anymore.
 */
- (void)onGeofenceDataCleared;

@end
