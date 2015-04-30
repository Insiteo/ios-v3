//
//  InitStepByStepViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 09/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "InitStepByStepViewController.h"

#import <InsiteoSDK/InsiteoSDK.h>
#import <MBProgressHUD/MBProgressHUD.h>

typedef NS_ENUM(NSUInteger, EInformationSections) {
    EInformationSectionApplication = 0,
    EInformationSectionPackages,
    EInformationSectionLast
};

typedef NS_ENUM(NSUInteger, EInformationApplicationRows) {
    EInformationApplicationRowVersion = 0,
    EInformationApplicationRowApiVersion,
    EInformationApplicationRowLocationVersion,
    EInformationApplicationRowItineraryVersion,
    EInformationApplicationRowSiteId,
    EInformationApplicatonRowLast
};

@interface InitStepByStepViewController () {
    //Current packages
    NSArray * m_packages;
    //Info HUD
    MBProgressHUD * m_hud;
    //Keep reference on new packages
    NSArray * m_newPackages;
}

@end

@implementation InitStepByStepViewController

- (id)init {
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        
    }
    return self;
}

#pragma mark - Separate Init / Update / Start

#define kSiteId 364

- (void)initAPI {
    //Create cancelable progress HUD. Canceling dialog will also cancel init task
    m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [m_hud setMode:MBProgressHUDModeIndeterminate];
    [m_hud setLabelText:@"Initializing"];
    [m_hud setDetailsLabelText:@"Double tap to cancel"];
    
    UITapGestureRecognizer * tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onHudDoubleTapped:)];
    [tapGestureRecognizer setNumberOfTapsRequired:2];
    [m_hud addGestureRecognizer:tapGestureRecognizer];
    
    //Initialize API
    [[Insiteo sharedInstance] initializeWithInitializeHandler:^(ISError *error, ISUserSite *suggestedSite, Boolean fromLocalCache) {
        //Hide HUD
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        //Now, start
        [self startAPI];
    }];
    
    //You could even use the ChooseSiteHandler if you want to use a specific location
}

- (void)startAPI {
    //Choose your site using user sites dictionary
    NSDictionary * sites = [[Insiteo currentUser] getSites];
    
    //Sort site by identifier
    NSMutableArray * sortedSiteKeys = [NSMutableArray arrayWithArray:[sites allKeys]];
    NSSortDescriptor * highestToLowest = [NSSortDescriptor sortDescriptorWithKey:@"self" ascending:NO];
    [sortedSiteKeys sortUsingDescriptors:[NSArray arrayWithObject:highestToLowest]];
    
    //Get first site with lower identifier
    NSNumber * lowerId = [sortedSiteKeys objectAtIndex:0];
    ISUserSite * site = [sites objectForKey:lowerId];
    
    //Or if you have more than one site, you could for exemple try to get it with its identifier (could be found on the back office)
    //ISUserSite * site = [[Insiteo currentUser] getSiteWithSiteId:kSiteId];
    
    //Start with site
    [[Insiteo sharedInstance] startWithSite:site andStartHandler:^(ISError *error, NSArray *newPackages) {
        //New packages available ?
        if ([newPackages count] > 0) {
            //Keep reference to download later
            m_newPackages = newPackages;
            
            //Present a popup to download new packages
            UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"New packages available"
                                                                 message:@"New packages are available, do you want to download now?"
                                                                delegate:self cancelButtonTitle:@"No" otherButtonTitles:@"Yes", nil];
            [alertView show];
            
        } else {
            //Start with error
            [self startWithErrorMessage:(error) ? @"Start has failed" : nil];
        }
    }];
}

- (void)downloadPackages:(NSArray *)packages {
    if (packages) {
        //Update HUD
        m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        [m_hud setLabelText:@"Updating"];
        [m_hud setDetailsLabelText:@"Double tap to cancel"];
        
        [[Insiteo sharedInstance] updateCurrentSiteWithWantedPackages:packages andUpdateHandler:^(ISError *error) {
            //Hide HUD
            [MBProgressHUD hideHUDForView:self.view animated:YES];
            
            //Launch site
            [self startWithErrorMessage:(error) ? @"Update has failed" : nil];
            
        } andUpdateProgressHandler:^(ISEPackageType packageType, Boolean download, int progress, int total) {
            //Update HUD progress
            [m_hud setMode:MBProgressHUDModeDeterminate];
            [m_hud setProgress:0.0];
            [m_hud setLabelText:download ? @"Downloading" : @"Installing"];
            [m_hud setProgress:(float)progress/(float)total];
        }];
    }
}

#pragma mark - Launch

- (void)startWithErrorMessage:(NSString *)errorMessage {
    //Error HUD
    if (errorMessage) {
        m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        [m_hud setMode:MBProgressHUDModeText];
        [m_hud setLabelText:@"Error"];
        [m_hud setDetailsLabelText:errorMessage];
        [m_hud hide:YES afterDelay:2];
    }
    
    //Update view with current site packages
    [self updateTableViewWithCurrentSite];
}

#pragma mark - Cancel

- (IBAction)onHudDoubleTapped:(id)sender {
    [m_hud hide:YES];
    [[Insiteo sharedInstance].currentTask cancel];
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex != alertView.cancelButtonIndex) {
        //Download packages
        [self downloadPackages:m_newPackages];
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return EInformationSectionLast;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == EInformationSectionApplication) {
        return EInformationApplicatonRowLast;
        
    } else if (section == EInformationSectionPackages) {
        return [m_packages count];
        
    }
    
    return 0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == EInformationSectionApplication) {
        NSString * appName = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleDisplayName"];
        return appName;
        
    } else if (section == EInformationSectionPackages) {
        return @"Packages";
        
    }
    
    return nil;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    if (section == EInformationSectionPackages) {
        return [NSString stringWithFormat:@"%i %@", [m_packages count], @"Packages"];
    }
    
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString * CellIdentifier = @"CellIdentifier";
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
        [cell setAccessoryType:UITableViewCellAccessoryNone];
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    }
    
    if (indexPath.section == EInformationSectionApplication) {
        if (indexPath.row == EInformationApplicationRowVersion) {
            NSString * appVersion = [NSString stringWithFormat:@"%@ (%@)", [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"], [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]];
            
            [cell.textLabel setText:@"Application"];
            [cell.detailTextLabel setText:appVersion];
            
        } else if (indexPath.row == EInformationApplicationRowApiVersion) {
            [cell.textLabel setText:@"API"];
            [cell.detailTextLabel setText:ISApiVersion];
            
        } else if (indexPath.row == EInformationApplicationRowLocationVersion) {
            NSString * locVersion = [ISLocationProvider getVersion];
            
            [cell.textLabel setText:@"Location"];
            [cell.detailTextLabel setText:locVersion];
            
        } else if (indexPath.row == EInformationApplicationRowItineraryVersion) {
            NSString * itineraryVersion = [ISItineraryProvider getVersion];
            
            [cell.textLabel setText:@"Itinerary"];
            [cell.detailTextLabel setText:itineraryVersion];
            
        } else if (indexPath.row == EInformationApplicationRowSiteId) {
            [cell.textLabel setText:@"Site Id"];
            [cell.detailTextLabel setText:[NSString stringWithFormat:@"%i/%@", [Insiteo currentSite].siteId, [Insiteo currentUser].initializationLanguage]];
        }
        
    } else if (indexPath.section == EInformationSectionPackages) {
        ISEPackageType packageType = (ISEPackageType)[[m_packages objectAtIndex:indexPath.row] intValue];
        
        //Name
        NSString * packageName = [ISPackage getDirectoryNameWithType:packageType];
        [cell.textLabel setText:packageName];
        
        //Version
        int packageVersion = [[Insiteo currentSite] getCurrentPackageVersionWithPackageType:packageType];
        [cell.detailTextLabel setText:[NSString stringWithFormat:@"v%d", packageVersion]];
    }
    
    return cell;
}

#pragma mark - Packages

- (void)updateTableViewWithCurrentSite {
    //Get current user site
    ISSite * currentSite = [Insiteo currentSite];
    ISUserSite * currentUserSite = [Insiteo currentSite].userSite;
    
    //Get packages
    NSString * sitesPath = [Insiteo getRootDirectoryPath];
    NSString * packagesPath = [NSString stringWithFormat:@"%@/%@/sites/%d/%d/%@", sitesPath, [Insiteo getServerTypeDirectoryName:currentUserSite.serverType], currentSite.siteId, currentSite.applicationVersion, currentSite.language];
    
    NSFileManager * fm = [NSFileManager defaultManager];
    NSArray * directories = [fm contentsOfDirectoryAtPath:packagesPath error:nil];
    
    NSMutableArray * packages = [[NSMutableArray alloc] init];
    for (NSString * directory in directories) {
        ISEPackageType type = [ISPackage getPackageTypeWithDirectoryName:directory];
        
        if (type != ISEPackageTypeUnknown) {
            [packages addObject:[NSNumber numberWithInt:type]];
        }
    }
    
    //Refresh data
    m_packages = [NSArray arrayWithArray:packages];
    [self.tableView reloadData];
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //UI
    [self setTitle:@"Initialization Step-By-Step"];
    
    //Reload item
    UIBarButtonItem * reloadItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(initAPI)];
    [self.navigationItem setRightBarButtonItem:reloadItem];
    
    m_packages = [[NSArray alloc] init];
    
    //Step by step init method
    [self initAPI];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
