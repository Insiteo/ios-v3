//
//  ISPUnzipLoaderListener.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 13/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPUnzipLoaderListener.h
 ISPUnzipLoaderListener
 */

#import <Foundation/Foundation.h>

/*!
 Protocol used to handle unzipping events.
 */
@protocol ISPUnzipLoaderListener <NSObject>

/*!
 Method called when a new file was unzipped.
 */
- (void)onFileUnzipOneFile;

/*!
 Method called when a whole zip file was unzipped.
 @param path The unzipping destination path.
 */
- (void)onFileUnzipSucceededWithPath:(NSString *)path;

/*!
 Method called when the unzipping task failed.
 */
- (void)onFileUnzipFailed;

@end
