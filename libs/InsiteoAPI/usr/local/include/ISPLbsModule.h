//
//  ISPLbsModule.h
//  CommonAPI
//
//  Created by INSITEO on 21/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPLbsModule.h
 ISPLbsModule
 */

#import <UIKit/UIKit.h>

#import "ISLocation.h"

@protocol PLbsModuleRequest;
@protocol PLbsModuleResponse;

/*!
 Enum used to define location modules.
 @constant LBS_MODULE_ITINERARY Itinerary location module.
 @constant LBS_MODULE_MEETME MeetMe location module.
 @constant LBS_MODULE_GEOFENCING Geofencing location module.
 */
typedef enum {
	LBS_MODULE_ITINERARY,
	LBS_MODULE_MEETME,
	LBS_MODULE_GEOFENCING
} LbsModuleType;

/*!
 Protocol used to define a Location module.
 */
@protocol ISPLbsModule <NSObject>

/*!
 Lbs module type (see enum for details).
 */
@property (readonly) LbsModuleType lbsModuleType;

/*!
 Method called to add module data to the Lbs request.
 @warning Application does not need to call this method. Set the response for this module.
 @param locRequest Location request.
 */
- (Boolean)addLbsModuleRequest:(id<PLbsModuleRequest>)locRequest;

/*!
 Method called to set module Lbs response.
 @warning Application does not need to call this method. Set the response for this module.
 @param locResponse Location response.
 */
- (void)setLbsResponse:(id<PLbsModuleResponse>)locResponse;

/*!
 Method called set the last location to the location module.
 @param location Last location get from the location provider.
 */
- (void)setLocation:(ISLocation *)location;

/*!
 Clear all data from this LBSModule. Module will need to be initialized before being used again.
 @warning Application does not need to call this method.
 */
- (void)clear;

@end
