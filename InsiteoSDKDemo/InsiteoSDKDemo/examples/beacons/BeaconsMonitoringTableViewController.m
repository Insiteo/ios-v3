//
//  BeaconsMonitoringTableViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 08/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "BeaconsMonitoringTableViewController.h"

#import "BeaconRegionDetailTableViewController.h"

#import <InsiteoSDK/Insiteo.h>

@interface BeaconsMonitoringTableViewController () {
    //Current beacon regions
    NSArray * m_beaconRegions;
    
    //Used to update table view on entry/exit
    NSMutableArray * m_regionsEntered;
}

@end

@implementation BeaconsMonitoringTableViewController

- (id)init {
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        
    }
    return self;
}

#pragma mark - ISBeaconDelegate

- (void)onEnterBeaconRegion:(ISBeaconRegion *)beaconRegion {
    //If the region is not already known as entered, add it
    if (![m_regionsEntered containsObject:beaconRegion.identifier]) {
        [m_regionsEntered addObject:beaconRegion.identifier];
        
        [self.tableView reloadData];
    }
}

- (void)onExitBeaconRegion:(ISBeaconRegion *)beaconRegion {
    //If the region is entered, remove it
    if ([m_regionsEntered containsObject:beaconRegion.identifier]) {
        [m_regionsEntered removeObject:beaconRegion.identifier];
        
        [self.tableView reloadData];
    }
}

- (void)rangedBeacons:(NSArray *)beacons andReachedProximityBeacons:(NSArray *)reachedProximityBeacons inRegion:(ISBeaconRegion *)beaconRegion andUnknownCLBeacons:(NSArray *)unknownCLBeacons withError:(NSError *)error {
    //If the region is not already known as entered, add it
    if (![m_regionsEntered containsObject:beaconRegion.identifier]) {
        [m_regionsEntered addObject:beaconRegion.identifier];
        
        [self.tableView reloadData];
    }
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return ([m_beaconRegions count] > 0) ? [m_beaconRegions count] : 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return @"Beacon Regions";
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return ([m_beaconRegions count] > 0) ? 80.f : UITableViewAutomaticDimension;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString * CellIdentifier = @"CellIdentifier";
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
        cell.detailTextLabel.numberOfLines = 0;
    }
    
    if ([m_beaconRegions count] == 0) {
        [cell setAccessoryType:UITableViewCellAccessoryNone];
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
        
        [cell.textLabel setText:@"No beacon regions found"];
        
    } else {
        ISBeaconRegion * beaconRegion = [m_beaconRegions objectAtIndex:indexPath.row];
        BOOL isEntered = ([m_regionsEntered containsObject:beaconRegion.identifier]);
        
        [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        [cell setSelectionStyle:UITableViewCellSelectionStyleDefault];
        
        [cell.imageView setImage:(isEntered) ? [UIImage imageNamed:@"ic_ibeacon_in"] : [UIImage imageNamed:@"ic_ibeacon_out"]];
        [cell.textLabel setText:beaconRegion.label];
        [cell.detailTextLabel setText:[NSString stringWithFormat:@"UUID: %@\rMajor: %@, Minor: %@", [beaconRegion.uuid lowercaseString], beaconRegion.major, beaconRegion.minor]];
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if ([m_beaconRegions count] > 0) {
        ISBeaconRegion * beaconRegion = [m_beaconRegions objectAtIndex:indexPath.row];
        BOOL isEntered = ([m_regionsEntered containsObject:beaconRegion.identifier]);
        
        BeaconRegionDetailTableViewController * beaconRegionDetailController = [[BeaconRegionDetailTableViewController alloc] initWithBeaconRegion:beaconRegion andIsEntered:isEntered];
        [self.navigationController pushViewController:beaconRegionDetailController animated:YES];
        
        //Update the delegate
        [[ISBeaconProvider sharedInstance] setDelegate:beaconRegionDetailController];
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setTitle:@"Beacons Example"];
    
    //Start beacon management
    [[ISBeaconProvider sharedInstance] startWithDelegate:self];
    
    //Init with existing beacon regions (could be empty if no beacon regions are define on
    //the back office or if the SDK has not been initialized yet
    m_beaconRegions = [NSArray arrayWithArray:[ISBeaconProvider sharedInstance].beaconRegions];
    
    //Will be used to store current entered regions
    m_regionsEntered = [[NSMutableArray alloc] init];
    
    //Init the API
    [[Insiteo sharedInstance] initializeWithInitializeHandler:^(ISError *error, ISUserSite *suggestedSite, Boolean fromLocalCache) {
        //Refresh the data source
        m_beaconRegions = [NSArray arrayWithArray:[ISBeaconProvider sharedInstance].beaconRegions];
        [self.tableView reloadData];
    }];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (!self.isMovingToParentViewController) {
        //Reset and refresh
        [m_regionsEntered removeAllObjects];
        [self.tableView reloadData];
        
        //Update the delegate
        [[ISBeaconProvider sharedInstance] setDelegate:self];
    }
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    //Clear the delegate
    [[ISBeaconProvider sharedInstance] setDelegate:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
