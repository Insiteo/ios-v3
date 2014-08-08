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

extern float DEFAULT_ZONE_HEIGHT;

#import "cocos2d.h"
#import "ISPosition.h"
#import "ISZone.h"
#import "ISPRTO.h"
#import "ISCC3Zone.h"
#import "ISCC2Zone.h"

/*!
 Class used to represent a Map Zone.
 */
@interface ISGfxZone : NSObject <ISPRTO> {
    
@private
    
    //Related zone entitie
    ISZone * m_zone;
    
#pragma mark - Rendering
    
    //Cocos2d node
    ISCC2Zone * m_cocos2dNode;
    
    //Cocos3d node
    ISCC3Zone * m_cocos3dNode;
    //
    CC3Node * m_shelfNode;
    
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
}

/*!
 Related zone entitie.
 */
@property (nonatomic, retain) ISZone * zone;

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
 Main constructor.
 @param zone Related zone entitie.
 @param map Zone map entitie.
 @param renderMode Current render mode.
 */
- (id)initWithZone:(ISZone *)zone andMap:(ISMap *)map andRenderMode:(ISERenderMode)renderMode;

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

/*!
 Static method used to get an ISZone height.
 @param zone Concerned zone.
 @return Given zone height.
 */
+ (float)zoneHeight:(ISZone *)zone;

@end
