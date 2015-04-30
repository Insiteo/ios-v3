//
//  AppDelegate.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 03/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "AppDelegate.h"

#import "MainTableViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

@synthesize window = m_window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    m_window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    //Start examples
    MainTableViewController * mainController = [[MainTableViewController alloc] init];
    UINavigationController * navigationController = [[UINavigationController alloc] initWithRootViewController:mainController];
    [m_window setRootViewController:navigationController];
    
    [m_window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {

}

- (void)applicationDidEnterBackground:(UIApplication *)application {

}

- (void)applicationWillEnterForeground:(UIApplication *)application {

}

- (void)applicationDidBecomeActive:(UIApplication *)application {

}

- (void)applicationWillTerminate:(UIApplication *)application {

}

@end
