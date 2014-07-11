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
#import "LoginResponseParser.h"

/*!
 Protocol used to handle INSITEO authentication.
 */
@protocol ISPAuthListener <NSObject>

/*!
 Method called when a login task is done.
 @param success <b>YES</b> if the login succeeded, otherwise <b>NO</b>.
 @param error Related error if no success.
 @param sites Logged user available sites.
 @param roleId Logged user role identifier.
 @param remote Boolean used to know if login is local or remote.
 */
- (void)onLoginDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error andSites:(NSArray *)sites andRoleId:(ERoleID)roleId andRemote:(Boolean)remote;

/*!
 Method called when a logout task is done.
 @param success <b>YES</b> if the logout succeeded, otherwise <b>NO</b>.
 @param error Related error if no success.
 */
- (void)onLogoutDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error;

@optional

/*!
 Method called to refresh user available sites.
 @param success <b>YES</b> if the refresh succeeded, otherwise <b>NO</b>.
 @param error Related error if no success.
 @param sites Refreshed available sites.
 @param roleId Refreshed user role identifier.
 */
- (void)onRefreshSitesDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error andSites:(NSArray *)sites andRoleId:(ERoleID)roleId;

@end
