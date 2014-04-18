//
//  ISEmbeddedLocationProvider.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 18/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

//DLL
#import "EmbeddedLocationProvider.h"

@interface ISEmbeddedLocationProvider : NSObject {
    
@private
    
    Boolean m_isFakeLoc;
    NSArray * m_knownAps;

#pragma mark - DLL Provider
    
    //DLL Provider
    EmbeddedLocationProvider * m_embeddedLocationProvider;
    AvailableSensors * m_availableSensors;
}

@property (nonatomic, assign) EmbeddedLocationProvider * embeddedLocationProvider;

@property (nonatomic, assign) AvailableSensors * availableSensors;

@property (nonatomic, readonly) Boolean isFakeLoc;

- (id)initWithEmbeddedLocationListener:(IEmbeddedLocationListener *)embeddedLocationListener;

- (NSArray *)getVisibleAps:(NSArray *)peripherals;

- (int)initLocationWithLocationFlags:(int)locationFlags andAvailableSensors:(AvailableSensors *)sensors andDefaultMapId:(int)defaultMapId andForceDefaultMap:(Boolean)forceDefautlMap andLocationPath:(NSString *)locationPath;

@end
