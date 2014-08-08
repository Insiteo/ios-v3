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

#import "CCNode.h"
#import "ISPRTO.h"
#import "ISGeofenceArea.h"

/*!
 Class used to display a GeofenceArea.
 */
@interface ISGfxGeofenceArea : CCNode <ISPRTO> {
    
@private
    
    //Related geofence area
    ISGeofenceArea * m_area;
    
#pragma mark - ISPRTO
    
    //Render identifier
    int m_rtoId;
    //Current render ratio
    double m_currentRatio;
	//Renderer current offset
	CGPoint m_currentOffset;
    
#pragma mark - Render
    
    //Intern draw node
    CCDrawNode * m_drawNode;
}

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
