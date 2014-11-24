//
//  AppDelegate.m
//  sampleapp
//
//  Created by dev_iphone on 15/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

#import "AppDelegate.h"

#import "InsiteoAPI.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    return YES;
}
							
- (void)applicationDidEnterBackground:(UIApplication *)application {
    if ([[ISInitProvider instance] isInitialized]) {
        [[CCDirector sharedDirector] stopAnimation];
    }
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    if ([[ISInitProvider instance] isInitialized]) {
        [[CCDirector sharedDirector] startAnimation];
    }
}

- (void)applicationWillResignActive:(UIApplication *)application {
    if ([[ISInitProvider instance] isInitialized]) {
        [[CCDirector sharedDirector] pause];
    }
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    if ([[ISInitProvider instance] isInitialized]) {
        [[CCDirector sharedDirector] resume];
    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
