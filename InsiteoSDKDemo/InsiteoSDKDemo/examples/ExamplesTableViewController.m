//
//  ExamplesTableViewController.m
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-present Insiteo. All rights reserved.
//

#import "ExamplesTableViewController.h"

#import "SDKInitTableViewController.h"
#import "MapViewController.h"
#import "BeaconsTableViewController.h"
#import "AnalyticsViewController.h"

#import <InsiteoSDK/InsiteoSDK.h>

// Sections
typedef NS_ENUM(NSUInteger, ExamplesSections) {
    ExamplesSectionInit,
    ExamplesSectionBeacons,
    ExamplesSectionMap,
    ExamplesSectionAnalytics,
    ExamplesSectionLast,
};

// Init examples
typedef NS_ENUM(NSUInteger, ExamplesInitRows) {
    ExamplesInitRowStepByStep,
    ExamplesInitRowAllInOne,
    ExamplesInitRowLast,
};

// Map examples
typedef NS_ENUM(NSUInteger, ExamplesMapRows) {
    ExamplesMapRowMapRto,
    ExamplesMapRowMapLoc,
    ExamplesMapRowMapLocGeofence,
    ExamplesMapRowMapLocIti,
    ExamplesMapRowLast,
};

@implementation ExamplesTableViewController

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = [NSString stringWithFormat:@"%@ - %@",
                  [NSBundle mainBundle].infoDictionary[@"CFBundleDisplayName"],
                  ISApiVersion];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    // Update
    [self.tableView reloadData];
}

#pragma mark - Table View

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return ExamplesSectionLast;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == ExamplesSectionInit) {
        return ExamplesInitRowLast;
    } else if (section == ExamplesSectionMap) {
        return ExamplesMapRowLast;
    }
    return 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *title;
    switch (section) {
        case ExamplesSectionInit:
            title = @"SDK Usage";
            break;
        case ExamplesSectionMap:
            title = @"Map / Location / Itinerary";
            break;
        case ExamplesSectionBeacons:
            title = @"iBeacon";
            break;
        case ExamplesSectionAnalytics:
            title = @"Analytics";
            break;
        default:
            break;
    }
    return title;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    if (section == ExamplesSectionInit) {
        BOOL InsiteoSDKIsInitialized = [[Insiteo sharedInstance] hasCurrentSite];
        return (!InsiteoSDKIsInitialized) ? @"Launch one SDK init example to enable the others" : nil;
    }
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"ExampleCellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    
    NSString *title, *details;
    UIImage *image;
    UIColor *tintColor;
    
    switch (indexPath.section) {
        case ExamplesSectionInit:
            image = [UIImage imageNamed:@"ic_init"];
            tintColor = [UIColor colorWithRed:105.0/255.0 green:130.0/255.0 blue:125.0/255.0 alpha:1];
            switch (indexPath.row) {
                case ExamplesInitRowAllInOne:
                    title = @"SDK Init All-In-One";
                    details = @"Launch process to init/update/start automatically";
                    break;
                case ExamplesInitRowStepByStep:
                    title = @"SDK Init Step-By-Step";
                    details = @"Alternative process to initialize, update and start individually";
                    break;
                default:
                    break;
            }
            break;
        case ExamplesSectionMap:
            image = [UIImage imageNamed:@"ic_map"];
            tintColor = [UIColor colorWithRed:0 green:179.0/255.0 blue:140.0/255.0 alpha:1];
            switch (indexPath.row) {
                case ExamplesMapRowMapRto:
                    title = @"Generic & Custom RTO Rendering";
                    details = @"How to use Generic RTO and Custom RTO rendering";
                    break;
                case ExamplesMapRowMapLoc:
                    title = @"User Location + Rendering";
                    details = @"How to display and customize location rendering";
                    break;
                case ExamplesMapRowMapLocGeofence:
                    title = @"Geofencing + Rendering";
                    details = @"How to display geofencing areas to help debugging";
                    break;
                case ExamplesMapRowMapLocIti:
                    title = @"Itineraries + Rendering";
                    details = @"How to display and customize itineraries";
                    break;
                default:
                    break;
            }
            break;
        case ExamplesSectionBeacons:
            image = [UIImage imageNamed:@"ic_ibeacon"];
            tintColor = [UIColor colorWithRed:5.0/255.0 green:98.0/255.0 blue:124.0/255.0 alpha:1];
            title = @"Beacon Monitoring";
            details = @"UI according to iBeacon detection";
            break;
        case ExamplesSectionAnalytics:
            image = [UIImage imageNamed:@"ic_analytics"];
            tintColor = [UIColor colorWithRed:204.0/255.0 green:98.0/255.0 blue:100.0/255.0 alpha:1];
            title = @"Track Custom Analytics Events";
            details = @"How to manage custom analytics events";
            break;
        default:
            break;
    }
    
    cell.imageView.image = image;
    cell.imageView.tintColor = tintColor;
    
    cell.textLabel.text = title;
    cell.textLabel.textColor = [UIColor blackColor];
    
    cell.detailTextLabel.text = details;
    cell.detailTextLabel.textColor = tintColor;
    
    // Check SDK initialization to disable all examples that require a successfull initialization
    BOOL InsiteoSDKIsInitialized = [[Insiteo sharedInstance] hasCurrentSite];
    if (indexPath.section != ExamplesSectionInit && !InsiteoSDKIsInitialized) {
        cell.userInteractionEnabled = InsiteoSDKIsInitialized;
        cell.imageView.tintColor = [UIColor lightGrayColor];
        cell.detailTextLabel.textColor = [UIColor lightGrayColor];
        cell.textLabel.textColor = [UIColor lightGrayColor];
    } else {
        cell.userInteractionEnabled = YES;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    UIViewController *newController;
    
    switch (indexPath.section) {
        case ExamplesSectionInit: {
            // Init
            SDKInitTableViewController *initController =
            (SDKInitTableViewController *)[self.storyboard instantiateViewControllerWithIdentifier:@"SDKInitExample"];
            initController.exampleInitMode = (InitMode)indexPath.row;
            newController = initController;
            break;
        } case ExamplesSectionMap: {
            // Map
            MapViewController *mapController =
            (MapViewController *)[self.storyboard instantiateViewControllerWithIdentifier:@"MapExample"];
            mapController.exampleMapMode = (MapMode)indexPath.row;
            newController = mapController;
            break;
        } case ExamplesSectionBeacons: {
            // iBeacons
            BeaconsTableViewController *beaconsController =
            (BeaconsTableViewController *)[self.storyboard instantiateViewControllerWithIdentifier:@"BeaconsExample"];
            newController = beaconsController;
            break;
        } case ExamplesSectionAnalytics: {
            // Analytics
            AnalyticsViewController *analyticsController =
            (AnalyticsViewController *)[self.storyboard instantiateViewControllerWithIdentifier:@"AnalyticsExample"];
            newController = analyticsController;
            break;
        } default:
            break;
    }
    
    if (newController) {
        [self.navigationController pushViewController:newController animated:YES];
    }
}

@end
