//
//  ISGeofenceAreaRenderer.h
//  LocationAPI
//
//  Created by dev_iphone on 25/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISGeofenceAreaRenderer.h
 ISGeofenceAreaRenderer
 */

#import <Foundation/Foundation.h>

#import "ISPRenderer.h"

/*!
 Renderer used to display ISGeofenceArea (only for debug and in 2D).
 */
@interface ISGeofenceAreaRenderer : NSObject <ISPRenderer>

/*!
 Current displayed layer.
 */
@property (assign) CCLayer * layer;

/*!
 All ISGfxGeofenceArea displayed.
 */
@property (nonatomic, retain) NSMutableDictionary * gfxGeofenceAreas;

@end
