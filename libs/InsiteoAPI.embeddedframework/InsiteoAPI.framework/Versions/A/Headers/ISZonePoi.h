//
//  ISZonePoi.h
//  CatalogAPI
//
//  Created by INSITEO on 04/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISZonePoi.h
 ISZonePoi
 */

#import <Foundation/Foundation.h>

@class ISGfxZone;

/*!
 @class ISZonePoi
 Class used to represent the association between a Zone (MapAPI) and a Poi (CatalogAPI).
 */
@interface ISZonePoi : NSObject {
    
@private
    
    //Relative zone identifier
    int m_zoneId;
    //Relative zone name
    NSString * m_zoneName;
    
    //Relative poiId
    int m_poiId;
    //External id
    NSString * m_externalId;
    //Poi x offset from zone center
    float m_offsetX;
    //Poi y offset from zone center
    float m_offsetY;
    
    //Relative mapId
    int m_mapId;
    
    //Y zone coordinate (in meters)
    float m_zonePosX;
    //X zone coordinate (in meters)
    float m_zonePosY;
    
    //Extra value
    NSString * m_extra1;
    //Extra value
    NSString * m_extra2;
    //Extra value
    NSString * m_extra3;
    //Extra value
    float m_fExtra1;
}

/*!
 Related zone identifier.
 */
@property (nonatomic, readwrite) int zoneId;

/*!
 Related zone name.
 */
@property (nonatomic, retain) NSString * zoneName;

/*!
 Related poiId.
 */
@property (nonatomic, readwrite) int poiId;

/*!
 Related poi external id.
 */
@property (nonatomic, retain) NSString * externalId;

/*!
 Poi x offset from zone center.
 */
@property (nonatomic, readwrite) float offsetX;

/*!
 Poi y offset from zone center.
 */
@property (nonatomic, readwrite) float offsetY;

/*!
 Related map identifier.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 Related zone x coordinates (in meters).
 */
@property (nonatomic, readwrite) float zonePosX;

/*!
 Related zone y coordinates (in meters).
 */
@property (nonatomic, readwrite) float zonePosY;

/*!
 NSString extra parameter.
 */
@property (nonatomic, retain) NSString * extra1;

/*!
 NSString extra parameter.
 */
@property (nonatomic, retain) NSString * extra2;

/*!
 NSString extra parameter.
 */
@property (nonatomic, retain) NSString * extra3;

/*!
 Float extra parameter.
 */
@property (nonatomic, readwrite) float fExtra1;

/*!
 Related zone.
 */
@property (nonatomic, readonly) ISGfxZone * zone;

@end