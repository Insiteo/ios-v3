//
//  ISInitParameters.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 09/02/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISInitParameters.h
 ISInitParameters
 */

#import <Foundation/Foundation.h>

/*!
 Enum used to handle INSITEO server types.
 @constant PROD_SERVER Production server.
 @constant TEST_SERVER Test server.
 @constant DEV_SERVER Development server.
 */
typedef enum {
    PROD_SERVER = 1,
    TEST_SERVER,
    DEV_SERVER
} ISEServerType;

#import "ISPRTO.h"

/*!
 Class used to define API initialization parameters.
 */
@interface ISInitParameters : NSObject {
    
@private
    
    //Server URL to use
    NSString * m_serverUrl;
    //Site identifier to use
    int m_siteId;
    //Application version to use
    int m_applicationVersion;
    //Language to use
    NSString * m_language;
    //INSITEO server type
    ISEServerType m_serverType;
    //Boolean used to know if we force the download of packages even if the application is up to date
    Boolean m_forceDownload;
}

/*!
 Server URL to use.
 */
@property (nonatomic, retain) NSString * serverUrl;

/*!
 Site identifier to use.
 */
@property (nonatomic, readwrite) int siteId;

/*!
 Application version to use.
 */
@property (nonatomic, readwrite) int applicationVersion;

/*!
 Language to use.
 */
@property (nonatomic, retain) NSString * language;

/*!
 INSITEO server type.
 */
@property (nonatomic, readwrite) ISEServerType serverType;

/*!
 Boolean used to know if we force the download of packages even if the application is up to date.
 */
@property (nonatomic, readwrite) Boolean forceDownload;

/*!
 Current map render mode (2D or 3D).
 */
@property (nonatomic, readwrite) ISERenderMode renderMode;

/*!
 Static method used to get the server type NSString identifier.
 @param serverType INSITEO server type.
 @return The related NSString.
 */
+ (NSString *)getServerTypeString:(ISEServerType)serverType;

/*!
 Static method used to get the server NSString for use in URLs.
 @param serverType INSITEO server type.
 @return The related NSString to use in URLs only.
 */
+ (NSString *)getServerTypeStringForURL:(ISEServerType)serverType;

/*!
 Main constructor.
 @param serverUrl The server URL to use.
 @param siteId The site identifier to use.
 @param applicationVersion The application version to use.
 @param language The language to use.
 @param forceDownload Boolean used to know if we force the download of packages even if the application is up to date.
 @param serverType INSITEO server type to communicate with.
 @param renderMode Wanted render mode.
 */
- (id)initWithServerUrl:(NSString *)serverUrl andSiteId:(int)siteId andApplicationVersion:(int)applicationVersion andLanguage:(NSString *)language andForceDownload:(Boolean)forceDownload andServerType:(ISEServerType)serverType andRenderMode:(ISERenderMode)renderMode;

@end
