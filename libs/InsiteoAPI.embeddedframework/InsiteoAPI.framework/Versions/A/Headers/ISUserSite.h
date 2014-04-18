//
//  ISUserSite.h
//  CommonAPI
//
//  Created by dev_iphone on 25/03/14.
//  Copyright (c) 2014 Unitag. All rights reserved.
//

/*!
 @header ISUserSite.h
 ISUserSite
 */

#import <Foundation/Foundation.h>

#import "ISInitProvider.h"

/*!
 Class used to represent a user INSITEO site.
 */
@interface ISUserSite : NSObject

/*!
 Site identifier.
 */
@property (nonatomic, readwrite) int siteID;

/*!
 Site label (its name).
 */
@property (nonatomic, retain) NSString * label;

/*!
 Site available languages.
 */
@property (nonatomic, retain) NSArray * languages;

/*!
 Site available versions.
 */
@property (nonatomic, retain) NSArray * versions;

/*!
 Server type.
 */
@property (nonatomic, readwrite) ISEServerType server;

/*!
 Main constructor.
 @param siteId Site identifier.
 @param label Site label (its name).
 @param languages Site available languages.
 @param versions Site available versions.
 */
- (id)initWithID:(int)siteId withLabel:(NSString *)label withLanguages:(NSArray *)languages withVersions:(NSArray *)versions;

@end
