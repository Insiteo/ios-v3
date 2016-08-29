//
//  AnalyticsViewController.m
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-present Insiteo. All rights reserved.
//

#import "AnalyticsViewController.h"

#import <InsiteoSDK/InsiteoSDK.h>

@interface AnalyticsViewController () <ISAnalyticsDelegate>

@property (strong, nonatomic) IBOutlet UILabel *labelAnalytics;

@end

@implementation AnalyticsViewController

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"Analytics Tracking Example";
    
    // Analytics delegate
    [[ISAnalyticsManager sharedInstance] setDelegate:self];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.labelAnalytics.text = @"";
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    // Clear the delegate
    [[ISAnalyticsManager sharedInstance] setDelegate:nil];
}


#pragma mark - Track Custom Event

- (void)trackCustomEvent {
    // Random 0-2 for the example
    NSUInteger r = arc4random_uniform(3);
    
    ISAnalyticsGenericEvent *myEvent;
    if (r == 0) {
        myEvent = [[ISAnalyticsGenericEvent alloc] initWithEventType:@"user-login-success"];
        myEvent.sParam1 = @"john"; // username
        myEvent.sParam2 = @"facebook"; // account type
        myEvent.iParam1 = 1234; // user external id
    } else if (r == 1) {
        myEvent = [[ISAnalyticsGenericEvent alloc] initWithEventType:@"user-click-on-promo"];
        myEvent.sParam1 = @"john"; // username
        myEvent.iParam1 = 1234; // user external id
        myEvent.iParam2 = 954; // promo id
    } else {
        myEvent = [[ISAnalyticsGenericEvent alloc] initWithEventType:@"debug-ui-test"];
        myEvent.iParam1 = 8;
    }
    
    // Track the event
    [[ISAnalyticsManager sharedInstance] addGenericEvent:myEvent];
}


#pragma mark - IBAction

- (IBAction)onTrackEventButtonTap:(id)sender {
    // Track event
    [self trackCustomEvent];
}

#pragma mark - ISAnalyticsDelegate

- (Boolean)analyticsManagerShouldSendGenericEvent:(ISAnalyticsGenericEvent *)event {
    NSLog(@"Will send generic event with type:%@", event.eventType);
    
    // You are able to avoid analytics tracking event
    if ([event.eventType isEqualToString:@"debug-ui-test"]) {
        // Send it to anywhere else or do what you want with this
        NSLog(@"Button %d clicked", event.iParam1);
        
        // Inform that you do not want to send this event to Insiteo analytics server
        return NO;
    }
    
    // Update UI
    self.labelAnalytics.text = [NSString stringWithFormat:@"Last event type: `%@`", event.eventType];
    
    // Otherwise return YES to track the event.
    return YES;
}

@end
