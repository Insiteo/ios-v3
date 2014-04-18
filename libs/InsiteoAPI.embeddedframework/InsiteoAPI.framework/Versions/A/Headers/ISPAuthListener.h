//
//  ISPAuthListener.h
//  CommonAPI
//
//  Created by dev_iphone on 25/03/14.
//  Copyright (c) 2014 Unitag. All rights reserved.
//

/*!
 @header ISPAuthListener.h
 ISPAuthListener
 */

#import <Foundation/Foundation.h>

#import "ISInsiteoError.h"

/*!
 Protocol used to handle INSITEO authentication.
 */
@protocol ISPAuthListener <NSObject>

/*!
 Method called when a login task is done.
 @param success <b>YES</b> if the login succeeded, otherwise <b>NO</b>.
 @param error Related error if no success.
 */
- (void)onLoginDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error;

/*!
 Method called when a logout task is done.
 @param success <b>YES</b> if the logout succeeded, otherwise <b>NO</b>.
 @param error Related error if no success.
 */
- (void)onLogoutDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error;

/*!
 Method called when a refresh sites task is done.
 @param success <b>YES</b> if the refreshing succeeded, otherwise <b>NO</b>.
 @param error Related error if no success.
 @param sites Available sites if success (could be nil).
 */
- (void)onRefreshSitesDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error andSites:(NSArray *)sites;

@end
