//
//  BeaconRegionDetailTableViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 08/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "BeaconRegionDetailTableViewController.h"

//Sections
typedef NS_ENUM(NSUInteger, ESections) {
    ESectionBeaconRegion = 0,
    ESectionBeaconReachedProximity,
    ESectionBeacons,
    ESectionUnknownBeacons,
    ESectionLast
};

//Beacon region rows
typedef NS_ENUM(NSUInteger, EBeaconRegionRows) {
    EBeaconRegionRowState = 0,
    EBeaconRegionRowLabel,
    EBeaconRegionRowUUID,
    EBeaconRegionRowMajorMinor,
    EBeaconRegionRowSiteId,
    EBeaconRegionRowMessage,
    EBeaconRegionRowCustomId,
    EBeaconRegionRowLast
};

@interface BeaconRegionDetailTableViewController () {
    //The current beacon region
    ISBeaconRegion * m_beaconRegion;
    //Unknow beacons detected
    NSArray * m_unknownBeacons;
    //Boolean used to know if the region is currently entered
    BOOL m_isEntered;
}

@end

@implementation BeaconRegionDetailTableViewController

- (id)initWithBeaconRegion:(ISBeaconRegion *)beaconRegion andIsEntered:(BOOL)entered {
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        m_beaconRegion = beaconRegion;
        m_isEntered = entered;
    }
    return self;
}

#pragma mark - ISBeaconDelegate

- (void)onEnterBeaconRegion:(ISBeaconRegion *)beaconRegion {
    if ([beaconRegion.identifier isEqualToString:m_beaconRegion.identifier] && !m_isEntered) {
        m_isEntered = YES;
        //Reload beacon row
        [self.tableView reloadRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:EBeaconRegionRowState inSection:ESectionBeaconRegion]] withRowAnimation:UITableViewRowAnimationNone];
    }
}

- (void)onExitBeaconRegion:(ISBeaconRegion *)beaconRegion {
    if ([beaconRegion.identifier isEqualToString:m_beaconRegion.identifier] && m_isEntered) {
        m_isEntered = NO;
        //Reload beacon row
        [self.tableView reloadRowsAtIndexPaths:@[[NSIndexPath indexPathForRow:EBeaconRegionRowState inSection:ESectionBeaconRegion]] withRowAnimation:UITableViewRowAnimationNone];
    }
}

- (void)onEnterBeacon:(ISBeacon *)beacon forRegion:(ISBeaconRegion *)beaconRegion {
    //You could perform a specific task, or popup or whatever on enter
}

- (void)onExitBeacon:(ISBeacon *)beacon forRegion:(ISBeaconRegion *)beaconRegion {
    //You could perform a specific task, or popup or whatever on enter
}

- (void)rangedBeacons:(NSArray *)beacons andReachedProximityBeacons:(NSArray *)reachedProximityBeacons inRegion:(ISBeaconRegion *)beaconRegion andUnknownCLBeacons:(NSArray *)unknownCLBeacons withError:(NSError *)error {
    if ([beaconRegion.identifier isEqualToString:m_beaconRegion.identifier]) {
        //Rows in table view to reload
        NSMutableArray * rowsToReload = [[NSMutableArray alloc] init];
        
        //Status
        if (!m_isEntered) {
            m_isEntered = YES;
            [rowsToReload addObject:[NSIndexPath indexPathForRow:EBeaconRegionRowState inSection:ESectionBeaconRegion]];
        }
        
        //Beacons
        if ([m_beaconRegion.beacons count] > 0) {
            for (int i = 0; i < [m_beaconRegion.beacons count]*2; i++) {
                [rowsToReload addObject:[NSIndexPath indexPathForRow:i inSection:ESectionBeacons]];
            }
        }
        
        [self.tableView reloadRowsAtIndexPaths:rowsToReload withRowAnimation:UITableViewRowAnimationNone];
        
        //UnknownConfiguredBeacons
        m_unknownBeacons = [NSArray arrayWithArray:unknownCLBeacons];
        [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:ESectionUnknownBeacons] withRowAnimation:UITableViewRowAnimationNone];
    }
}

- (BOOL)shouldPresentLocalNotificationOnBeaconRegionEntry:(ISBeaconRegion *)beaconRegion {
    //First case, disable notification for each Beacon Region
    //    return NO;
    
    //Second case, only disable for a specific Beacon Region (ex: externalId == @"no-notif")
    //    if ([beaconRegion.externalId isEqualToString:@"no-notif"]) {
    //        return NO;
    //    } else {
    //        return YES;
    //    }
    
    //Third case, disable notification and present a UILocalNotification on your own
    //    UILocalNotification * notification = [[UILocalNotification alloc] init];
    //    notification.alertBody = [NSString stringWithFormat:@"%@", beaconRegion.externalId];
    //    notification.soundName = UILocalNotificationDefaultSoundName;
    //    return NO;
    
    //Default case
    return YES;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return ESectionLast;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == ESectionBeaconRegion) {
        return EBeaconRegionRowLast;
        
    } else if (section == ESectionBeaconReachedProximity) {
        return 1;
        
    } else if (section == ESectionBeacons) {
        return ([m_beaconRegion.beacons count] > 0) ? [m_beaconRegion.beacons count]*2 : 1;
        
    } else if (section == ESectionUnknownBeacons && [m_unknownBeacons count] > 0) {
        return [m_unknownBeacons count];
    }
    
    return 0;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == ESectionBeaconRegion) {
        return @"Beacon region";
        
    } else if (section == ESectionBeaconReachedProximity) {
        return @"Beacon triggering proximity";
        
    } else if (section == ESectionBeacons) {
        return @"Beacons";
        
    } else if (section == ESectionUnknownBeacons && [m_unknownBeacons count] > 0) {
        return @"Unknwon beacons";
    }
    
    return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == ESectionBeacons && [m_beaconRegion.beacons count] > 0 && indexPath.row % 2 == 1) {
        return 120.f;
        
    } else if (indexPath.section == ESectionUnknownBeacons) {
        return 90.f;
    }
    
    return 44.f;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString * CellIdentifier = @"CellIdentifier";
    
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
        [cell.detailTextLabel setNumberOfLines:0];
        [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    }
    
    [cell setAccessoryView:nil];
    [cell.textLabel setText:nil];
    [cell.detailTextLabel setText:nil];
    [cell.detailTextLabel setTextColor:[UIColor blackColor]];
    [cell setAccessoryType:UITableViewCellAccessoryNone];
    
    if (indexPath.section == ESectionBeaconRegion) {
        if (indexPath.row == EBeaconRegionRowState) {
            UIImageView * imageView = [[UIImageView alloc] initWithImage:(m_isEntered) ? [UIImage imageNamed:@"ic_ibeacon_in"] : [UIImage imageNamed:@"ic_ibeacon_out"]];
            [cell setAccessoryView:imageView];
            [cell.textLabel setText:@"Status"];
            [cell.detailTextLabel setText:(m_isEntered) ? @"IN" : @"OUT"];
            
        } else if (indexPath.row == EBeaconRegionRowLabel) {
            [cell.textLabel setText:@"Label"];
            [cell.detailTextLabel setText:m_beaconRegion.label];
            
        } else if (indexPath.row == EBeaconRegionRowUUID) {
            [cell.textLabel setText:@"UUID"];
            [cell.detailTextLabel setText:[m_beaconRegion.uuid lowercaseString]];
            
        } else if (indexPath.row == EBeaconRegionRowMajorMinor) {
            [cell.textLabel setText:@"Major - Minor"];
            [cell.detailTextLabel setText:[NSString stringWithFormat:@"%@ - %@", m_beaconRegion.major, m_beaconRegion.minor]];
            
        } else if (indexPath.row == EBeaconRegionRowSiteId) {
            [cell.textLabel setText:@"Site Id"];
            [cell.detailTextLabel setText:[NSString stringWithFormat:@"%d", m_beaconRegion.siteId]];
            
        } else if (indexPath.row == EBeaconRegionRowMessage) {
            [cell.textLabel setText:@"Message"];
            [cell.detailTextLabel setText:m_beaconRegion.message];
            
        } else if (indexPath.row == EBeaconRegionRowCustomId) {
            [cell.textLabel setText:@"Custom attribute"];
            [cell.detailTextLabel setText:m_beaconRegion.externalId];
        }
        
    } else if (indexPath.section == ESectionBeaconReachedProximity) {
        [cell.textLabel setText:@"Proximity"];
        [cell.detailTextLabel setText:[self nameForProximity:m_beaconRegion.proximity]];
        
    } else if (indexPath.section == ESectionBeacons) {
        
        if ([m_beaconRegion.beacons count] == 0) {
            [cell.textLabel setText:@"No configured beacons found"];
            
        } else {
            if (indexPath.row % 2 == 0) {
                //Beacon label + proximity
                NSInteger index = indexPath.row / 2;
                ISBeacon * beacon = [m_beaconRegion.beacons objectAtIndex:index];
                [cell.detailTextLabel setText:[self nameForProximity:beacon.proximity]];
                if (beacon.proximity != CLProximityUnknown && beacon.proximity <= beacon.proximity) {
                    [cell.detailTextLabel setTextColor:[UIColor greenColor]];
                }
                
            } else {
                //Info
                NSInteger index = (indexPath.row - 1) / 2;
                ISBeacon * beacon = [m_beaconRegion.beacons objectAtIndex:index];
                NSString * detail = [NSString stringWithFormat:@"UUID: %@\nMajor: %d, Minor: %d\nSite Id: %d\nCustom Id: %@\nAccuracy: %f m\nRSSI: %ld db", [beacon.uuid lowercaseString], beacon.major, beacon.minor, beacon.siteId, beacon.externalId, beacon.accuracy, (long)beacon.rssi];
                [cell.detailTextLabel setText:detail];
            }
        }
        
    } else if (indexPath.section == ESectionUnknownBeacons && [m_unknownBeacons count] > 0) {
        CLBeacon * clBeacon = [m_unknownBeacons objectAtIndex:indexPath.row];
        NSString * detail = [NSString stringWithFormat:@"UUID: %@\nMajor: %d, Minor: %d\nProximity: %@\nAccuracy: %f m\nRSSI: %ld db", [clBeacon.proximityUUID.UUIDString lowercaseString], [clBeacon.major intValue], [clBeacon.minor intValue], [self nameForProximity:clBeacon.proximity], clBeacon.accuracy, (long)clBeacon.rssi];
        [cell.detailTextLabel setText:detail];
    }
    
    return cell;
}

#pragma mark - Utils

- (NSString *)nameForProximity:(CLProximity)proximity {
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
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setTitle:m_beaconRegion.label];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
