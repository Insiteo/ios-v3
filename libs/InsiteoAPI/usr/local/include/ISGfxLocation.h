//
//  ISGfxLocation.h
//  LocationAPI
//
//  Created by INSITEO on 06/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISGfxLocation.h
 ISGfxLocation
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#import "cocos2d.h"
#import "CC3ShadowVolumes.h"

#import "ISLocation.h"
#import "ISPRTO.h"
#import "ISLocationNode.h"

/*!
 Class used to represent a location result.
 */
@interface ISGfxLocation : CCNode <ISPRTO>

/*!
 Related location.
 */
@property (nonatomic, retain) ISLocation * location;

/*
 Intern 2D rendering node.
 */
@property (nonatomic, retain) ISLocationNode * locationNode;

/*!
 Current displayed map identifier.
 */
@property (nonatomic, readwrite) int currentMapId;

/*!
 Motion rendering intensity.
 */
@property (nonatomic, readwrite) double motionColorIntensity;

/*!
 Location current azimuth.
 */
@property (nonatomic, retain) NSNumber * azimuth;

/*!
 Accuracy rendering color (default: ccc4f(0.0, 0.0, 255.0, 255.0/6.0), none: ccc4f(255.0, 255.0, 255.0, 0.0)).
 */
@property (nonatomic, readwrite) ccColor4F accuracyColor;

/*!
 Main constructor.
 @param location ISLocation to use.
 */
- (id)initWithLocation:(ISLocation *)location;

/*!
 Method called to update the current location.
 @param location ISLocation to use for update.
 */
- (void)updateWithLocation:(ISLocation *)location;

/*!
 Method called to set compass visible or not.
 @param displayEnabled <b>YES</b> if the compass is visible, otherwise <b>NO</b>.
 */
- (void)setCompassDisplayEnabled:(Boolean)displayEnabled;

@end
