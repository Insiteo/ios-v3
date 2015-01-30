//
//  AppDelegate.m
//  sampleapp
//
//  Created by dev_iphone on 15/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

#pragma mark - ISBeacon

- (void)onEnterBeaconRegion:(ISBeaconRegion *)beaconRegion {
    
}

- (void)onExitBeaconRegion:(ISBeaconRegion *)beaconRegion {
    
}

- (void)onEnterBeacon:(ISBeacon *)beacon forRegion:(ISBeaconRegion *)beaconRegion andProximity:(CLProximity)proximity {
    
}

- (void)onExitBeacon:(ISBeacon *)beacon forRegion:(ISBeaconRegion *)beaconRegion andProximity:(CLProximity)proximity {
    
}


#pragma mark - Application

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //Start the beacon provider and set the ISPBeaconListener
    [[ISBeaconProvider sharedInstance] startWithListener:self];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

#define kTimeToReinit 3600 //ex: every 1 hour, beacon regions are updated on the back office

- (void)applicationDidBecomeActive:(UIApplication *)application {
    //Check if user is authenticated
    if ([[Insiteo sharedInstance] isAuthenticated]) {
        //Check the interval between now
        double interval = [[NSDate date] timeIntervalSinceDate:[Insiteo currentUser].lastInitializationDate];
        
        if (interval > kTimeToReinit) {
            //Reinit the API, using the previous configuration
            [[Insiteo sharedInstance] initializeWithInitializeHandler:nil andChooseSiteHandler:nil];
        }
    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
