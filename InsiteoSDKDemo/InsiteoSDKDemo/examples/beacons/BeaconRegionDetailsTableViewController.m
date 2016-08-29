//
//  BeaconRegionDetailTableViewController.m
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-preesnt Insiteo. All rights reserved.
//

#import "BeaconRegionDetailsTableViewController.h"

// Sections
typedef NS_ENUM(NSUInteger, ESections) {
    ESectionBeaconRegion = 0,
    ESectionBeacons,
    ESectionUnknownBeacons,
    ESectionLast
};

// Beacon region rows
typedef NS_ENUM(NSUInteger, EBeaconRegionRows) {
    EBeaconRegionRowState = 0,
    EBeaconRegionRowUUID,
    EBeaconRegionRowMajorMinor,
    EBeaconRegionRowSiteId,
    EBeaconRegionRowMessage,
    EBeaconRegionRowCustomId,
    EBeaconRegionRowLast
};

NSString *NSStringFromCLProximity(CLProximity proximity) {
    NSString *description;
    switch (proximity) {
        case CLProximityUnknown:
            return @"Unknown";
            break;
        case CLProximityImmediate:
            return @"Immediate";
            break;
        case CLProximityNear:
            return @"Near";
            break;
        case CLProximityFar:
            return @"Far";
            break;
    }
    return description;
}

@interface BeaconRegionDetailsTableViewController () {
    // The current beacon region
    ISBeaconRegion *_beaconRegion;
    // Unknow beacons detected
    NSArray *_unknownBeacons;
    // Boolean used to know if the region is currently entered
    BOOL _isEntered;
}

@end

@implementation BeaconRegionDetailsTableViewController

#pragma mark - Initialization

- (void)setRegion:(ISBeaconRegion *)region isAlreadyEntered:(BOOL)alreadyEntered {
    self.title = region.label;
    _beaconRegion = region;
    _isEntered = alreadyEntered;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return ESectionLast;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSInteger rows = 0;
    switch (section) {
        case ESectionBeaconRegion:
            rows = EBeaconRegionRowLast;
            break;
        case ESectionBeacons:
            rows = [_beaconRegion.beacons count];
            break;
        case ESectionUnknownBeacons:
            rows = [_unknownBeacons count];
            break;
    }
    return rows;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *title;
    switch (section) {
        case ESectionBeaconRegion:
            title = @"Beacon region";
            break;
        case ESectionBeacons:
            title = @"Beacons";
            break;
        case ESectionUnknownBeacons:
            title = ([_unknownBeacons count] > 0) ? @"Unknown beacons" : nil;
            break;
    }
    return title;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section {
    if (section == ESectionBeacons) {
        if ([_beaconRegion.beacons count] == 0) {
            return @"No beacon defined for that region";
        }
    }
    return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == ESectionBeacons) {
        return 110.f;
    } else if (indexPath.section == ESectionUnknownBeacons) {
        return 70.f;
    }
    return 50.f;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    
    if (indexPath.section == ESectionBeaconRegion) {
        // Region
        static NSString *regionCellIdentifier = @"RegionCellIdentifier";
        cell = [tableView dequeueReusableCellWithIdentifier:regionCellIdentifier forIndexPath:indexPath];
        
        NSString *title;
        NSString *details;
        UIImage *image;
        
        switch (indexPath.row) {
            case EBeaconRegionRowState:
                details = (_isEntered) ? @"Inside" : @"Outside";
                title = _beaconRegion.label;
                image = [UIImage imageNamed:@"ic_ibeacon"];
                break;
            case EBeaconRegionRowUUID:
                details = @"UUID";
                title = [_beaconRegion.uuid lowercaseString];
                break;
            case EBeaconRegionRowMajorMinor:
                details = @"Major - Minor";
                title = [NSString stringWithFormat:@"%@ - %@", _beaconRegion.major ?: @"X", _beaconRegion.minor ?: @"X"];
                break;
            case EBeaconRegionRowSiteId:
                details = @"Site Identifier";
                title = [NSString stringWithFormat:@"%d", _beaconRegion.siteId];
                break;
            case EBeaconRegionRowMessage:
                details = @"Notification message";
                title = (_beaconRegion.message &&
                         ![_beaconRegion.message isEqualToString:@""]) ? _beaconRegion.message : @"No message defined";
                break;
            case EBeaconRegionRowCustomId:
                details = @"Custom content";
                title = (_beaconRegion.externalId &&
                         ![_beaconRegion.externalId isEqualToString:@""]) ? _beaconRegion.externalId : @"No content defined";
                break;
            default:
                break;
        }
        
        cell.imageView.image = image;
        cell.imageView.tintColor = (_isEntered) ? [UIColor greenColor] : [UIColor redColor];
        cell.textLabel.text = details;
        cell.detailTextLabel.text = title;
        
    } else if (indexPath.section == ESectionBeacons) {
        // Beacons
        static NSString *beaconCellIdentifier = @"BeaconCellIdentifier";
        cell = [tableView dequeueReusableCellWithIdentifier:beaconCellIdentifier forIndexPath:indexPath];
        
        ISBeacon *beacon = [_beaconRegion.beacons objectAtIndex:indexPath.row];
        
        // Info
        NSString *info = [NSString stringWithFormat:
                          @"UUID: %@\nMajor - Minor: %d - %d\nSite Identifier: %d\n"
                          "Custom content: %@\nAccuracy: %.2f m\nRSSI: %ld db",
                          [beacon.uuid lowercaseString],
                          beacon.major,
                          beacon.minor,
                          beacon.siteId,
                          beacon.externalId,
                          beacon.accuracy,
                          (long)beacon.rssi];
        
        NSAttributedString *attributedInfo =
        [[NSAttributedString alloc] initWithString:info
                                        attributes:@{ NSFontAttributeName:
                                                          [UIFont systemFontOfSize:12
                                                                            weight:UIFontWeightLight] }];
        
        cell.textLabel.attributedText = attributedInfo;
        
        // Proximity
        UIColor *detailTintColor;
        cell.detailTextLabel.text = NSStringFromCLProximity(beacon.proximity);
        if (beacon.proximity == CLProximityUnknown) {
            detailTintColor = [UIColor lightTextColor];
        } else if (beacon.proximity <= _beaconRegion.proximity) {
            detailTintColor = [UIColor greenColor];
        }
        cell.detailTextLabel.textColor = detailTintColor;
        cell.imageView.tintColor = detailTintColor;
        
    } else {
        // Unknown beacons
        static NSString *unkwnownBeaconCellIdentifier = @"UnknownBeaconCellIdentifier";
        cell = [tableView dequeueReusableCellWithIdentifier:unkwnownBeaconCellIdentifier forIndexPath:indexPath];
        
        CLBeacon *clBeacon = [_unknownBeacons objectAtIndex:indexPath.row];
        
        // Info
        NSString *info = [NSString stringWithFormat:
                          @"UUID: %@\nMajor - Minor: %@ - %@\nAccuracy: %.2f m\nRSSI: %ld db",
                          [clBeacon.proximityUUID.UUIDString lowercaseString],
                          clBeacon.major,
                          clBeacon.minor,
                          clBeacon.accuracy,
                          (long)clBeacon.rssi];
        
        NSAttributedString *attributedInfo =
        [[NSAttributedString alloc] initWithString:info
                                        attributes:@{ NSFontAttributeName:
                                                          [UIFont systemFontOfSize:12
                                                                            weight:UIFontWeightLight] }];
        
        cell.textLabel.attributedText = attributedInfo;
    }
    
    return cell;
}

#pragma mark - ISBeaconDelegate

- (void)onEnterBeaconRegion:(ISBeaconRegion *)beaconRegion {
    NSLog(@"Enter region");
    if ([beaconRegion.identifier isEqualToString:_beaconRegion.identifier] && !_isEntered) {
        _isEntered = YES;
        // Reload beacon row
        [self.tableView reloadRowsAtIndexPaths:@[ [NSIndexPath indexPathForRow:EBeaconRegionRowState
                                                                     inSection:ESectionBeaconRegion] ]
                              withRowAnimation:UITableViewRowAnimationAutomatic];
    }
}

- (void)onExitBeaconRegion:(ISBeaconRegion *)beaconRegion {
    NSLog(@"Exit region");
    if ([beaconRegion.identifier isEqualToString:_beaconRegion.identifier] && _isEntered) {
        _isEntered = NO;
        // Reload beacon row
        [self.tableView reloadRowsAtIndexPaths:@[ [NSIndexPath indexPathForRow:EBeaconRegionRowState
                                                                     inSection:ESectionBeaconRegion] ]
                              withRowAnimation:UITableViewRowAnimationAutomatic];
    }
}

- (void)onEnterBeacon:(ISBeacon *)beacon forRegion:(ISBeaconRegion *)beaconRegion {
    // You can perform a specific task, or popup or whatever on enter
}

- (void)onExitBeacon:(ISBeacon *)beacon forRegion:(ISBeaconRegion *)beaconRegion {
    // You can perform a specific task, or popup or whatever on exit
}

- (void)rangedBeacons:(NSArray *)beacons andReachedProximityBeacons:(NSArray *)reachedProximityBeacons inRegion:(ISBeaconRegion *)beaconRegion andUnknownCLBeacons:(NSArray *)unknownCLBeacons withError:(NSError *)error {
    NSLog(@"Ranging beacons in region");
    if ([beaconRegion.identifier isEqualToString:_beaconRegion.identifier]) {
        // Rows in table view to reload
        NSMutableArray *rowsToReload = [[NSMutableArray alloc] init];
        
        // Status
        if (!_isEntered) {
            _isEntered = YES;
            [rowsToReload addObject:[NSIndexPath indexPathForRow:EBeaconRegionRowState inSection:ESectionBeaconRegion]];
        }
        
        // Update unknown Beacons
        _unknownBeacons = unknownCLBeacons;
        
        // Refresh UI
        [self.tableView reloadData];
    }
}

@end
