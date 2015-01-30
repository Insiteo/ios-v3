//
//  ViewController.m
//  sampleapp
//
//  Created by dev_iphone on 15/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

#import "ViewController.h"

int const ALERTVIEW_RETRY_INIT = 0;

int const ALERTVIEW_LOCATE_EXT_POI = 2;

int const ACTIONSHEET_CHANGE_MAP = 0;
int const ACTIONSHEET_ACTIONS = 1;

#import "MyRto.h"

@interface ViewController ()

- (void)launch:(NSString *)message;

@end

@implementation ViewController

@synthesize mapContentView;

- (void)startAPI {
    //Create cancelable progress dialog. Canceling dialog will also cancel init task
    m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    [m_hud setMode:MBProgressHUDModeIndeterminate];
    [m_hud setLabelText:NSLocalizedString(@"STR_INITIALIZING", nil)];
    [m_hud setDetailsLabelText:NSLocalizedString(@"STR_DOUBLE_TAP_TO_CANCEL", nil)];
    
    UITapGestureRecognizer * tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onHudDoubleTapped:)];
    [tapGestureRecognizer setNumberOfTapsRequired:2];
    [m_hud addGestureRecognizer:tapGestureRecognizer];
    [tapGestureRecognizer release];
    
    [[Insiteo sharedInstance] launchWithInitializeHandler:^(ISInsiteoError * error, ISUserSite * suggestedSite) {
        NSLog(@"========================> 1) initializeDone: %@", ((error == nil) ? @"success" : @"fail"));
    } andChooseSiteHandler:^CLLocationCoordinate2D {
        return CLLocationCoordinate2DMake(43.393, -1.456);
    } andStartHandler:^(ISInsiteoError * error, NSArray * newPackages) {
        //Hide HUD
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        if (error != nil) {
            //Error HUD
            m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            [m_hud setMode:MBProgressHUDModeText];
            [m_hud setLabelText:[ISInsiteoError getErrorCodeToString:error.code]];
            [m_hud setDetailsLabelText:[ISInsiteoError getErrorReasonToString:error.reason]];
            [m_hud hide:YES afterDelay:2];
            
            //Launch site
            [self launch:NSLocalizedString(@"STR_START_FAILED", nil)];
        } else if ([newPackages count] > 0) {
            //Update HUD
            m_hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            [m_hud setLabelText:NSLocalizedString(@"STR_UPDATING", nil)];
            [m_hud setDetailsLabelText:NSLocalizedString(@"STR_DOUBLE_TAP_TO_CANCEL", nil)];
        }
    } andUpdateHandler:^(ISInsiteoError * error) {
        //Hide HUD
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        //Launch site
        [self launch:((error != nil) ? NSLocalizedString(@"STR_UPDATE_FAILED", nil) : NSLocalizedString(@"STR_UPDATE_SUCCEEDED", nil))];
    } andUpdateProgressHandler:^(ISEPackageType packageType, Boolean download, int progress, int total) {
        //Update UI progress
        [m_hud setMode:MBProgressHUDModeDeterminate];
        [m_hud setProgress:0.0];
        [m_hud setLabelText:(download ? NSLocalizedString(@"STR_DOWNLOADING", nil) : NSLocalizedString(@"STR_INSTALLING", nil))];
        [m_hud setProgress:(float)progress/(float)total];
    }];
}

- (void)startMap {
    //Initialize map controller
    if ([Insiteo currentUser].renderMode == ISERenderMode2D) {
        m_mapView = [[ISMap2DView map2DViewWithFrame:self.mapContentView.frame andMapListener:self] retain];
    } else {
        m_mapView = [[ISMap3DView map3DViewWithFrame:self.mapContentView.frame andMapListener:self] retain];
    }
    [self.mapContentView addSubview:m_mapView];
    
    //Add location renderer
    m_locationProvider = [[ISLocationProvider alloc] init];
    [m_mapView addRenderer:[m_locationProvider renderer]];
    
    //Add itinerary renderer
    m_itineraryProvider = (ISItineraryProvider *)[[m_locationProvider getLbsModule:ISELbsModuleTypeItinerary] retain];
    ISItineraryRenderer * itineraryRenderer = [m_itineraryProvider renderer];
    [itineraryRenderer setRenderListener:self];
    [m_mapView addRenderer:itineraryRenderer];
    
    //Possible itinerary customization...
    //    [itineraryProvider setFrontStrokeThickness:15.0];
    //    [itineraryProvider setFrontFillColor:[UIColor redColor]];
    //    [itineraryProvider setBackStrokeThickness:20.0];
    //    [itineraryProvider setBackFillColor:[UIColor blueColor]];
    //    [itineraryProvider setOnlyPath:YES];
    
    //Geofencing
    m_geofenceProvider = (ISGeofenceProvider *)[[m_locationProvider getLbsModule:ISELbsModuleTypeGeofencing] retain];
    
    [m_mapView startRendering];
}

#pragma mark - ISPInitListener

- (void)launch:(NSString *)message {
    //Check that packges exist for map (MAP_DATA_PACKAGE), location, itinerary, and geofencing
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeMapData] &&
        [[Insiteo currentSite] hasPackage:ISEPackageTypeLocation] &&
        [[Insiteo currentSite] hasPackage:ISEPackageTypeItinerary] &&
        [[Insiteo currentSite] hasPackage:ISEPackageTypeGeofencing]) {
        //If a message needs to be displayed
        if (message != nil) {
            UIAlertView * alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"STR_INFORMATION", nil) message:message delegate:nil cancelButtonTitle:NSLocalizedString(@"STR_OK", nil) otherButtonTitles:nil];
            [alert show];
        }
        
        [self startMap];
    } else {
        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"STR_NO_DATA_AVAILABLE_TITLE", nil) message:NSLocalizedString(@"STR_NO_DATA_AVAILABLE_MESSAGE", nil) delegate:self cancelButtonTitle:nil otherButtonTitles:NSLocalizedString(@"STR_RETRY", nil), nil];
        [alert setTag:ALERTVIEW_RETRY_INIT];
        [alert show];
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    switch (alertView.tag) {            
        case ALERTVIEW_RETRY_INIT:  {
            [self startAPI];
            break;
        }
        case ALERTVIEW_LOCATE_EXT_POI : {
            if (buttonIndex != alertView.cancelButtonIndex) {
                NSString * extId = [alertView textFieldAtIndex:0].text;
                NSArray * zonesPois = [ISDBHelperMap getExternalZonePoisForExtIdPoi:extId];
                
                //Clear all other ISGenericRTO/MyRto
                [m_mapView clearRendererWithRTOClass:[ISGenericRTO class]];
                [m_mapView clearRendererWithRTOClass:[MyRto class]];
                
                for (ISZonePoi * zonePoi in zonesPois) {
                    //And add a new one
                    ISGenericRTO * rto = [[ISGenericRTO alloc] initWithName:zonePoi.externalPoiId andLabel:@"My label" andMetersPosition:nil andWindowDisplayed:YES andLabelDisplayed:YES];
                    [m_mapView addRTO:rto inZone:zonePoi.zoneId withOffset:cc3v(zonePoi.offset.x, zonePoi.offset.y, 0)];
                    [rto release];
                }
                
                //Center on first association
                if ([zonesPois count] > 0) {
                    ISZonePoi * zonePoi = [zonesPois objectAtIndex:0];
                    [m_mapView centerMapWithPosition:zonePoi.position andAnimated:YES];
                }
            }
            break;
        }
    }
}

#pragma mark - ISPMapListener

- (void)onZoneClickedWithZone:(ISZone *)zone {
    //Get external zone pois associations
    NSArray * zonesPois = [ISDBHelperMap getZonePoisForIdZone:zone.idZone andExternal:YES];
    
    //Clear all other ISGenericRTO/MyRto
    [m_mapView clearRendererWithRTOClass:[ISGenericRTO class]];
    [m_mapView clearRendererWithRTOClass:[MyRto class]];
    
    for (ISZonePoi * zonePoi in zonesPois) {
        //And add a noew one
        MyRto * rto = [[MyRto alloc] initWithName:zonePoi.externalPoiId andLabel:@"My label" andMetersPosition:nil andWindowDisplayed:YES andLabelDisplayed:YES];
        [m_mapView addRTO:rto inZone:zone.idZone withOffset:cc3v(zonePoi.offset.x, zonePoi.offset.y, 0)];
        [rto release];
    }
    
    //Center map
    if ([zonesPois count] > 1) {
        [m_mapView centerMapWithPosition:zone.center andAnimated:YES];
    } else {
        ISZonePoi * zonePoi = [zonesPois objectAtIndex:0];
        [m_mapView centerMapWithPosition:zonePoi.position andAnimated:YES];
    }
}

- (void)onMapChangeWithNewMapId:(int)newMapId andMapName:(NSString *)mapName {
    
}

- (void)onMapMoved {
    
}

- (void)onMapClicked:(ISPosition *)touchPosition {
    
}

- (void)onZoomEnd:(double)newZoom {
    
}

#pragma mark - ISPLocationListener

- (void)onLocationInitDoneWithSuccess:(Boolean)success andError:(ISInsiteoError *)error {
    //Activate Location rendering
    [m_mapView setRendererDisplayWithRTOClass:[ISGfxLocation class] andDisplay:YES];
}

- (void)onLocationReceived:(ISLocation *)location {
    NSLog(@"%@", NSLocalizedString(@"STR_LOC_RECEIVED", nil));
//    [m_mapView centerMapWithPosition:location.position andAnimated:YES];
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
    UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"STR_NO_REGISTERED_BEACONS_TITLE", nil) message:NSLocalizedString(@"STR_NO_REGISTERED_BEACONS_MESSAGE", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"STR_OK", nil) otherButtonTitles:nil];
    [alertView show];
}

- (void)noRegisteredBeaconDetected {
    [self performSelectorOnMainThread:@selector(mainAlert) withObject:nil waitUntilDone:NO];
}

#pragma mark - ISPGeofenceListener

- (void)onGeofenceDataUpdateWithEnteredAreas:(NSArray *)enteredAreas andStayedAreas:(NSArray *)stayedAreas andLeftAreas:(NSArray *)leftAreas {
    NSString * message = @"";
    
    if ([enteredAreas count] > 0) {
        message = [message stringByAppendingString:NSLocalizedString(@"STR_ENTERED", nil)];
        for (ISGeofenceArea * geoArea in enteredAreas) {
            message = [message stringByAppendingFormat:@" %@ ", geoArea.GUID];
        }
    }
    
    if ([stayedAreas count] > 0) {
        message = [message stringByAppendingString:NSLocalizedString(@"STR_STAYED", nil)];
        for (ISGeofenceArea * geoArea in stayedAreas) {
            message = [message stringByAppendingFormat:@" %@ ", geoArea.GUID];
        }
    }
    
    if ([leftAreas count] > 0) {
        message = [message stringByAppendingString:NSLocalizedString(@"STR_LEFT", nil)];
        for (ISGeofenceArea * geoArea in leftAreas) {
            message = [message stringByAppendingFormat:@" %@ ", geoArea.GUID];
        }
    }
    
//    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"STR_GEOFENCE_TITLE", nil) message:message delegate:nil cancelButtonTitle:NSLocalizedString(@"STR_OK", nil) otherButtonTitles:nil];
//    [alert show];
    
    NSLog(@"%@", message);
}

- (void)onGeofenceDataCleared {
    
}

#pragma mark - ISPItineraryRequestListener

- (void)onItineraryRequestDoneWithSuccess:(Boolean)success andRequest:(ISItineraryBaseRequest *)request andError:(ISInsiteoError *)error {
    if (success) {
        NSLog(@"%@", NSLocalizedString(@"STR_ITINERARY_REQUEST_SUCCEEDED", nil));
    } else {
        NSLog(@"%@", NSLocalizedString(@"STR_ITINERARY_REQUEST_FAILED", nil));
    }
}

- (void)onItineraryChangedWithRequest:(ISItineraryBaseRequest *)request andDistanceToItinerary:(float)distanceToItinerary {
    NSLog(@"%@", [NSString stringWithFormat:NSLocalizedString(@"STR_ITINERARY_CHANGED", nil), distanceToItinerary]);
    
    //If the distance to join the path is greater than 10 meters
    if (distanceToItinerary > 10.0) {
        //Recompute
        [request recompute];
    }
}

#pragma mark - ISPItineraryRenderListener

- (void)onWaypointClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex andSection:(ISItinerarySection *)section {
    NSLog(@"%@", NSLocalizedString(@"STR_WAYPOINT_CLICKED", nil));
}

- (void)onInstructionClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex {
    NSLog(@"%@", [NSString stringWithFormat:NSLocalizedString(@"STR_INSTRUCTION_CLICKED", nil), instructionIndex]);
}

- (void)onMapSwitcherClickedWithNextPosition:(ISPosition *)nextPosition {
    NSLog(@"%@", NSLocalizedString(@"STR_MAP_SWITCHER_CLICKED", nil));
    [m_mapView centerMapWithPosition:nextPosition andAnimated:NO];
}

#pragma mark - IBAction

#define FIRST_MAP_ID 1
#define SECOND_MAP_ID 2
#define MAX_COORDINATES 50

- (void)computeItinerary {
    if (m_itineraryProvider != nil) {
        //Start location if it's not
        if (!m_locationProvider.isStarted) {
            [self onLocationButtonPush:nil];
        }
        
        //Request an itinerary between two points on the current map
        [m_itineraryProvider requestItineraryFromCurrentLocationWithEndPoint:CGPointMake(8, 23) andEndMapId:SECOND_MAP_ID andListener:self andPMR:NO];
        
        //Example between two points (please check to not recompute it every time)
//        [m_itineraryProvider requestItineraryWithStartPoint:CGPointMake(20, 20) andStartMapId:FIRST_MAP_ID andEndPoint:CGPointMake(20, 20) andEndMapId:SECOND_MAP_ID andListener:self andPMR:NO];
    }
}

- (void)computeOptimizedRoute {
    if (m_itineraryProvider != nil) {
        //Request an optimized itinerary for random positions
        [m_itineraryProvider requestOptimizedItineraryWithWaypoints:[NSArray arrayWithObjects:[ISPosition ISPositionWithX:rand()%MAX_COORDINATES andY:rand()%MAX_COORDINATES andMapId:FIRST_MAP_ID], [ISPosition ISPositionWithX:rand()%MAX_COORDINATES andY:rand()%MAX_COORDINATES andMapId:FIRST_MAP_ID], [ISPosition ISPositionWithX:rand()%MAX_COORDINATES andY:rand()%MAX_COORDINATES andMapId:SECOND_MAP_ID], [ISPosition ISPositionWithX:rand()%MAX_COORDINATES andY:rand()%MAX_COORDINATES andMapId:SECOND_MAP_ID], [ISPosition ISPositionWithX:rand()%MAX_COORDINATES andY:rand()%MAX_COORDINATES andMapId:FIRST_MAP_ID], [ISPosition ISPositionWithX:rand()%MAX_COORDINATES andY:rand()%MAX_COORDINATES andMapId:SECOND_MAP_ID], nil] andOptimMode:ISEOptimizationModeNearestNeighbourShortestPath andKeepFirstPosition:YES andKeepLastPosition:NO andListener:self andPMR:NO];
    }
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex != actionSheet.cancelButtonIndex) {
        if (actionSheet.tag == ACTIONSHEET_ACTIONS) {
            switch (buttonIndex) {
                case 0 : {
                    //Itinerary
                    [self computeItinerary];
                    break;
                }
                case 1: {
                    //Optimized route
                    [self computeOptimizedRoute];
                    break;
                }
                case 2 : {
                    //Get zone
                    UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"STR_LOCATE_EXT_POI_TITLE", nil) message:NSLocalizedString(@"STR_LOCATE_EXT_POI_MESSAGE", nil) delegate:self cancelButtonTitle:NSLocalizedString(@"STR_CANCEL", nil) otherButtonTitles:NSLocalizedString(@"STR_SEARCH", nil), nil];
                    [alertView setTag:ALERTVIEW_LOCATE_EXT_POI];
                    [alertView setAlertViewStyle:UIAlertViewStylePlainTextInput];
                    [alertView show];
                    break;
                }
                case 3 : {
                    //Clear itinerary
                    [m_mapView clearRendererWithRTOClass:[ISGfxItinerary class]];
                    break;
                }
                case 4 : {
                    //Clear all
                    [m_mapView clear];
                    break;
                }
            }
        } else if (actionSheet.tag == ACTIONSHEET_CHANGE_MAP) {
            //Get clicked map
            NSArray * maps = [[Insiteo currentSite].maps allValues];
            ISMap * map = [maps objectAtIndex:buttonIndex];
            
            //Change the current map using the selected identifier
            [m_mapView changeMapWithMapId:map.mapId andKeepPosition:NO andKeepZoomLevel:NO andKeepRotationAngle:NO];
        }
    }
}

- (IBAction)onActionsItemButtonPush:(id)sender {
    UIActionSheet * actionSheet = [[UIActionSheet alloc] initWithTitle:NSLocalizedString(@"STR_ACTIONS", nil) delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil otherButtonTitles:nil];
    
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_COMPUTE_ITINERARY", nil)];
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_COMPUTE_OPTIMIZED_ROUTE", nil)];
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_LOCATE_EXT_POI", nil)];
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_CLEAR_ITINERARY", nil)];
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_CLEAR_ALL", nil)];
    
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_CANCEL", nil)];
    [actionSheet setCancelButtonIndex:5];
    
    [actionSheet setTag:ACTIONSHEET_ACTIONS];
    
    [actionSheet showInView:self.view];
}

- (IBAction)onMapSelectorButtonPush:(id)sender {
    UIActionSheet * actionSheet = [[UIActionSheet alloc] initWithTitle:NSLocalizedString(@"STR_CHOOSE_MAP", nil) delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil otherButtonTitles:nil];
    
    //List all maps in an UIActionSheet
    NSArray * maps = [[Insiteo currentSite].maps allValues];
    for (ISMap * map in maps) {
        [actionSheet addButtonWithTitle:map.name];
    }
    
    [actionSheet addButtonWithTitle:NSLocalizedString(@"STR_CANCEL", nil)];
    [actionSheet setCancelButtonIndex:[maps count]];
    
    [actionSheet setTag:ACTIONSHEET_CHANGE_MAP];
    
	[actionSheet showInView:self.view];
}

- (void)threadStartLocation {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    [m_locationProvider startWithListener:self];
    
    [pool release];
}

- (IBAction)onLocationButtonPush:(id)sender {
    //Check if location is started
    if (m_locationProvider.isStarted) {
        //Stop location
        [m_locationProvider stopLocation];
        
        //"Stop" geofencing
        [m_geofenceProvider setListener:nil];
        
        //And reset rotation
        [m_mapView rotateWithAngle:0 andAnimated:NO];
    } else {
        //Start location
        [NSThread detachNewThreadSelector:@selector(threadStartLocation) toTarget:self withObject:nil];
        
        //"Start" geofencing
        [m_geofenceProvider setListener:self];
    }
}

- (IBAction)onHudDoubleTapped:(id)sender {
    [[Insiteo sharedInstance].currentTask cancel];
    [m_hud hide:YES];
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"STR_SAMPLE_APP_TITLE", nil), API_VERSION]];
    
    //Actions item
    UIBarButtonItem * actionsItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAction target:self action:@selector(onActionsItemButtonPush:)];
    [self.navigationItem setRightBarButtonItem:actionsItem];
    
    [self startAPI];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)dealloc {
    [m_mapView release];
    [m_locationProvider release];
    [m_itineraryProvider release];
    [m_geofenceProvider release];
    [super dealloc];
}

@end
