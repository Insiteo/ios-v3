//
//  SDKInitTableViewController.m
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import "SDKInitTableViewController.h"

#import <InsiteoSDK/InsiteoSDK.h>
#import <MBProgressHUD/MBProgressHUD.h>

typedef NS_ENUM(NSUInteger, TableViewSections) {
    TableViewSectionApplication = 0,
    TableViewSectionPackages,
    TableViewSectionLast
};

typedef NS_ENUM(NSUInteger, SectionApplicationRows) {
    SectionApplicationRowVersion = 0,
    SectionApplicationRowSDKVersion,
    SectionApplicationRowLocationVersion,
    SectionApplicationRowItineraryVersion,
    SectionApplicationRowSiteId,
    SectionApplicationRowLast
};

@interface SDKInitTableViewController () {
    NSArray *_packages;
}

@end

@implementation SDKInitTableViewController

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Refresh button
    UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh
                                                                          target:self
                                                                          action:@selector(onRefreshButtonTap:)];
    self.navigationItem.rightBarButtonItem = item;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    // Init SDK
    [self initializeSDK];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return TableViewSectionLast;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == TableViewSectionApplication) {
        return SectionApplicationRowLast;
    }
    return [_packages count];
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == TableViewSectionApplication) {
        return @"Application Info";
        
    }
    return @"Packages";
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    if (section == TableViewSectionPackages) {
        return [NSString stringWithFormat:@"%ld %@", (unsigned long)[_packages count], @"packages"];
    }
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *reuseIdentifier = @"InitCellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseIdentifier forIndexPath:indexPath];
    
    NSString *title, *detail;
    
    if (indexPath.section == TableViewSectionApplication) {
        switch (indexPath.row) {
            case SectionApplicationRowVersion:
                title = @"Application";
                detail = [NSString stringWithFormat:@"v%@ (%@)",
                          [NSBundle mainBundle].infoDictionary[@"CFBundleShortVersionString"],
                          [NSBundle mainBundle].infoDictionary[@"CFBundleVersion"]];
                break;
            case SectionApplicationRowSDKVersion:
                title = @"SDK";
                detail = [NSString stringWithFormat:@"v%@", ISApiVersion];
                break;
            case SectionApplicationRowLocationVersion:
                title = @"Location";
                detail = [NSString stringWithFormat:@"v%@", [ISLocationProvider getVersion]];
                break;
            case SectionApplicationRowItineraryVersion:
                title = @"Itinerary";
                detail = [NSString stringWithFormat:@"v%@", [ISItineraryProvider getVersion]];
                break;
            case SectionApplicationRowSiteId:
                title = @"Current Site Id";
                detail = [NSString stringWithFormat:@"%i/%@",
                          [Insiteo currentSite].siteId,
                          [Insiteo currentUser].initializationLanguage];
                break;
            default:
                break;
        }
    } else {
        ISEPackageType packageType = (ISEPackageType)[[_packages objectAtIndex:indexPath.row] intValue];
        
        // Package name
        title = [[ISPackage getDirectoryNameWithType:packageType] capitalizedString];
        
        // Package version
        int packageVersion = [[Insiteo currentSite] getCurrentPackageVersionWithPackageType:packageType];
        detail = [NSString stringWithFormat:@"v%d", packageVersion];
    }
    
    cell.textLabel.text = title;
    cell.detailTextLabel.text = detail;
    
    return cell;
}

#pragma mark - IBActions

- (IBAction)onRefreshButtonTap:(id)sender {
    // Refresh SDK
    [self initializeSDK];
}

- (IBAction)onHudDoubleTap:(id)sender {
    // Hide current progress view
    [MBProgressHUD hideHUDForView:self.navigationController.view animated:YES];
    // Cancel current task
    [[Insiteo sharedInstance].currentTask cancel];
}

#pragma mark - Insiteo SDK Initialization

- (void)initializeSDK {
    // Present a progress view to inform the user
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeIndeterminate;
    hud.label.text = @"Initializing";
    hud.detailsLabel.text = @"Double tap to cancel";
    
    // Add double tap gesture to enable task cancellation
    UITapGestureRecognizer *tapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self
                                                                                    action:@selector(onHudDoubleTap:)];
    tapRecognizer.numberOfTapsRequired = 2;
    [hud addGestureRecognizer:tapRecognizer];
    
    if (_exampleInitMode == InitModeAllInOne) {
        // Launch SDK (All in one process)
        [[Insiteo sharedInstance] launchWithInitializeHandler:^(ISError *error,
                                                                ISUserSite *suggestedSite,
                                                                Boolean fromLocalCache) {
            NSLog(@"Initialization %@", (error == nil) ? @"succeed" : @"failed");
            // NB: if an error occured, the SDK will try to initialize with the last known configuration. If it succeed,
            // `fromLocalCache` will be set to `YES`.
        }
                                         andChooseSiteHandler:^CLLocation *{
                                             // Random location for the example
                                             return [[CLLocation alloc] initWithLatitude:43.393 longitude:-1.456];
                                         }
                                              andStartHandler:^(ISError *error, NSArray *newPackages) {
                                                  if ([newPackages count] > 0) {
                                                      // New package(s) available
                                                      hud.label.text = @"Updating";
                                                  } else if (error) {
                                                      // Start
                                                      [self startWithErrorMessage:@"Start has failed"];
                                                  }
                                              }
                                             andUpdateHandler:^(ISError *error) {
                                                 // Start
                                                 [self startWithErrorMessage:(error) ? @"Update has failed" : nil];
                                                 
                                             }
                                     andUpdateProgressHandler:^(ISEPackageType packageType,
                                                                Boolean download,
                                                                int progress,
                                                                int total) {
                                         // Update progress view
                                         [hud setMode:MBProgressHUDModeDeterminate];
                                         hud.label.text = (download) ? @"Downloading" : @"Installing";
                                         [hud setProgress:(float)progress/(float)total];
                                     }];
        
    } else {
        // Initialization
        [[Insiteo sharedInstance] initializeWithInitializeHandler:^(ISError *error,
                                                                    ISUserSite *suggestedSite,
                                                                    Boolean fromLocalCache) {
            
            if (!error) {
                // Use `suggestedSite` or select yours for example:
                //ISUserSite *mySite = [[Insiteo currentUser] getSiteWithSiteId:MY-SITE-ID];
                
                // Start
                [[Insiteo sharedInstance] startWithSite:suggestedSite andStartHandler:^(ISError *error, NSArray *newPackages) {
                    if ([newPackages count] > 0) {
                        // Hide progress view
                        [MBProgressHUD hideHUDForView:self.navigationController.view animated:YES];
                        
                        // New packages available
                        UIAlertController *alertController =
                        [UIAlertController alertControllerWithTitle:@"New packages available"
                                                            message:@"New packages are available, do you want to download now?"
                                                     preferredStyle:UIAlertControllerStyleAlert];
                        
                        // Download
                        [alertController addAction:[UIAlertAction actionWithTitle:@"Download"
                                                                            style:UIAlertActionStyleDefault
                                                                          handler:^(UIAlertAction * _Nonnull action) {
                                                                              // Download
                                                                              [self downloadPackages:newPackages];
                                                                          }]];
                        
                        // Cancel
                        [alertController addAction:[UIAlertAction actionWithTitle:@"Cancel"
                                                                            style:UIAlertActionStyleCancel
                                                                          handler:^(UIAlertAction * _Nonnull action) {
                                                                              // Try to start if possible
                                                                          }]];
                        
                        [self presentViewController:alertController animated:YES completion:nil];
                        
                    } else {
                        // Start with error
                        [self startWithErrorMessage:(error) ? @"Start has failed" : nil];
                    }
                }];
                
            }
        }];
    }
}

- (void)downloadPackages:(NSArray *)packages {
    if (packages) {
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        hud.label.text = @"Updating";
        hud.detailsLabel.text = @"Double tap to cancel";
        
        UITapGestureRecognizer *tapRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self
                                                                                        action:@selector(onHudDoubleTap:)];
        tapRecognizer.numberOfTapsRequired = 2;
        [hud addGestureRecognizer:tapRecognizer];
        
        // Download packages
        [[Insiteo sharedInstance] updateCurrentSiteWithWantedPackages:packages
                                                     andUpdateHandler:^(ISError *error) {
                                                         // Start
                                                         [self startWithErrorMessage:(error) ? @"Update has failed" : nil];
                                                     }
                                             andUpdateProgressHandler:^(ISEPackageType packageType,
                                                                        Boolean download,
                                                                        int progress,
                                                                        int total) {
                                                 //Update HUD progress
                                                 [hud setMode:MBProgressHUDModeDeterminate];
                                                 [hud setProgress:0.0];
                                                 hud.label.text = download ? @"Downloading" : @"Installing";
                                                 [hud setProgress:(float)progress/(float)total];
                                             }];
    }
}

#pragma mark - Start

- (void)startWithErrorMessage:(NSString *)errorMessage {
    // Hide current progress view
    [MBProgressHUD hideHUDForView:self.navigationController.view animated:YES];
    
    if (errorMessage) {
        // An error occured
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
        [hud setMode:MBProgressHUDModeText];
        hud.label.text = @"Error";
        hud.detailsLabel.text = errorMessage;
        [hud hideAnimated:YES afterDelay:2];
    }
    
    // Refresh data
    [self refreshPackagesSection];
}

- (void)refreshPackagesSection {
    // Get current site
    ISSite *currentSite = [Insiteo currentSite];
    ISUserSite *currentUserSite = currentSite.userSite;
    
    // Get packages path
    NSString *sitesPath = [Insiteo getRootDirectoryPath];
    NSString *packagesPath = [NSString stringWithFormat:@"%@/%@/sites/%d/%d/%@",
                              sitesPath,
                              [Insiteo getServerTypeDirectoryName:currentUserSite.serverType],
                              currentSite.siteId,
                              currentSite.applicationVersion,
                              currentSite.language];
    
    NSArray *directories = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:packagesPath error:nil];
    
    NSMutableArray *packages = [[NSMutableArray alloc] init];
    for (NSString *directory in directories) {
        ISEPackageType type = [ISPackage getPackageTypeWithDirectoryName:directory];
        if (type != ISEPackageTypeUnknown) {
            [packages addObject:@(type)];
        }
    }
    
    _packages = [NSArray arrayWithArray:packages];
    
    // Reload tableView
    [self.tableView reloadData];
}

@end
