//
//  BeaconsTableViewController.m
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-present Insiteo. All rights reserved.
//

#import "BeaconsTableViewController.h"

#import "BeaconRegionDetailsTableViewController.h"

#import <InsiteoSDK/InsiteoSDK.h>

@interface BeaconsTableViewController () <ISBeaconDelegate> {
    NSArray *_beaconRegions;
    // Set of entered region identifiers
    NSMutableSet *_enteredRegions;
}

@end

@implementation BeaconsTableViewController

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Start beacon management
    [[ISBeaconProvider sharedInstance] startWithDelegate:self];
    
    // Init with existing iBeacon regions defined on the Back office. If no regions are configured, this array will be
    // empty.
    // Note: you must have initialized the SDK at least once.
    NSArray *currentRegions = [ISBeaconProvider sharedInstance].beaconRegions;
    _beaconRegions = currentRegions;
    
    // Will be used to keep entered regions identifiers (for UI)
    _enteredRegions = [[NSMutableSet alloc] init];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    // Be the delegate again
    [[ISBeaconProvider sharedInstance] setDelegate:self];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return ([_beaconRegions count] > 0) ? [_beaconRegions count] : 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return @"Beacon Regions";
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return ([_beaconRegions count] > 0) ? 80.f : UITableViewAutomaticDimension;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    if ([_beaconRegions count] == 0) {
        static NSString * CellUndefinedIdentifier = @"CellUndefinedIdentifier";
        cell = [tableView dequeueReusableCellWithIdentifier:CellUndefinedIdentifier forIndexPath:indexPath];
        
    } else {
        static NSString * CellBeaconIdentifier = @"CellBeaconIdentifier";
        cell = [tableView dequeueReusableCellWithIdentifier:CellBeaconIdentifier forIndexPath:indexPath];
        
        ISBeaconRegion *region = [_beaconRegions objectAtIndex:indexPath.row];
        BOOL isEntered = ([_enteredRegions containsObject:region.identifier]);
        cell.imageView.tintColor = (isEntered) ? [UIColor greenColor] : [UIColor redColor];
        
        // Info
        NSMutableAttributedString *regionAttributedTitle =
        [[NSMutableAttributedString alloc] initWithString:region.label
                                               attributes:@{ NSForegroundColorAttributeName: [UIColor blackColor],
                                                             NSFontAttributeName:
                                                                 [UIFont systemFontOfSize:16
                                                                                   weight:UIFontWeightLight] }];
        
        NSString *regionInfo = [NSString stringWithFormat:@"\nUUID: %@\nMajor: %@\nMinor: %@",
                                [region.uuid lowercaseString], region.major ?: @"X", region.minor ?: @"X"];
        NSMutableAttributedString *regionAttributedInfo =
        [[NSMutableAttributedString alloc] initWithString:regionInfo
                                               attributes:@{ NSForegroundColorAttributeName: [UIColor blackColor],
                                                             NSFontAttributeName:
                                                                 [UIFont systemFontOfSize:11
                                                                                   weight:UIFontWeightLight] }];
        [regionAttributedTitle appendAttributedString:regionAttributedInfo];
        cell.textLabel.attributedText = regionAttributedTitle;
    }
    
    return cell;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"RegionDetailsIdentifier"]) {
        UIViewController *destinationController = [segue destinationViewController];
        BeaconRegionDetailsTableViewController *detailsController =
        (BeaconRegionDetailsTableViewController *)destinationController;
        
        // Update delegate
        [[ISBeaconProvider sharedInstance] setDelegate:detailsController];
        
        // Get the row index
        UITableViewCell *cell = (UITableViewCell *)sender;
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        
        // Pass the selected region and a boolean to indicate current state
        ISBeaconRegion *region = [_beaconRegions objectAtIndex:indexPath.row];
        BOOL alreadyEntered = [_enteredRegions containsObject:region.identifier];
        [detailsController setRegion:region isAlreadyEntered:alreadyEntered];
    }
}

#pragma mark - ISBeaconDelegate

- (void)onEnterBeaconRegion:(ISBeaconRegion *)beaconRegion {
    // If the region is not already checked as entered
    if (![_enteredRegions containsObject:beaconRegion.identifier]) {
        [_enteredRegions addObject:beaconRegion.identifier];
        // Refresh UI
        [self.tableView reloadData];
    }
}

- (void)onExitBeaconRegion:(ISBeaconRegion *)beaconRegion {
    // If the region was checked as entered
    if ([_enteredRegions containsObject:beaconRegion.identifier]) {
        [_enteredRegions removeObject:beaconRegion.identifier];
        // Refresh UI
        [self.tableView reloadData];
    }
}

- (void)rangedBeacons:(NSArray *)beacons
andReachedProximityBeacons:(NSArray *)reachedProximityBeacons
             inRegion:(ISBeaconRegion *)beaconRegion
  andUnknownCLBeacons:(NSArray *)unknownCLBeacons
            withError:(NSError *)error {
    // If the region is not already checked as entered
    if (![_enteredRegions containsObject:beaconRegion.identifier]) {
        [_enteredRegions addObject:beaconRegion.identifier];
        // Refresh UI
        [self.tableView reloadData];
    }
}

- (BOOL)shouldPresentLocalNotificationOnBeaconRegionEntry:(ISBeaconRegion *)beaconRegion {
    // By default, if the beacon region has a notification message configured, the SDK will automatically present a
    // `UILocalNotification` on entry. You can override the process by sending the notification on your own, or simply
    // disable the presentation by returning `NO`. Otherwise, keep `YES`.
    return YES;
}

@end
