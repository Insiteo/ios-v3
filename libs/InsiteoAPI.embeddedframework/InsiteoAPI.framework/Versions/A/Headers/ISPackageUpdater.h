//
//  ISPackageUpdater.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 16/11/11.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPackageUpdater.h
 ISPackageUpdater
 */

#import <Foundation/Foundation.h>

#import "ISPackageDescriptor.h"
#import "ISPPackageLoaderListener.h"
#import "ISPUnzipLoaderListener.h"
#import "ISPInitListener.h"
#import "ISPCancelable.h"

/*!
 Class used to manage INSITEO data packages inside an application.
 */
@interface ISPackageUpdater : NSObject <ISPPackageLoaderListener, ISPUnzipLoaderListener, ISPCancelable> {
    
@private
    
    //Array of packages that need to be downloaded
    NSMutableArray * m_downloadPackages;
    //Array of packages that need to be unzipped
    NSMutableArray * m_unzipPackages;
    //Array of wanted packages
    NSArray * m_wantedPackages;
    
    //Total packages size
    int m_packagesSize;
    //Current download size
    int m_currentDownloadSize;
    //Total packages files
    int m_packagesNbFiles;
    //Current treated files
    int m_nbTreatedFiles;
    
    //Init listener used to notify for update events
    id<ISPInitListener> m_initListener;
    
#pragma mark - ISPCancelable
    
    //Cancel boolean used to handle user cancel events
    volatile Boolean m_cancelBool;
    //Packages downloader
    id<ISPCancelable> m_currentPackageLoader;
    //Packages unzipper
    id<ISPCancelable> m_currentFileUnzipper;
    //Intern boolean used to know if a new Analytics package is installed
    Boolean m_newAnalyticsPackage;
}

/*!
 Array of packages that need to be downloaded.
 */
@property (nonatomic, retain) NSMutableArray * downloadPackages;

/*!
 Init listener used to notify for update events.
 */
@property (assign) id<ISPInitListener> initListener;

/*!
 Method used to updates all application packages.
 @param wantedPackages An array of wanted packages that need to be updated.
 */
- (void)updatePackagesWithWantedPackages:(NSArray *)wantedPackages;

/*!
 Method used to updates all application packages.
 @param wantedPackages An array of wanted packages that need to be updated.
 @param force Boolean used to know if we force the download of all packages.
 */
- (void)updatePackagesWithWantedPackages:(NSArray *)wantedPackages andForce:(Boolean)force;

/*!
 Method used to check all application packages.
 @param forceDownload Boolean used to know if we force the download of packages even if the application is up to date.
 */
- (void)checkPackages:(Boolean)forceDownload;

/*
 Static methode used to unzip specifi packages.
 @param forceDownload Boolean used to know if we force the download of packages even if the application is up to date.
 */
+ (void)unzipPackages:(NSArray *)packageDescriptors withListener:(id<ISPUnzipLoaderListener>)listener;

@end
