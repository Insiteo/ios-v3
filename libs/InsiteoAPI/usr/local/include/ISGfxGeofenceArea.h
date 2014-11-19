//
//  ISGfxGeofenceArea.h
//  LocationAPI
//
//  Created by dev_iphone on 25/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISGfxGeofenceArea.h
 ISGfxGeofenceArea
 */

#import <Foundation/Foundation.h>

#import "cocos2d.h"

#import "ISPRTO.h"
#import "ISGeofenceArea.h"

/*!
 Class used to display a GeofenceArea.
 */
@interface ISGfxGeofenceArea : CCNode <ISPRTO>

/*!
 Related geofence area.
 */
@property (nonatomic, retain) ISGeofenceArea * area;

/*!
 Main constructor.
 @param area Related geofence area.
 */
- (id)initWithArea:(ISGeofenceArea *)area;

@end
