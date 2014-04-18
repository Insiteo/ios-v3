//
//  ISGeofenceProvider.h
//  LocationAPI
//
//  Created by INSITEO on 14/12/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISGeofenceProvider.h
 ISGeofenceProvider
 */

#import <Foundation/Foundation.h>

#import "ISPLbsModule.h"
#import "ISPGeofenceListener.h"
#import "ISMapSettings.h"

/*!
 This class handles the geofencing process. You can retrieve an instance of it by calling getModule:GEOFENCING on your location provider. It provides a way to be notified when location is detected in a certain area (see ISGeofenceZone), defined on Insiteo servers. To use this class, you just have to call setListener(ISPGeofenceListener), and start the location. The listener will then receive notification each time location enter/stay/leave an area.
 */
@interface ISGeofenceProvider : NSObject <ISPLbsModule> {
    
@private
    
    //Coordinates mode to use
    CoordinatesMode m_coordMode;
    //If no location was received during this time, we notify that a reset of all zone's state have been done
    NSTimeInterval m_timeToReset;
    //Maps settings (geomatrix, map identifier, scale)
    NSMutableDictionary * m_mapsSettings;
    //All geofencing areas to consider
    NSMutableArray * m_areas;
    //Current active geofencing zones (state != UNDEFINED)
    NSMutableArray * m_activeZones;
    //Geofencing notifications listener
    id<ISPGeofenceListener> m_listener;
    
    //Boolean use to know if the provider is initialized
    volatile Boolean m_isInitialized;
    //Internal boolean use to know if the provider is initializing
    volatile Boolean m_isInitializing;
    
    //Internal timer use to handle reset time
    NSTimer * m_resetTimer;
    //Intenr last package version
    int m_lastPackageVersion;
}

/*!
 Geofencing notifications listener.
 */
@property (assign) id<ISPGeofenceListener> listener;

/*!
 Boolean use to know if the provider is initialized.
 */
@property (nonatomic, readonly) Boolean isInitialized;

/*
 All current used geofence areas
 */
@property (nonatomic, readonly) NSArray * areas;

@end
	