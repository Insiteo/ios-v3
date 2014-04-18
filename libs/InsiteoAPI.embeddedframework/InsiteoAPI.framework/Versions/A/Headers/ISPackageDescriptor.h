//
//  ISPackageDescriptor.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 16/11/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPackageDescriptor.h
 ISPackageDescriptor
 */

#import <Foundation/Foundation.h>

/*!
 Enum used to handle INSITEO data packages.
 @constant MAP_DATA_PACKAGE The package that contains Map data such as zoom levels and scales.
 @constant TILES_PACKAGE The package that contains Map tiles in .3cm format.
 @constant LOCATION_PACKAGE The package that contains Location data.
 @constant ITINERARY_PACKAGE The package that contains Itinerary data.
 @constant GEOFENCING_PACKAGE The package that contains Geofencing data.
 @constant LRR_CONTENT_PACKAGE The package that contains low refresh rate catalog content.
 @constant HRR_CONTENT_PACKAGE The package that contains high refresh rate catalog content.
 @constant FINGERPRINT_PACKAGE The package that contains fingerprint configuration files.
 @constant ANALYTICS_PACKAGE The package that contains analytics configuration files.
 @constant GAMING_PACKAGE The package that contains gaming files.
 @constant MAP_3D_PACKAGE The package that contains all 3D files.

 @constant UNKNOWN_PACKAGE Default NULL package type.
 */
typedef enum {
	MAP_DATA_PACKAGE,
    TILES_PACKAGE,
    LOCATION_PACKAGE,
    ITINERARY_PACKAGE,
    GEOFENCING_PACKAGE,
    LRR_CONTENT_PACKAGE,
    HRR_CONTENT_PACKAGE,
    FINGERPRINT_PACKAGE,
    ANALYTICS_PACKAGE,
    GAMING_PACKAGE,
    APP_RESOURCES_PACKAGE,
    MAP_3D_PACKAGE,
    UNKNOWN_PACKAGE,
} ISPackageType;

#import "ISInitParameters.h"

#pragma mark - MAP

/*!
 @"mapdata"
 */
extern NSString * const PACK_MAP_DATA_DIRECTORY_NAME;

/*!
 @"mapdata"
 */
extern NSString * const PACK_TILES_DIRECTORY_NAME;

#pragma mark - LOCATION

/*!
 @"loc"
 */
extern NSString * const PACK_LOCATION_DIRECTORY_NAME;

#pragma mark - ITINERARY

/*!
 @"iti"
 */
extern NSString * const PACK_ITINERARY_DIRECTORY_NAME;

#pragma mark - GEOFENCING

/*!
 @"geofence"
 */
extern NSString * const PACK_GEOFENCING_DIRECTORY_NAME;

#pragma mark - CONTENT

/*!
 @"lrrcontent"
 */
extern NSString * const PACK_LRR_CONTENT_DIRECTORY_NAME;

/*!
 @"hrrcontent"
 */
extern NSString * const PACK_HRR_CONTENT_DIRECTORY_NAME;

#pragma mark - FINGERPRINT

/*!
 @"fingerprint"
 */
extern NSString * const PACK_FINGERPRINT_DIRECTORY_NAME;

/*!
 @"analytics"
 */
extern NSString * const PACK_ANALYTICS_DIRECTORY_NAME;

/*!
 @"resources"
 */
extern NSString * const PACK_APP_RESOURCES_DIRECTORY_NAME;

/*!
 @"3d"
 */
extern NSString * const PACK_3D_DIRECTORY_NAME;

/*!
 Class used to represent an INSITEO data package.
 */
@interface ISPackageDescriptor : NSObject {
    
@private
    
    //Package type
    ISPackageType m_packageType;
    //URL to download it
    NSString * m_fileUrl;
    //Package version
    int m_version;
    //Package zip MD5
    NSString * m_zipMd5;
    //Package size
    int m_size;
    //Package related site identifier
    int m_siteId;
    //Package related application version
    int m_applicationVersion;
    //Package related language
    NSString * m_language;
    //INSITEO server type
    ISEServerType m_serverType;
    //Package temporary zip path
    NSString * m_zipPath;
}

/*!
 Package type.
 */
@property (nonatomic, readwrite) ISPackageType packageType;

/*!
 URL to download it.
 */
@property (nonatomic, retain) NSString * fileUrl;

/*!
 Package version.
 */
@property (nonatomic, readwrite) int version;

/*!
 Package zip MD5.
 */
@property (nonatomic, retain) NSString * zipMd5;

/*!
 Package size.
 */
@property (nonatomic, readwrite) int size;

/*!
 Package related site identifier.
 */
@property (nonatomic, readwrite) int siteId;

/*!
 Package related application version.
 */
@property (nonatomic, readwrite) int applicationVersion;

/*!
 Package related language.
 */
@property (nonatomic, retain) NSString * language;

/*!
 Package related INSITEO server type.
 */
@property (nonatomic, readwrite) ISEServerType serverType;

/*!
 Package temporary zip path.
 */
@property (nonatomic, retain) NSString * zipPath;

/*!
 Main constructor.
 @param siteId Package related site identifier.
 @param applicationVersion Package related application version.
 @param language Package related language.
 @param zipPath Temporary package zipPath. (Could be nil).
 @param serverType INSITEO server type.
 */
- (id)initWithSiteId:(int)siteId andApplicationVersion:(int)applicationVersion andLanguage:(NSString *)language andZipPath:(NSString *)zipPath andServerType:(ISEServerType)serverType;

/*!
 Static method used to know if the filename parameter corresponds to a known INSITEO package.
 @param filename The filename to test.
 @return The related ISPackageType. Could be UNKNOWN_PACKAGE.
 */
+ (ISPackageType)getPackageType:(NSString *)filename;

/*!
 Static method used to know if the directoryName parameter corresponds to a known INSITEO package.
 @param directoryName The wanted package directory name.
 @return The related ISPackageType. Could be UNKNOWN_PACKAGE.
 */
+ (ISPackageType)getPackageTypeWithDirectoryName:(NSString *)directoryName;

/*!
 Static method used to get the application directory related to a specific package type.
 @param type Package type to consider.
 @return The related directory path. Could be nil.
 */
+ (NSString *)getDirectoryNameWithType:(ISPackageType)type;

@end
