//
//  ISGfxGeofenceProvider.h
//  LocationAPI
//
//  Created by dev_iphone on 25/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISGeofenceProvider.h
 ISGfxGeofenceProvider
 */

#import "ISGeofenceProvider.h"

@class ISGeofenceAreaRenderer;
@class ISGeofenceArea;

/*!
 Same as ISGeofenceProvider but with rendering.
 */
@interface ISGfxGeofenceProvider : ISGeofenceProvider {
    
@private
    
    //Geofence area Renderer
    ISGeofenceAreaRenderer * m_geofenceAreaRenderer;
}

/*!
 Geofence area Renderer.
 */
@property (nonatomic, retain) ISGeofenceAreaRenderer * renderer;

@end
