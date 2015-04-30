//
//  MainTableViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 03/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "MainTableViewController.h"

//Init
#import "InitAllInOneViewController.h"
#import "InitStepByStepViewController.h"
//Beacons
#import "BeaconsMonitoringTableViewController.h"
//Map
#import "MapRtoViewController.h"
#import "MapLocViewController.h"
#import "MapLocGeofencingViewController.h"
#import "MapLocItiViewController.h"
//Analytics
#import "AnalyticsViewController.h"

//Sections
typedef NS_ENUM(NSUInteger, ExamplesSections) {
    ExamplesSectionInit,
    ExamplesSectionBeacons,
    ExamplesSectionMap,
    ExamplesSectionAnalytics,
    ExamplesSectionLast,
};

//Init examples
typedef NS_ENUM(NSUInteger, ExamplesInitRows) {
    ExamplesInitRowAllInOne,
    ExamplesInitRowStepByStep,
    ExamplesInitRowLast,
};

//Map examples
typedef NS_ENUM(NSUInteger, ExamplesMapRows) {
    ExamplesMapRowMapRto,
    ExamplesMapRowMapLoc,
    ExamplesMapRowMapLocGeofence,
    ExamplesMapRowMapLocIti,
    ExamplesMapRowLast,
};


@interface MainTableViewController ()

@end

@implementation MainTableViewController

- (id)init {
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        
    }
    return self;
}

#pragma mark - Table View

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return ExamplesSectionLast;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == ExamplesSectionInit) {
        return @"API Initialization";
        
    } else if (section == ExamplesSectionBeacons) {
        return @"Beacons";
        
    } else if (section == ExamplesSectionMap) {
        return @"Map";
        
    } else if (section == ExamplesSectionAnalytics) {
        return @"Analytics";
    }
    
    return nil;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == ExamplesSectionInit) {
        return ExamplesInitRowLast;
        
    } else if (section == ExamplesSectionMap) {
        return ExamplesMapRowLast;
    }
    
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString * CellIdentifier = @"CellIdentifier";
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
        [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
    }
    
    if (indexPath.section == ExamplesSectionInit) {
        if (indexPath.row == ExamplesInitRowAllInOne) {
             [cell.textLabel setText:@"Init All-In-One"];
            
        } else if (indexPath.row == ExamplesInitRowStepByStep) {
            [cell.textLabel setText:@"Init Step-By-Step"];
        }
        
    } else if (indexPath.section == ExamplesSectionBeacons) {
        [cell.textLabel setText:@"Beacons Monitoring"];
        
    } else if (indexPath.section == ExamplesSectionMap) {
        if (indexPath.row == ExamplesMapRowMapRto) {
            [cell.textLabel setText:@"Map + RTO"];
            
        } else if (indexPath.row == ExamplesMapRowMapLoc) {
            [cell.textLabel setText:@"Map + Location"];
            
        } else if (indexPath.row == ExamplesMapRowMapLocGeofence) {
            [cell.textLabel setText:@"Map + Location + Geofencing"];
            
        } else if (indexPath.row == ExamplesMapRowMapLocIti) {
            [cell.textLabel setText:@"Map + Location + Itinerary"];
            
        }
        
    } else if (indexPath.section == ExamplesSectionAnalytics) {
        [cell.textLabel setText:@"Analytics Generic + Overriding"];
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UIViewController * newController;
    
    if (indexPath.section == ExamplesSectionInit) {
        if (indexPath.row == ExamplesInitRowAllInOne) {
            newController = [[InitAllInOneViewController alloc] init];
            
        } else if (indexPath.row == ExamplesInitRowStepByStep) {
            newController = [[InitStepByStepViewController alloc] init];
        }
        
    } else if (indexPath.section == ExamplesSectionBeacons) {
        newController = [[BeaconsMonitoringTableViewController alloc] init];
        
    } else if (indexPath.section == ExamplesSectionMap) {
        if (indexPath.row == ExamplesMapRowMapRto) {
            newController = [[MapRtoViewController alloc] init];
            
        } else if (indexPath.row == ExamplesMapRowMapLoc) {
            newController = [[MapLocViewController alloc] init];
            
        } else if (indexPath.row == ExamplesMapRowMapLocGeofence) {
            newController = [[MapLocGeofencingViewController alloc] init];

        } else if (indexPath.row == ExamplesMapRowMapLocIti) {
            newController = [[MapLocItiViewController alloc] init];
            
        }
        
    } else if (indexPath.section == ExamplesSectionAnalytics) {
        newController = [[AnalyticsViewController alloc] init];
    }
    
    if (newController) {
        [self.navigationController pushViewController:newController animated:YES];
    }
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setTitle:[NSString stringWithFormat:@"%@ %@", @"InsiteoSDK Demo", ISApiVersion]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
