//
//  MapLocItiViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 10/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "MapLocItiViewController.h"

#import "ItineraryWaypoint.h"

#import <MBProgressHUD/MBProgressHUD.h>

@interface MapLocItiViewController () {
    //Map view
    ISMapView * m_mapView;
    //Location provider
    ISLocationProvider * m_locationProvider;
    //Itinerary provider
    ISItineraryProvider * m_itineraryProvider;
    //Used to keep a reference on last itinerary request to be cancelled if needed
    ISItineraryBaseRequest * m_lastItineraryRequest;
    //Start waypoint RTO
    ItineraryWaypoint * m_startWaypoint;
    //End waypoint RTO
    ItineraryWaypoint * m_endWaypoint;
    //Boolean used to avoid itinerary recopmputation
    BOOL m_shouldRecomputeItinerary;
    //Info HUD
    MBProgressHUD * m_hud;
    //Button location
    UIButton * m_buttonLoc;
    //Spinner added on location button (to wait until loc starts)
    UIActivityIndicatorView * m_spinner;
}

@end

@implementation MapLocItiViewController

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
        m_locationProvider = [ISLocationProvider sharedInstance];
        [m_mapView addRenderer:m_locationProvider.renderer];
        
        //Add loc button
        m_buttonLoc = [UIButton buttonWithType:UIButtonTypeCustom];
        [m_buttonLoc setFrame:CGRectMake(self.view.frame.size.width / 2.0 - 20, self.view.frame.size.height - 48, 40, 40)];
        [m_buttonLoc setBackgroundImage:[UIImage imageNamed:@"btn_location"] forState:UIControlStateNormal];
        [m_buttonLoc addTarget:self action:@selector(onLocationButtonPush:) forControlEvents:UIControlEventTouchUpInside];
        m_buttonLoc.autoresizingMask = (UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleTopMargin);
        [self.view addSubview:m_buttonLoc];
        
        //Check if Itinerary package is available
        if ([[Insiteo currentSite] hasPackage:ISEPackageTypeItinerary]) {
            m_itineraryProvider = (ISItineraryProvider *)[m_locationProvider getLbsModule:ISELbsModuleTypeItinerary];
            ISItineraryRenderer * itineraryRenderer = [m_itineraryProvider renderer];
            [itineraryRenderer setDelegate:self];
            [m_mapView addRenderer:itineraryRenderer];
            
            //You could customize itinerary rendering
            [itineraryRenderer setFrontFillColor:[UIColor redColor]]; //Common property 2D/3D
            [itineraryRenderer setFrontStrokeThickness:5.0];
            
            if (m_mapView.renderMode == ISERenderMode2D) { //Specific 2D
                [itineraryRenderer setBackStrokeThickness:6.0];
                [itineraryRenderer setBackFillColor:[UIColor blueColor]];
                [itineraryRenderer setSelectedFillColor:[UIColor redColor]];
                [itineraryRenderer setProgressiveDrawing:YES];
                [itineraryRenderer setOnlyPath:YES];
                
            } else if (m_mapView.renderMode == ISERenderMode3D) { //Specific 3D
                [itineraryRenderer setDefaultWaypointColor:[UIColor blackColor]];
                [itineraryRenderer setStartWaypointColor:[UIColor greenColor]];
                [itineraryRenderer setEndWaypointColor:[UIColor blueColor]];
                [itineraryRenderer setMapChangerWaypointColor:[UIColor orangeColor]];
                [itineraryRenderer setEntryWaypointColor:[UIColor redColor]];
            }
            
            //Add rendering for custom RTO class
            ISGenericRenderer * genericRenderer = [[ISGenericRenderer alloc] initWithRTOClass:[ItineraryWaypoint class] andPriority:7];
            [genericRenderer setRtoDelegate:self];
            [m_mapView addRenderer:genericRenderer];
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

#pragma mark - ISRTODelegate

- (void)onRTOSelected:(id<ISRTO>)rto andZone:(ISZone *)zone {
    
}

- (void)onRTOClicked:(id<ISRTO>)rto andZone:(ISZone *)zone {
    
}

- (void)onRTOMoved:(id<ISRTO>)rto andZone:(ISZone *)zone {
    NSLog(@"RTO moved");
}

- (void)onRTOReleased:(id<ISRTO>)rto andZone:(ISZone *)zone {
    //Check RTO class and if an itinery is started
    if ([rto isKindOfClass:[ItineraryWaypoint class]] && m_lastItineraryRequest != nil) {
        [self recomputeItineraryWithStartPosition:m_startWaypoint.metersPosition andEndPosition:m_endWaypoint.metersPosition];
    }
}

#pragma mark - Itinerary

#define kFirstMapId 1
#define kSecondMapId 2
#define kMaxCoordinates 50

- (void)recomputeItineraryWithStartPosition:(ISPosition *)startPosition andEndPosition:(ISPosition *)endPosition {
    if (startPosition && endPosition) {
        //Recompute iti with start and end
        m_lastItineraryRequest = [m_itineraryProvider requestItineraryWithStartPoint:startPosition.coordinates andStartMapId:startPosition.mapId
                                                                         andEndPoint:endPosition.coordinates andEndMapId:endPosition.mapId andDelegate:self andPMR:NO];
    } else if (endPosition) {
        //Recompute with last current position and end position
        m_lastItineraryRequest = [m_itineraryProvider requestItineraryFromCurrentLocationWithEndPoint:endPosition.coordinates andEndMapId:endPosition.mapId andDelegate:self andPMR:NO];
    }
}

- (void)computeItineraryFromPositionToRandomPosition {
    //If loc is started and at least one location has been received
    if (m_locationProvider.isStarted && m_locationProvider.lastLocation != nil) {
        //Cancel itinerary
        [self cancelItinerary];
        
        //Random end position
        ISPosition * endPosition = [ISPosition ISPositionWithX:arc4random_uniform(kMaxCoordinates) andY:arc4random_uniform(kMaxCoordinates) andMapId:(arc4random_uniform(kSecondMapId) + kFirstMapId)];
        
        //Create draggable waypoint RTO end
        m_endWaypoint = [[ItineraryWaypoint alloc] initWithPosition:endPosition andName:@"END"];
        [m_mapView addRTO:m_endWaypoint];
        
        //Compute from current location to random position coordinates, and keep the reference
        m_lastItineraryRequest = [m_itineraryProvider requestItineraryFromCurrentLocationWithEndPoint:endPosition.coordinates
                                                                                          andEndMapId:endPosition.mapId andDelegate:self andPMR:NO];
        
        m_shouldRecomputeItinerary = YES;
        
    } else {
        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"Information" message:@"You need to start the location first"
                                                            delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
    }
}

- (void)computeItineraryBetweenTwoPositions {
    //Cancel itinerary
    [self cancelItinerary];
    
    //Random start position
    ISPosition * startPosition = [ISPosition ISPositionWithX:arc4random_uniform(kMaxCoordinates) andY:arc4random_uniform(kMaxCoordinates)
                                                    andMapId:(arc4random_uniform(kSecondMapId) + kFirstMapId)];
    
    //Create draggable waypoint RTO start
    m_startWaypoint = [[ItineraryWaypoint alloc] initWithPosition:startPosition andName:@"START"];
    [m_mapView addRTO:m_startWaypoint];
    
    //Random end position
    ISPosition * endPosition = [ISPosition ISPositionWithX:arc4random_uniform(kMaxCoordinates) andY:arc4random_uniform(kMaxCoordinates)
                                                  andMapId:(arc4random_uniform(kSecondMapId) + kFirstMapId)];
    
    //Create draggable waypoint RTO end
    m_endWaypoint = [[ItineraryWaypoint alloc] initWithPosition:endPosition andName:@"END"];
    [m_mapView addRTO:m_endWaypoint];
    
    //Compute from current location to random position coordinates, and keep the reference
    m_lastItineraryRequest = [m_itineraryProvider requestItineraryWithStartPoint:startPosition.coordinates andStartMapId:startPosition.mapId
                                                                     andEndPoint:endPosition.coordinates andEndMapId:endPosition.mapId andDelegate:self andPMR:NO];
}

- (void)computeItineraryBetweenMultiplePositions {
    //Cancel itinerary
    [self cancelItinerary];
    
    //Define as much positions as you want
    int nbPositions = 5;
    NSMutableArray * positions = [[NSMutableArray alloc] init];
    for (int i = 0; i < nbPositions; i++) {
        //Random position
        int randomMapId = arc4random_uniform(kSecondMapId) + kFirstMapId;
        ISPosition * position = [ISPosition ISPositionWithX:arc4random_uniform(kMaxCoordinates) andY:arc4random_uniform(kMaxCoordinates) andMapId:randomMapId];
        [positions addObject:position];
    }
    
    //If you want to compute using the current location, insert at the beginning of the array
    BOOL keepFirstPosition = NO;
    if (m_locationProvider.isStarted && m_locationProvider.lastLocation != nil) {
        [positions insertObject:m_locationProvider.lastLocation.position atIndex:0];
        keepFirstPosition = YES; //Used to keep first position order
    }
    
    //Compute optimal itinerary using random positions. All positions will be reordered, so if you want to keep first
    //and/or last position order, just change the andKeepFirstPosition and/or andKeepLastPosition boolean.
    m_lastItineraryRequest = [m_itineraryProvider requestOptimizedItineraryWithWaypoints:positions andOptimMode:ISEOptimizationModeNearestNeighbourShortestPath andKeepFirstPosition:keepFirstPosition andKeepLastPosition:NO andDelegate:self andPMR:NO];
}

- (void)cancelItinerary {
    //Cancel last request
    [m_lastItineraryRequest cancel];
    m_lastItineraryRequest = nil;
    
    //Clear itinerary rendering
    [m_mapView clearRendererWithRTOClass:[ISGfxItinerary class]];
    
    //Reset start and end RTOs
    [m_mapView removeRTO:m_startWaypoint];
    m_startWaypoint = nil;
    
    [m_mapView removeRTO:m_endWaypoint];
    m_endWaypoint = nil;
    
    //You could also clear all RTOs with class
    //[m_mapView clearRendererWithRTOClass:[ItineraryWaypoint class]];
    
    m_shouldRecomputeItinerary = NO;
}

#pragma mark - ISItineraryRequestDelegate

//Note: We usually use 10.0 meters as recomputation distance.
#define kDistanceToRecompute 10.0

- (void)onItineraryRequestDoneWithSuccess:(Boolean)success andRequest:(ISItineraryBaseRequest *)request andError:(ISError *)error {
    NSLog(@"Itinerary request %@", (success) ? @"success" : @"failed");
    
    //Change map if needed to see the start waypoint on itinerary success
    if (m_startWaypoint != nil) {
        [m_mapView changeMapWithMapId:m_startWaypoint.metersPosition.mapId andKeepPosition:YES andKeepZoomLevel:YES andKeepRotationAngle:YES];
    }
}

- (void)onItineraryChangedWithRequest:(ISItineraryBaseRequest *)request andDistanceToItinerary:(float)distanceToItinerary {
    NSLog(@"Itinerary changed with distance: %f", distanceToItinerary);
    
    //If the distance to join the path is greater than defined
    if (distanceToItinerary > kDistanceToRecompute && m_shouldRecomputeItinerary) {
        //Recompute
        [request recompute];
    }
    
    //Note: please check to not recompute too many times
}

#pragma mark - ISItineraryRenderDelegate

- (void)onWaypointClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex andSection:(ISItinerarySection *)section {
    NSLog(@"Waypoint clicked");
}

- (void)onInstructionClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex {
    NSLog(@"Instruction clicked with index: %i", instructionIndex);
}

- (void)onMapSwitcherClickedWithNextPosition:(ISPosition *)nextPosition {
    NSLog(@"Map Switcher clicked");
    [m_mapView centerMapWithPosition:nextPosition andAnimated:NO];
}

#pragma mark - IBActions

#define kActionSheetMap 100
#define kActionSheetIti 101

- (IBAction)presentMapActionSheet:(id)sender {
    UIActionSheet * actionSheet = [[UIActionSheet alloc] initWithTitle:@"Change Map"
                                                              delegate:self
                                                     cancelButtonTitle:nil
                                                destructiveButtonTitle:nil
                                                     otherButtonTitles:nil];
    [actionSheet setTag:kActionSheetMap];
    
    //List all maps in an UIActionSheet
    NSArray * maps = [[Insiteo currentSite].maps allValues];
    for (ISMap * map in maps) {
        [actionSheet addButtonWithTitle:map.name];
    }
    
    [actionSheet addButtonWithTitle:@"Cancel"];
    [actionSheet setCancelButtonIndex:[maps count]];
    
    [actionSheet showInView:self.view];
}

- (IBAction)presentItineraryActionSheet:(id)sender {
    UIActionSheet * actionSheet = [[UIActionSheet alloc] initWithTitle:@"Itinerary"
                                                              delegate:self
                                                     cancelButtonTitle:@"Cancel"
                                                destructiveButtonTitle:@"Clear all itineraries"
                                                     otherButtonTitles:@"Compute from position", @"Compute using 2 positions", @"Compute with random positions", nil];
    [actionSheet setTag:kActionSheetIti];
    [actionSheet showInView:self.view];
}

- (IBAction)onLocationButtonPush:(id)sender {
    //Check if location is started
    if (m_locationProvider.isStarted) {
        //Stop location
        [m_locationProvider stopLocation];
        
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
    if (buttonIndex != actionSheet.cancelButtonIndex) {
        if (actionSheet.tag == kActionSheetMap) {
            //Get clicked map
            NSArray * maps = [[Insiteo currentSite].maps allValues];
            ISMap * map = [maps objectAtIndex:buttonIndex];
            
            //Change the current map using the selected identifier
            [m_mapView changeMapWithMapId:map.mapId andKeepPosition:YES andKeepZoomLevel:YES andKeepRotationAngle:YES];
            
        } else if (actionSheet.tag == kActionSheetIti) {
            if (buttonIndex != actionSheet.destructiveButtonIndex) {
                if (buttonIndex == 1) { //Itinerary from position
                    [self computeItineraryFromPositionToRandomPosition];
                    
                } else if (buttonIndex == 2) { //Itinerary with two random positions
                    [self computeItineraryBetweenTwoPositions];
                    
                } else if (buttonIndex == 3) { //Optimal itineray with random positions
                    [self computeItineraryBetweenMultiplePositions];
                }
                
            } else {
                //Clear and cancel
                [self cancelItinerary];
            }
        }
    }
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //UI
    [self.view setBackgroundColor:[UIColor whiteColor]];
    
    //Actions item
    UIBarButtonItem * actionsItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAction target:self action:@selector(presentItineraryActionSheet:)];
    [self.navigationItem setRightBarButtonItem:actionsItem];
    
    //Launch API
    [self launchAPI];
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
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
