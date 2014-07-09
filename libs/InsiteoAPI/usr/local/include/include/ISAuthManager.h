//
//  ISAuthManager.h
//  CommonAPI
//
//  Created by dev_iphone on 25/03/14.
//  Copyright (c) 2014 Unitag. All rights reserved.
//

/*!
 @header ISAuthManager.h
 ISAuthManager
 */

#import <Foundation/Foundation.h>

#import "ISInitProvider.h"
#import "ISPAuthListener.h"

/*!
 Class used to manage INSITEO authentication.
 */
@interface ISAuthManager : NSObject {
    
@private
    
    //Intern boolean used to know if we are connected
    Boolean m_isConnected;
    //Current user mail (could be nil
    NSString * m_currentUserMail;
}

/*!
 Intern boolean used to know if we are connected.
 */
@property (nonatomic, readonly) Boolean isConnected;

/*!
 Intern boolean used to know if we are connected.
 */
@property (nonatomic, retain) NSString * currentUserMail;

/*!
 Method used to log in.
 @param username The username.
 @param password The password.
 @param serverType The related server type.
 @param listener The listener to notify.
 */
- (void)loginWithUsername:(NSString *)username andPassword:(NSString *)password andServerType:(ISEServerType)serverType andListener:(id<ISPAuthListener>)listener;

/*!
 Method used to log out.
 @param serverType The related server type.
 @param listener The listener to notify.
 */
- (void)logoutWithServerType:(ISEServerType)serverType andListener:(id<ISPAuthListener>)listener;

/*!
 Method used to get all available sites.
 @param serverType The related server type.
 @param listener The listener to notify.
 */
- (void)refreshSitesWithServerType:(ISEServerType)serverType andListener:(id<ISPAuthListener>)listener;

@end
