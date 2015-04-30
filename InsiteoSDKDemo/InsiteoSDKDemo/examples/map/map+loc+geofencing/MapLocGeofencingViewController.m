//
//  MapLocGeofencingViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 10/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "MapLocGeofencingViewController.h"

#import <MBProgressHUD/MBProgressHUD.h>

@interface MapLocGeofencingViewController () {
    //Map view
    ISMapView * m_mapView;
    //Location provider
    ISLocationProvider * m_locationProvider;
    //Geofencing provider
    ISGeofenceProvider * m_geofenceProvider;
    //Info HUD
    MBProgressHUD * m_hud;
    //Button location
    UIButton * m_buttonLoc;
    //Spinner added on location button (to wait until loc starts)
    UIActivityIndicatorView * m_spinner;
}

@end

@implementation MapLocGeofencingViewController

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
        
        if (error) {
            //You could even try to start using your last known data
            [self startWithErrorMessage:@"Start has failed"];
            
        } else if ([newPackages count] > 0) {
            //Update HUD
            m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            [m_hud setLabelText:@"Updating"];
            [m_hud setDetailsLabelText:@"Double tap to cancel"];
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
    }
    
    //Map creation (see Map+RTO example for more details)
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeMapData]) {
        if ([Insiteo currentUser].renderMode == ISERenderMode2D) {
            [ISMap2DView getMap2DViewWithFrame:self.view.frame andMapDelegate:self andHandler:^(ISMap2DView * map2DView) {
                [self createMap:map2DView];
            }];
            
        } else {
            [ISMap3DView getMap3DViewWithFrame:self.view.frame andMapDelegate:self andHandler:^(ISMap3DView * map3DView) {
                [self createMap:map3DView];
            }];
        }
        
    } else {
        NSLog(@"Map Data package not found.");
    }
}

#pragma mark - Map

- (void)createMap:(ISMapView *)mapView {
    m_mapView = mapView;
    [self.view addSubview:m_mapView];
    
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeLocation]) {
        //Init Location Provider and add its renderer
        m_locationProvider = [[ISLocationProvider alloc] init];
        [m_mapView addRenderer:m_locationProvider.renderer];
        
        //Add loc button
        m_buttonLoc = [UIButton buttonWithType:UIButtonTypeCustom];
        [m_buttonLoc setFrame:CGRectMake(self.view.frame.size.width / 2.0 - 20, self.view.frame.size.height - 48, 40, 40)];
        [m_buttonLoc setBackgroundImage:[UIImage imageNamed:@"btn_location"] forState:UIControlStateNormal];
        [m_buttonLoc addTarget:self action:@selector(onLocationButtonPush:) forControlEvents:UIControlEventTouchUpInside];
        m_buttonLoc.autoresizingMask = (UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleTopMargin);
        [self.view addSubview:m_buttonLoc];
        
        //Check if Geonfencing Package is available
        if ([[Insiteo currentSite] hasPackage:ISEPackageTypeGeofencing]) {
            //Init the geofencing provider using previous created location provider
            m_geofenceProvider = (ISGeofenceProvider *)[m_locationProvider getLbsModule:ISELbsModuleTypeGeofencing];
            
            //If you want to debug and display geofencing area you could use the geofencing renderer
            [m_mapView addRenderer:m_geofenceProvider.renderer];
            [m_mapView setRendererDisplayWithRTOClass:[ISGfxGeofenceArea class] andDisplay:YES];
        }
    }
    
    //Start the rendering
    [m_mapView startRendering];
    
    //Add map changer
    UIButton * buttonMap = [UIButton buttonWithType:UIButtonTypeCustom];
    [buttonMap setFrame:CGRectMake(self.view.frame.size.width - 48, self.view.frame.size.height - 48, 40, 40)];
    [buttonMap setBackgroundImage:[UIImage imageNamed:@"btn_map"] forState:UIControlStateNormal];
    [buttonMap addTarget:self action:@selector(presentMapActionSheet:) forControlEvents:UIControlEventTouchUpInside];
    buttonMap.autoresizingMask = (UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleTopMargin);
    [self.view addSubview:buttonMap];
}

#pragma mark - ISMapViewDelegate

- (void)onMapChangedWithNewMapId:(int)newMapId andMapName:(NSString *)mapName {
    [self setTitle:mapName];
}

- (void)onMapMoved {
    
}

- (void)onMapClicked:(ISPosition *)touchPosition {
    
}

- (void)onMapReleased {
    
}

- (void)onZoneClickedWithZone:(ISZone *)zone {
    
}

- (void)onZoomEnd:(double)newZoom {
    
}

#pragma mark - ISLocationDelegate

- (void)onLocationInitDoneWithSuccess:(Boolean)success andError:(ISError *)error {
    //You could update your UI or do what you want
    NSLog(@"Location init: %@", (error) ? @"error" : @"success");
}

- (void)onLocationReceived:(ISLocation *)location {
    //Do stuff only on first loc
    if (m_locationProvider.lastLocation == nil) {
        //Stop spinner and enable button loc
        [self hideSpinnerOnLocationButton];
    }
    
    //Then you could for exemple center map on each new position received
    //[m_mapView centerMapWithPosition:location.position andAnimated:YES];
}

- (void)onAzimuthReceived:(float)azimuth {
    //Check if we got a location before rotate the map
    if (m_locationProvider.lastLocation != nil) {
        //Update map rendering angle
        float angle = (m_mapView.currentAzimuth - azimuth);
        [m_mapView rotateWithAngle:angle andAnimated:NO];
    }
}

- (void)mainAlert {
    //Display a message
    m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [m_hud setMode:MBProgressHUDModeText];
    [m_hud setLabelText:@"Information"];
    [m_hud setDetailsLabelText:@"No known beacon detected. You are probably out of site"];
    [m_hud hide:YES afterDelay:3];
    
    //Stop spinner and enable button loc
    [self hideSpinnerOnLocationButton];
}

- (void)noRegisteredBeaconDetected {
    [self performSelectorOnMainThread:@selector(mainAlert) withObject:nil waitUntilDone:NO];
    
    //Note: if a Fake Location has been created and is available for the current site, it will be used.
}

#pragma mark - ISGeofenceDelegate

- (void)onGeofenceDataUpdateWithEnteredAreas:(NSArray *)enteredAreas andStayedAreas:(NSArray *)stayedAreas andLeftAreas:(NSArray *)leftAreas {
    NSString * message = @"";
    
    if ([enteredAreas count] > 0) {
        message = [message stringByAppendingString:@"Entered"];
        for (ISGeofenceArea * geoArea in enteredAreas) {
            message = [message stringByAppendingFormat:@" %@ ", geoArea.guid];
        }
    }
    
    if ([stayedAreas count] > 0) {
        message = [message stringByAppendingString:@"Stayed"];
        for (ISGeofenceArea * geoArea in stayedAreas) {
            message = [message stringByAppendingFormat:@" %@ ", geoArea.guid];
        }
    }
    
    if ([leftAreas count] > 0) {
        message = [message stringByAppendingString:@"Left"];
        for (ISGeofenceArea * geoArea in leftAreas) {
            message = [message stringByAppendingFormat:@" %@ ", geoArea.guid];
        }
    }
    
    //Display a simple message
    //m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    //[m_hud setMode:MBProgressHUDModeText];
    //[m_hud setLabelText:@"Geonotification"];
    //[m_hud setDetailsLabelText:message];
    //[m_hud hide:YES afterDelay:2];
    
    //Or even a UILocalNotification (uncomment in viewDidLoad the iOS8 requirement)
    //UILocalNotification * notification = [[UILocalNotification alloc] init];
    //notification.alertBody = message;
    //notification.soundName = UILocalNotificationDefaultSoundName;
    
    NSLog(@"%@", message);
}

- (void)onGeofenceDataCleared {
    
}

#pragma mark - IBActions

- (IBAction)presentMapActionSheet:(id)sender {
    UIActionSheet * actionSheet = [[UIActionSheet alloc] initWithTitle:@"Change Map"
                                                              delegate:self
                                                     cancelButtonTitle:nil
                                                destructiveButtonTitle:nil
                                                     otherButtonTitles:nil];
    
    //List all maps in an UIActionSheet
    NSArray * maps = [[Insiteo currentSite].maps allValues];
    for (ISMap * map in maps) {
        [actionSheet addButtonWithTitle:map.name];
    }
    
    [actionSheet addButtonWithTitle:@"Cancel"];
    [actionSheet setCancelButtonIndex:[maps count]];
    
    [actionSheet showInView:self.view];
}

- (IBAction)onLocationButtonPush:(id)sender {
    //Check if location is started
    if (m_locationProvider.isStarted) {
        //Stop location
        [m_locationProvider stopLocation];
        
        //"Stop" geofencing
        [m_geofenceProvider setDelegate:nil];
        
        //And reset rotation
        [m_mapView rotateWithAngle:0 andAnimated:NO];
        
    } else {
        //Display a spinner activity on location button
        [self addSpinnerOnLocationButton];
        
        //Start location asynchronous to not block the UI
        dispatch_async(dispatch_get_main_queue(), ^{
            //Start using your .plist configuration
            [m_locationProvider startWithDelegate:self];
        });
        
        //"Start" geofencing
        [m_geofenceProvider setDelegate:self];
    }
}

- (void)addSpinnerOnLocationButton {
    //On main thread, add a spinner on location button and disable it
    dispatch_async(dispatch_get_main_queue(), ^(void){
        if (m_spinner == nil) {
            m_spinner = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
            [m_spinner setFrame:m_buttonLoc.bounds];
            [m_spinner setHidesWhenStopped:YES];
        }
        [m_spinner startAnimating];
        [m_buttonLoc addSubview:m_spinner];
        [m_buttonLoc setEnabled:NO];
    });
}

- (void)hideSpinnerOnLocationButton {
    //On main thread, hide the spinner and enable location button
    dispatch_async(dispatch_get_main_queue(), ^(void){
        [m_spinner stopAnimating];
        [m_buttonLoc setEnabled:YES];
    });
}

#pragma mark - UIActionSheetDelegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    //Cancel button
    if (buttonIndex != actionSheet.cancelButtonIndex) {
        //Get clicked map
        NSArray * maps = [[Insiteo currentSite].maps allValues];
        ISMap * map = [maps objectAtIndex:buttonIndex];
        
        //Change the current map using the selected identifier
        [m_mapView changeMapWithMapId:map.mapId andKeepPosition:YES andKeepZoomLevel:YES andKeepRotationAngle:YES];
    }
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //UI
    [self.view setBackgroundColor:[UIColor whiteColor]];
    
    //Launch API
    [self launchAPI];
    
    //UILocalNotification requirement in iOS8
    //if ([[UIApplication sharedApplication] respondsToSelector:@selector(registerUserNotificationSettings:)]) {
    //    [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];
    //}
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    //Clear map
    if (m_mapView) {
        [m_mapView clear];
        [m_mapView stopRendering];
    }
    
    //Stop loc
    if (m_locationProvider.isStarted) {
        [m_locationProvider stopLocation];
        
        //"Stop" geofencing
        [m_geofenceProvider setDelegate:nil];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
