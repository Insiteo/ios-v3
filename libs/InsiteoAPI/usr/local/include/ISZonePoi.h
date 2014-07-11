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

#import "ISZonePoi.h"
#import "ISPosition.h"

/*!
 @class ISZonePoi
 Class used to represent the association between a Zone (MapAPI) and a Poi (CatalogAPI).
 */
@interface ISZonePoi : NSObject {
    
@private
    
    //Relative zone identifier
    int m_zoneId;
    //Relative zone name
    NSString * m_label;
    
    //Relative poiId
    int m_poiId;
    //External id
    NSString * m_externalPoiId;
    
    //Zone position
    ISPosition * m_position;
    
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
 Related poiId.
 */
@property (nonatomic, readwrite) int poiId;

/*!
 Related poi external id.
 */
@property (nonatomic, retain) NSString * externalPoiId;

/*!
 Related zone position.
 */
@property (nonatomic, retain) ISPosition * position;

/*!
 Poi offset from zone center.
 */
@property (nonatomic, readwrite) CGPoint offset;

/*!
 Related association label.
 */
@property (nonatomic, retain) NSString * label;

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