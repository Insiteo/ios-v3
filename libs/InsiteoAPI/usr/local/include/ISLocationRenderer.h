//
//  ISLocationRenderer.h
//  LocationAPI
//
//  Created by INSITEO on 04/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISLocationRenderer.h
 ISLocationRenderer
 */

#import <Foundation/Foundation.h>

extern int const LOCATION_RENDERER_PRIORITY;

#import "ISPRenderer.h"
#import "ISPMotionListener.h"
#import "ISLocation.h"

/*!
 Class used to render locations on the map.
 */
@interface ISLocationRenderer : NSObject <ISPRenderer, ISPMotionListener>

/*!
 Current locations to render.
 */
@property (nonatomic, retain) NSMutableArray * locations;

/*
 Boolean used to know if the location was too degrade to be considered.
 */
@property (nonatomic, readwrite) Boolean locationLost;

/*!
 Location lost render color. (default: ccc3(255.0, 150.0, 0.0), none: ccc3(255.0, 255.0, 255.0)).
 */
@property (nonatomic, readwrite) ccColor3B locationLostColor;

/*!
 Location render color. (default: ccc3(0, 162.0, 255.0), none: ccc3(255.0, 255.0, 255.0)).
 */
@property (nonatomic, readwrite) ccColor3B locationColor;

/*!
 Accuracy rendering color (default: ccc4f(0.0, 0.0, 255.0, 255.0/6.0), none: ccc4f(255.0, 255.0, 255.0, 0.0)).
 */
@property (nonatomic, readwrite) ccColor4F accuracyColor;

/*!
 Map view layer.
 */
@property (assign) CCLayer * layer;

/*!
 Method called to update existing location.
 @param location ISLocation to update.
 */
- (void)updateLocation:(ISLocation *)location;

/*!
 Method called to update the current azimuth.
 @param azimuth New azimuth to consider.
 */
- (void)updateAzimuth:(float)azimuth;

/*!
 Method called to set compass visible or not.
 @param displayEnabled <b>YES</b> if the compass is visible, otherwise <b>NO</b>.
 */
- (void)setCompassDisplayEnabled:(Boolean)displayEnabled;

@end
