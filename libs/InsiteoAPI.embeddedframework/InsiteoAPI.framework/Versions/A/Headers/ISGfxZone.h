//
//  ISGfxZone.h
//  MapAPI
//
//  Created by INSITEO on 05/11/10.
//  Copyright 2010 Insiteo. All rights reserved.
//

/*!
 @header ISGfxZone.h
 ISGfxZone
 */

#import <Foundation/Foundation.h>

#import "cocos2d.h"
#import "ISPosition.h"
#import "ISPZone.h"
#import "ISPRTO.h"
#import "ISCC3Zone.h"
#import "ISCC2Zone.h"

/*!
 Class used to represent a Map Zone.
 */
@interface ISGfxZone : NSObject <ISPZone, ISPRTO> {
    
@private
    
#pragma mark - Structure
	
    //Zone identifier
	int m_idZone;
    //Zone GUID
    NSString * m_guid;
    //Zone type identifier
    int m_typeId;
    //Zone name
    NSString * m_name;
    
#pragma mark - Positionning
    
	//Zone position (x, y and map Id)
    ISPosition * m_metersPosition;
    //Z value (to order rendering/touch)
    int m_z;
    //ZoomLevel min where the zone appears
    int m_zoomMin;
    //ZoomLevel max where the zone appears
    int m_zoomMax;
    
#pragma mark - Rendering
    
    //Zone node points
    NSMutableArray * m_points;
    //Zone tiles references
    NSMutableArray * m_tiles;
    //Boolean used to know if the zone handle touch event and if it's displayed
    Boolean m_isHidden;
    
    //Cocos2d
    ISCC2Zone * m_cocos2dNode;
    
    //Cocos3d
    ISCC3Zone * m_cocos3dNode;
    CC3Node * m_shelfNode;
    
#pragma mark - Touch
    
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
    
#pragma mark - Specific
    
    //Boolean used to know if the zone was touched
    Boolean m_isTouched;
    //Boolean used to know if the zone needs to be displayed
    Boolean m_needToBeDisplayed;
    //Internal touch reference point
    CGPoint m_referencePoint;
    
    //Cocos2d unique identifier
    int m_rtoId;
    //Rendering last offset
    CGPoint m_lastOffset;
    //Rendering last ratio
    float m_lastRatio;
    //Zone rendering color
    ccColor4B m_zoneColor;
    
#pragma mark - 3D
    
    //Current rendering mode
    ISERenderMode m_renderMode;
    //Intern 3D intersection used to get the real touched zone
    CC3MeshIntersection m_3dIntersection;
    
    //3D shelf count
    int m_nbShelf;
    //3D first front point
    CGPoint m_p1;
    //3D second front point
    CGPoint m_p2;
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
 Zone name.
 */
@property (nonatomic, retain) NSString * name;

/*!
 Zone position (in meters).
 */
@property (nonatomic, retain) ISPosition * metersPosition;

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
 Boolean used to know if the zone needs to be displayed.
 */
@property (nonatomic, readwrite) Boolean needToBeDisplayed;

/*!
 Boolean used to know if the zone is touched.
 */
@property (nonatomic, readwrite) Boolean isTouched;

/*!
 Zone rendering color.
 */
@property (nonatomic, readwrite) ccColor4B zoneColor;

/*!
 Boolean used to know if the zone handle touch event and if it's displayed.
 */
@property (nonatomic, readwrite) Boolean isHidden;

/*!
 Last rendering ratio.
 */
@property (nonatomic, readwrite) float lastRatio;

/*!
 Last rendering offset.
 */
@property (nonatomic, readwrite) CGPoint lastOffset;

/*
 Intern 3D intersection used to get the real touched zone.
 */
@property (nonatomic, readonly) CC3MeshIntersection intersection;

/*!
 3D shelf count.
 */
@property (nonatomic, readwrite) int nbShelf;

/*!
 3D first front point.
 */
@property (nonatomic, readwrite) CGPoint p1;

/*!
 3D second front point.
 */
@property (nonatomic, readwrite) CGPoint p2;

/*!
 Method used to know if a point is in the concerned Zone.
 @param point Point to test.
 @return <b>YES</b> if the zone contains the point, otherwise <b>NO</b>.
 */
- (Boolean)containsPoint:(CGPoint)point;

/*!
 Method called to update the last offset and ratio computed.
 @param offset Last offset computed.
 @param ratio Last ratio computed.
 */
- (void)setOffset:(CGPoint)offset andRatio:(float)ratio;

@end
