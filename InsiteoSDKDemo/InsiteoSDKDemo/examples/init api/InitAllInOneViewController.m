//
//  InitAllInOneViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 09/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "InitAllInOneViewController.h"

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

#define kSiteId 364

@interface InitAllInOneViewController () {
    //Current packages
    NSArray * m_packages;
    //Info HUD
    MBProgressHUD * m_hud;
}

@end

@implementation InitAllInOneViewController

- (id)init {
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        
    }
    return self;
}

#pragma mark - All in One init/start API

- (void)launchAPI {
    //Create cancelable progress HUD. Canceling dialog will also cancel init task
    m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [m_hud setMode:MBProgressHUDModeIndeterminate];
    [m_hud setLabelText:@"Initializing"];
    [m_hud setDetailsLabelText:@"Double tap to cancel"];
    
    UITapGestureRecognizer * tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onHudDoubleTapped:)];
    [tapGestureRecognizer setNumberOfTapsRequired:2];
    [m_hud addGestureRecognizer:tapGestureRecognizer];
    
    //Launch API
    [[Insiteo sharedInstance] launchWithInitializeHandler:^(ISError *error, ISUserSite *suggestedSite, Boolean fromLocalCache) {
        NSLog(@"Initialization done: %@", (error == nil) ? @"success" : @"fail");
        
    } andChooseSiteHandler:^CLLocation * {
        return [[CLLocation alloc] initWithLatitude:43.393 longitude:-1.456];
        
    } andStartHandler:^(ISError * error, NSArray * newPackages) {
        //Hide HUD
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        if (error) {
            //You could even try to start using your last known data
            [self startWithErrorMessage:@"Start has failed"];
            
        } else if ([newPackages count] > 0) { //New packages available
            //Update HUD
            m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            [m_hud setLabelText:@"Updating"];
            [m_hud setDetailsLabelText:@"Double tap to cancel"];
        }
        
    } andUpdateHandler:^(ISError * error) {
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
    
    //Update view with packages information
    [self updateTableViewWithCurrentSite];
}

#pragma mark - Cancel

- (IBAction)onHudDoubleTapped:(id)sender {
    //Hide HUD
    [m_hud hide:YES];
    //Cancel task
    [[Insiteo sharedInstance].currentTask cancel];
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
    [self setTitle:@"Initialization All-In-One"];
    
    //Reload item
    UIBarButtonItem * reloadItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(launchAPI)];
    [self.navigationItem setRightBarButtonItem:reloadItem];
    
    m_packages = [[NSArray alloc] init];
    
    //All in one method
    [self launchAPI];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
