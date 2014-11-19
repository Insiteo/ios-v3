//
//  ISEmbeddedLocationProvider.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 18/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "EmbeddedLocationProvider.h"

@interface ISEmbeddedLocationProvider : NSObject

@property (nonatomic, assign) EmbeddedLocationProvider * embeddedLocationProvider;

@property (nonatomic, assign) AvailableSensors * availableSensors;

@property (nonatomic, readonly) Boolean isFakeLoc;

- (id)initWithEmbeddedLocationListener:(IEmbeddedLocationListener *)embeddedLocationListener;

- (int)initLocationWithLocationFlags:(int)locationFlags andAvailableSensors:(AvailableSensors *)sensors andDefaultMapId:(int)defaultMapId andForceDefaultMap:(Boolean)forceDefautlMap andLocationPath:(NSString *)locationPath andLogsPath:(NSString *)logsPath;

@end
