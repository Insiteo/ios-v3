//
//  ISZone.h
//  lbs
//
//  Created by dev_iphone on 02/07/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISZone.h
 ISZone
 */

#import <Foundation/Foundation.h>

#import "ISPosition.h"

/*!
 Class used to represent an INSITEO zone entity.
 */
@interface ISZone : NSObject {
    
#pragma mark - Structure
	
    //Zone identifier
	int m_idZone;
    //Zone GUID
    NSString * m_guid;
    //Zone type identifier
    int m_typeId;
    //Zone label
    NSString * m_label;
    
#pragma mark - Positionning
    
	//Zone position (x, y and map Id)
    ISPosition * m_center;
    //Z value (to order rendering/touch)
    int m_z;
    //ZoomLevel min where the zone appears
    int m_zoomMin;
    //ZoomLevel max where the zone appears
    int m_zoomMax;
    
    //Zone node points
    NSMutableArray * m_points;
    //Zone tiles references
    NSMutableArray * m_tiles;

#pragma mark - Action
    
    //Zone action type (ZoomIn, ZoomOut etc...)
	int m_actionType;
    //Zone action parameter
	NSString * m_actionParameter;
    
#pragma mark - Behaviour
    
    //Sort index
    int m_sortIndex;
    //Zone comments (if needed)
    NSString * m_comments;
    
#pragma mark - Extra
    
    //String extra parameter
    NSString * m_extra1;
    //String extra parameter
    NSString * m_extra2;
    //String extra parameter
    NSString * m_extra3;
    //String extra parameter
    NSString * m_extra4;
    //String extra parameter
    NSString * m_extra5;
    //Float extra parameter
    float m_fExtra1;
    
    //String extra parameter
    NSString * m_dispExtra1;
    //String extra parameter
    NSString * m_dispExtra2;
    //String extra parameter
    NSString * m_dispExtra3;
    //Float extra parameter
    float m_dispFExtra1;
    
    //Boolean used to know if the zone handle touch event and if it's displayed
    Boolean m_isHidden;
    
#pragma mark - 3D/GeoPush
    
    //3D first front point
    ISPosition * m_p1;
    //3D second front point
    ISPosition * m_p2;
    //
    float m_customGeoWidth;
    //
    Boolean m_isDisplayShelving;
}

/*!
 Zone identifier.
 */
@property (nonatomic, readwrite) int idZone;

/*!
 Zone GUID.
 */
@property (nonatomic, retain) NSString * guid;

/*!
 Zone type identifier.
 */
@property (nonatomic, readwrite) int typeId;

/*!
 Zone label.
 */
@property (nonatomic, retain) NSString * label;

/*!
 Zone center in meters.
 */
@property (nonatomic, retain) ISPosition * center;

/*!
 ISZone * map identifier.
 */
@property (nonatomic, readonly) int mapId;

/*!
 Z value (to order rendering/touch).
 */
@property (nonatomic, readwrite) int z;

/*!
 ZoomLevel from which the zone is visible.
 */
@property (nonatomic, readwrite) int zoomMin;

/*!
 ZoomLevel from which the zone is hidden.
 */
@property (nonatomic, readwrite) int zoomMax;

/*!
 Zone node points.
 */
@property (nonatomic, retain) NSMutableArray * points;

/*!
 Zone tiles references.
 */
@property (nonatomic, retain) NSMutableArray * tiles;

/*!
 Zone action type (ZoomIn, ZoomOut etc...).
 */
@property (nonatomic, readwrite) int actionType;

/*!
 Zone action parameter (ZoomIn, ZoomOut etc...).
 */
@property (nonatomic, retain) NSString * actionParameter;

/*!
 Zone sort index.
 */
@property (nonatomic, readwrite) int sortIndex;

/*!
 Zone comments (if needed).
 */
@property (nonatomic, retain) NSString * comments;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra1;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra2;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra3;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra4;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * extra5;

/*!
 Float extra parameter.
 */
@property (nonatomic, readwrite) float fExtra1;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * dispExtra1;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * dispExtra2;

/*!
 String extra parameter.
 */
@property (nonatomic, retain) NSString * dispExtra3;

/*!
 Float extra parameter.
 */
@property (nonatomic, readwrite) float dispFExtra1;

/*!
 Boolean used to know if the zone handle touch event and if it's displayed.
 */
@property (nonatomic, readwrite) Boolean isHidden;

/*!
 Shelf left side point.
 */
@property (nonatomic, retain) ISPosition * p1;

/*!
 Shelf right side point.
 */
@property (nonatomic, retain) ISPosition * p2;

/*
 Custom geofence width. Used to create custom geofence zones on the fly.
 */
@property (nonatomic, readwrite) float customGeoWidth;

/*!
 Boolean used to know if the zone is a display shelving.
 */
@property (nonatomic, readwrite) Boolean isDisplayShelving;

@end
