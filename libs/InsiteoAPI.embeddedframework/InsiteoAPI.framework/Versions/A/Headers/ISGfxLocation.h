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

#import "ISLocation.h"
#import "ISPRTO.h"

#import "cocos2d.h"
#import "CC3ShadowVolumes.h"

/*!
 Class used to represent a location result.
 */
@interface ISGfxLocation : CCNode <ISPRTO> {
    
@private
    
#pragma mark - Structure
    
    //Related location
    ISLocation * m_location;
    
#pragma mark - Rendering
    
    //RTO unique identifier
    int m_rtoId;
    //Renderer current ratio
	double m_currentRatio;
	//Renderer current offset
	CGPoint m_currentOffset;
    //Current displayed map identifier
    int m_currentMapId;
    //Motion rendering intensity
    double m_motionColorIntensity;
    //Slide wanted new position
    ISPosition * m_wantedPosition;
    //Dot sprite
    CCSprite * m_dot;
    //Compass sprite
    CCSprite * m_compass;
    //Internal rendering accuracy count
    float m_locCircleCount;
    //Location current azimuth
    NSNumber * m_azimuth;
    //Boolean used to store the last device orientation angle
    float m_lastDeviceOrientationAngle;
    //Current rendering mode
    ISERenderMode m_renderMode;
    
#pragma mark - 3D
    
    //3D sphere representation
    CC3SphereNode * m_sphere;
}

/*!
 Related location.
 */
@property (nonatomic, retain) ISLocation * location;

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
 Location dot sprite reference.
 */
@property (nonatomic, retain) CCSprite * dot;

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
