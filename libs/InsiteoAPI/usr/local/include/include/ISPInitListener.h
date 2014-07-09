//
//  ISPInitListener.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 11/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPInitListener.h
 ISPInitListener
 */

#import <Foundation/Foundation.h>

#import "ISInsiteoError.h"
#import "ISPackage.h"

/*!
 Enum used to manage application initialization return codes.
 @constant FAIL The initialization application failed.
 @constant SUCCESS The application initialization succeeded.
 @constant SUCCESS_NEW_DATA The application initialization succeeded and new data are available.
 */
typedef enum {
   	FAIL,
	SUCCESS,
	SUCCESS_NEW_DATA,
} ISEInitAPIResult;

/*!
 Protocol used to define initialization, update and deployement events of our API.
 */
@protocol ISPInitListener <NSObject>

#pragma mark - Initialization
/*!
 @name Initialization
 */

/*!
 Method called when an API initialization finished.
 @param result Initialization result.
 @param error The resulted ISInsiteoError to handle. Could be nil if success.
 */
- (void)onInitDone:(ISEInitAPIResult)result andError:(ISInsiteoError *)error;
                                                          
#pragma mark - Progress

/*!
 @name Progress
 */

/*!
 Method called during the download task to get data progress.
 @param progress Download progress.
 @param total Total download bytes data.
 */
- (void)onDownloadProgressWithProgress:(int)progress andTotal:(int)total;

/*!
 Method called when the download task for a package will start.
 @param packageType the package type that will be downloaded.
 */
- (void)onDownloadPackageWillStart:(ISPackageType)packageType;

/*!
 Method called during the unzipping task to get data progress.
 @param progress Unzipping progress.
 @param total Total unzipping data.
 */
- (void)onInstallProgressWithProgress:(int)progress andTotal:(int)total;
                                                          
#pragma mark - Update

/*!
 @name Update
 */
                                                          
/*!
 Method called when an update succeeded.
 @param success Boolean used to know if the update succeeded.
 @param error Related error if success == false.
 */
- (void)onDataUpdateDone:(Boolean)success andError:(ISInsiteoError *)error;

@end
