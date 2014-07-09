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
 Renderer used to display ISGeofenceArea (only for debug).
 */
@interface ISGeofenceAreaRenderer : NSObject <ISPRenderer> {
    
@private
    
    //All ISGfxGeofenceArea displayed
    NSMutableDictionary * m_gfxGeofenceAreas;
    //Intern mutex
    NSLock * m_gfxGeofenceAreasLock;
    
#pragma mark - Rendering
    
    //Current render mode
    ISERenderMode m_renderMode;
    //Current displayed layer
    ISLayer * m_layer;
    //Current displayed map
    ISMap * m_currentMap;
    //Boolean used to know if the rendering is enabled
    Boolean m_displayEnabled;
    //Render priority
    int m_priority;
    //RTO listener reference
    id<ISPRTOListener> m_rtoListener;
}

/*!
 Current displayed layer.
 */
@property (assign) ISLayer * layer;

/*!
 All ISGfxGeofenceArea displayed.
 */
@property (nonatomic, retain) NSMutableDictionary * gfxGeofenceAreas;

@end
