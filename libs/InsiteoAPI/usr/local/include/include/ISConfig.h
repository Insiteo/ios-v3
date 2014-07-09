//
//  ISConfig.h
//  CommonAPI
//

/*!
 @header ISConfig.h
 ISConfig
 */

/*!
 @"rest/api/"
 */
extern NSString * const BASE_SERVICE_PATH;

/*!
 Class used to manage common client/server url.
 */

@interface ISConfig : NSObject

/*
 @internal
 Method used to set a different init package url. DO NOT USE this function if you're not sure.
 @param initPackage New init package to use.
*/
+ (void)setInitPackage:(NSString *)initPackage;

/*!
 Method used to get the base service URL.
 @param serverUrl Server url to use.
 @return The resulted service URL.
 */
+ (NSString *)getServiceUrlWithServerUrl:(NSString *)serverUrl;

/*!
 Method used to get the init URL.
 @param serverUrl Server url to use.
 @param siteId Site id to use.
 @param applicationVersion Application version to use.
 @param language Language to use.
 @return The resulted init URL.
 */
+ (NSString *)getInitUrlWithServerUrl:(NSString *)serverUrl andSiteId:(int)siteId andApplicationVersion:(int)applicationVersion andLanguage:(NSString *)language;

/*!
 Method used to get a localized NSString from an NSString key (word to translate).
 @param key Word to translate.
 @return The translated NSString.
 */
+ (NSString *)localizedString:(NSString *)key;

/*!
 Method used to get the system localized NSString from an NSString key (word to translate).
 @param key Word to translate.
 @return The translated NSString.
 */
+ (NSString *)realLocalizedString:(NSString *)key;

/*!
 Method used to get a localized NSString from an NSString key (word to translate) for a specific language.
 @param key Word to translate.
 @param language The language to use.
 @return The translated NSString.
 */
+ (NSString *)localizedStringWithKey:(NSString *)key andLanguage:(NSString *)language;

@end
