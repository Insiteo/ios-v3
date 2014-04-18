//
//  ISPPackageLoaderListener.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 11/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPPackageLoaderListener.h
 ISPPackageLoaderListener
 */

#import <Foundation/Foundation.h>

/*!
 Protocol used to define a download package listener.
 */
@protocol ISPPackageLoaderListener <NSObject>

/*!
 Method called when a package was successfully downloaded.
 @param filePath Package file location.
 */
- (void)onPackageAvailableWithFilePath:(NSString *)filePath;

/*!
 Method called when a package download failed.
 */
- (void)onPackageDownloadFailed;

/*!
 Method called when package data were received.
 @param size Redeived data size.
 */
- (void)onDataReceived:(int)size;

/*!
 Method called when a package will start downloading.
 @param packageType Type of package.
 */
- (void)onDownloadPackageWillStart:(ISPackageType)packageType;

@end
