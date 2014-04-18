//
//  ISZipArchive.h
//  ISZipArchive
//
//  Created by Sam Soffes on 7/21/10.
//  Copyright Sam Soffes 2010. All rights reserved.
//
//  Based on ZipArchive by aish
//  http://code.google.com/p/ziparchive
//

/*!
 @header ISZipArchive.h
 ISZipArchive
 */

#import <UIKit/UIKit.h>

#import "ISPUnzipLoaderListener.h"
#import "ISPCancelable.h"

/*!
 Internal class used to unzip INSITEO packages.
 */
@interface ISZipArchive : NSObject <ISPCancelable> {
    
@private
    
    //Float unzipping progress
    float m_progress;
    //Unzipping listener to notify
    id<ISPUnzipLoaderListener> m_listener;
    //Internal boolean used to know if the unzipping action was cancelled
    volatile Boolean m_cancel;
}

/*!
 unzipping progress.
 */
@property (nonatomic, readwrite) float progress;

/*!
 Unzipping listener to notify.
 */
@property (nonatomic, retain) id<ISPUnzipLoaderListener> listener;

/*!
 Internal boolean used to know if the unzipping action was cancelled.
 */
@property (atomic, readwrite) volatile Boolean cancel;

+ (ISZipArchive *)instance;

- (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination andListener:(id<ISPUnzipLoaderListener>)listener;

- (BOOL)unzipFileAtPath:(NSString *)path toDestination:(NSString *)destination andListener:(id<ISPUnzipLoaderListener>)listener overwrite:(BOOL)overwrite password:(NSString *)password error:(NSError **)error;

@end
