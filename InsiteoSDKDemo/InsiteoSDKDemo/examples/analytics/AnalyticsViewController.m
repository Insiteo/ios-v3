//
//  AnalyticsViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 13/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "AnalyticsViewController.h"

#import <MBProgressHUD/MBProgressHUD.h>

@interface AnalyticsViewController () {
    //Label displaying the number of generic events send
    UILabel * m_label;
    //Number of generic event send
    int m_genericEventCount;
    //Info HUD
    MBProgressHUD * m_hud;
}

@end

@implementation AnalyticsViewController

#pragma mark - Init API (see Init API Example for more details)

- (void)launchAPI {
    //Create cancelable progress HUD. Canceling dialog will also cancel init task
    m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [m_hud setMode:MBProgressHUDModeIndeterminate];
    [m_hud setLabelText:@"Initializing"];
    [m_hud setDetailsLabelText:@"Double tap to cancel"];
    
    UITapGestureRecognizer * tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onHudDoubleTapped:)];
    [tapGestureRecognizer setNumberOfTapsRequired:2];
    [m_hud addGestureRecognizer:tapGestureRecognizer];
    
    //Launch
    [[Insiteo sharedInstance] launchWithInitializeHandler:^(ISError *error, ISUserSite *suggestedSite, Boolean fromLocalCache) {
        NSLog(@"Initialization done: %@", (error == nil) ? @"success" : @"fail");
        
    } andChooseSiteHandler:nil andStartHandler:^(ISError * error, NSArray * newPackages) {
        //Hide HUD
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        //New packages ?
        if ([newPackages count] > 0) {
            //Update HUD
            m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            [m_hud setLabelText:@"Updating"];
            [m_hud setDetailsLabelText:@"Double tap to cancel"];
            
        } else {
            //You could even try to start using your last known data
            [self startWithErrorMessage:(error) ? @"Start has failed" : nil];
        }
        
    } andUpdateHandler:^(ISError * error) {
        //Hide HUD
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        //Launch site
        [self startWithErrorMessage:(error) ? @"Update has failed" : nil];
        
    } andUpdateProgressHandler:^(ISEPackageType packageType, Boolean download, int progress, int total) {
        //Update HUD progress
        [m_hud setMode:MBProgressHUDModeDeterminate];
        [m_hud setProgress:0.0];
        [m_hud setLabelText:download ? @"Downloading" : @"Installing"];
        [m_hud setProgress:(float)progress/(float)total];
    }];
}


- (IBAction)onHudDoubleTapped:(id)sender {
    [m_hud hide:YES];
    //Cancel Insiteo current task
    [[Insiteo sharedInstance].currentTask cancel];
}


#pragma mark - Start

- (void)startWithErrorMessage:(NSString *)errorMessage {
    //Error HUD
    if (errorMessage) {
        m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        [m_hud setMode:MBProgressHUDModeText];
        [m_hud setLabelText:@"Error"];
        [m_hud setDetailsLabelText:errorMessage];
        [m_hud hide:YES afterDelay:2];
        
        //Create a generic event when starting with error
        ISAnalyticsGenericEvent * genericEvent = [[ISAnalyticsGenericEvent alloc] initWithEventType:@"start_error_event"];
        [genericEvent setSParam1:errorMessage];
        [[ISAnalyticsManager sharedInstance] addGenericEvent:genericEvent];
        
    } else {
        //Create a generic event when starting with success
        ISAnalyticsGenericEvent * genericEvent = [[ISAnalyticsGenericEvent alloc] initWithEventType:@"start_success_event"];
        [[ISAnalyticsManager sharedInstance] addGenericEvent:genericEvent];
    }
}


#pragma mark - ISPAnalyticsListener

- (Boolean)analyticsManagerShouldSendGenericEvent:(ISAnalyticsGenericEvent *)event {
    //You could check when an event is send through this callback
    NSLog(@"Will send generic event with type:%@", event.eventType);
    
    //For example, you could override the sending of an event, by checking its type
    if ([event.eventType isEqualToString:@"start_error_event"]) {
        return NO;
    }
    
    //Update count
    m_genericEventCount++;
    
    //Update label
    NSString * eventCountString = [NSString stringWithFormat:@"Generic events send: %i", m_genericEventCount];
    CGSize labelSize = [eventCountString sizeWithFont:[UIFont systemFontOfSize:16.0] constrainedToSize:CGSizeMake(380, 20) lineBreakMode:NSLineBreakByTruncatingTail];
    CGRect frame = CGRectMake(self.view.frame.size.width/2 - labelSize.width/2, self.view.frame.size.height/2 - labelSize.height/2, labelSize.width, labelSize.height);
    [m_label setFrame:frame];
    [m_label setText:eventCountString];
    [m_label sizeToFit];
    
    //For other event just return as default
    return YES;
}


#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //UI
    [self.view setBackgroundColor:[UIColor whiteColor]];
    
    m_genericEventCount = 0;
    
    //Add label
    NSString * eventCountString = [NSString stringWithFormat:@"Generic events send: %i", m_genericEventCount];
    CGSize labelSize = [eventCountString sizeWithFont:[UIFont systemFontOfSize:16.0] constrainedToSize:CGSizeMake(380, 20) lineBreakMode:NSLineBreakByTruncatingTail];
    CGRect frame = CGRectMake(self.view.frame.size.width/2 - labelSize.width/2, self.view.frame.size.height/2 - labelSize.height/2, labelSize.width, labelSize.height);
    m_label = [[UILabel alloc] initWithFrame:frame];
    [m_label setText:eventCountString];
    [m_label sizeToFit];
    m_label.autoresizingMask = (UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin |
                                UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleTopMargin);
    [self.view addSubview:m_label];
    
    //Analytics delegate
    [[ISAnalyticsManager sharedInstance] setDelegate:self];
    
    //Init API
    [self launchAPI];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    //Clear the delegate
    [[ISAnalyticsManager sharedInstance] setDelegate:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
