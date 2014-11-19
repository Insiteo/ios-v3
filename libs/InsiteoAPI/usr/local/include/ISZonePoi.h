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

@class ISZone;

#import "ISZonePoi.h"
#import "ISPosition.h"

/*!
 @class ISZonePoi
 Class used to represent the association between a Zone (MapAPI) and a Poi (CatalogAPI).
 */
@interface ISZonePoi : NSObject

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
 Method used to get the related ISZone.
 @return Related ISZone.
 */
- (ISZone *)getZone;

@end