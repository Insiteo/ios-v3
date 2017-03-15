//
//  MapViewController.m
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import "MapViewController.h"

#import "MyCustomRTO.h"
#import "MyCustomRTORenderer.h"
#import "ItineraryWaypoint.h"

#import <InsiteoSDK/InsiteoSDK.h>
#import <MBProgressHUD/MBProgressHUD.h>

@interface MapViewController () <ISMapViewDelegate, ISRTODelegate, ISLocationDelegate, ISGeofenceDelegate, ISItineraryRequestDelegate, ISItineraryRenderDelegate> {
    ISMapView *_mapView;
    ISGenericRTO *_currentRTO;
    ISItineraryBaseRequest *_lastRouteRequest;
}

@property (strong, nonatomic) IBOutlet UIView *mapContainerView;
@property (strong, nonatomic) IBOutlet UIButton *locationButton;
@property (strong, nonatomic) IBOutlet UIButton *mapSwitcherButton;
@property (strong, nonatomic) IBOutlet UIButton *itineraryButton;

@end

@implementation MapViewController

#pragma mark - UI

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    // Start Map Rendering (SDK must be initialized see init example)
    [self startMapRendering];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    // Stop rendering
    if ([_mapView isRendering]) {
        [_mapView stopRendering];
    }
    
    // Stop specifics
    if (_exampleMapMode == MapModeLoc || _exampleMapMode == MapModeGeofence || _exampleMapMode == MapModeItinerary) {
        // Stop location
        if ([ISLocationProvider sharedInstance].isStarted) {
            [[ISLocationProvider sharedInstance] stopLocation];
        }
        
        // Stop geofencing
        if (_exampleMapMode == MapModeGeofence) {
            [self startGeofencingDetection:NO];
        }
        
        // Cancel itinerary
        if (_exampleMapMode == MapModeItinerary) {
            [self cancelItinerary];
        }
    }
}

#pragma mark IBAction

- (IBAction)onLocationButtonTap:(id)sender {
    if (_exampleMapMode != MapModeRTO) {
        [self computeUserLocation];
    }
}

- (IBAction)onMapSwitcherButtonTap:(id)sender {
    // Present Action Sheet to select maps
    UIAlertController *controller = [UIAlertController alertControllerWithTitle:@"Change Map"
                                                                        message:nil
                                                                 preferredStyle:UIAlertControllerStyleActionSheet];
    // List all maps
    NSArray *maps = [[Insiteo currentSite].maps allValues];
    for (ISMap *map in maps) {
        [controller addAction:[UIAlertAction actionWithTitle:map.name
                                                       style:UIAlertActionStyleDefault
                                                     handler:^(UIAlertAction * _Nonnull action) {
                                                         [_mapView changeMapWithMapId:map.mapId
                                                                      andKeepPosition:YES
                                                                     andKeepZoomLevel:YES
                                                                 andKeepRotationAngle:YES
                                                                 andCompletionHandler:nil];
                                                     }]];
    }
    
    // Add cancel
    [controller addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil]];
    
    // iPad compatibility
    UIButton *button = (UIButton *)sender;
    [controller setModalPresentationStyle:UIModalPresentationPopover];
    controller.popoverPresentationController.sourceView = button;
    controller.popoverPresentationController.sourceRect = button.bounds;
    
    [self presentViewController:controller animated:YES completion:nil];
}

- (IBAction)onItineraryButtonTap:(id)sender {
    
    //ISPosition * endPosition = [ISPosition ISPositionWithX:arc4random_uniform(kMaxCoordinates) andY:arc4random_uniform(kMaxCoordinates) andMapId:(arc4random_uniform(kSecondMapId) + kFirstMapId)];
    
    // Present Action Sheet with multiple iti examples
    UIAlertController *controller = [UIAlertController alertControllerWithTitle:@"Choose an itinerary example"
                                                                        message:nil
                                                                 preferredStyle:UIAlertControllerStyleActionSheet];
    
    // Iti 1: between 2 random positions
    [controller addAction:[UIAlertAction actionWithTitle:@"Between two random points"
                                                   style:UIAlertActionStyleDefault
                                                 handler:
                           ^(UIAlertAction * _Nonnull action) {
                               ISPosition *p1 = [ISPosition ISPositionWithX:arc4random_uniform(50)
                                                                       andY:arc4random_uniform(50)
                                                                   andMapId:(arc4random_uniform(1) + 2)];
                               ISPosition *p2 = [ISPosition ISPositionWithX:arc4random_uniform(50)
                                                                       andY:arc4random_uniform(50)
                                                                   andMapId:(arc4random_uniform(1) + 2)];
                               [self computeItineraryBetweenPosition:p1 andOther:p2];
                           }]];
    
    // Iti 2: between location and random end position
    [controller addAction:[UIAlertAction actionWithTitle:@"From location to random point"
                                                   style:UIAlertActionStyleDefault
                                                 handler:
                           ^(UIAlertAction * _Nonnull action) {
                               ISPosition *p2 = [ISPosition ISPositionWithX:arc4random_uniform(50)
                                                                       andY:arc4random_uniform(50)
                                                                   andMapId:(arc4random_uniform(1) + 2)];
                               [self computeItineraryBetweenPosition:nil andOther:p2];
                           }]];
    
    // Iti 3: between multiple random positions
    [controller addAction:[UIAlertAction actionWithTitle:@"Multiple random points"
                                                   style:UIAlertActionStyleDefault
                                                 handler:
                           ^(UIAlertAction * _Nonnull action) {
                               [self computeItineraryBetweenRandomPositions];
                           }]];
    
    
    // Clear itineraries
    [controller addAction:[UIAlertAction actionWithTitle:@"Clear itineraries"
                                                   style:UIAlertActionStyleDestructive
                                                 handler:
                           ^(UIAlertAction * _Nonnull action) {
                               [self cancelItinerary];
                           }]];
    
    // Add cancel
    [controller addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil]];
    
    // iPad compatibility
    UIButton *button = (UIButton *)sender;
    [controller setModalPresentationStyle:UIModalPresentationPopover];
    controller.popoverPresentationController.sourceView = button;
    controller.popoverPresentationController.sourceRect = button.bounds;
    
    [self presentViewController:controller animated:YES completion:nil];
}

- (IBAction)onHudDoubleTap:(id)sender {
    // Hide current progress view
    [MBProgressHUD hideHUDForView:self.navigationController.view animated:YES];
    // Cancel current task
    [[Insiteo sharedInstance].currentTask cancel];
}

#pragma mark -
#pragma mark Examples - Start Insiteo Map Rendering
#pragma mark -

- (void)startMapRendering {
    // Check if map data package is available before trying to create anything
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeMapData]) {
        // Create the map view according to the render mode from the .plist
        if ([Insiteo currentUser].renderMode == ISERenderMode2D) {
            // 2D
            [ISMap2DView getMap2DViewWithFrame:self.mapContainerView.bounds
                                andMapDelegate:self
                                    andHandler:^(ISMap2DView *map2DView) {
                                        [self createMapView:map2DView];
                                    }];
            
        } else {
            // 3D
            [ISMap3DView getMap3DViewWithFrame:self.mapContainerView.bounds
                                andMapDelegate:self
                                    andHandler:^(ISMap3DView *map3DView) {
                                        [self createMapView:map3DView];
                                    }];
        }
        
    } else {
        NSLog(@"Map Data package not found.");
    }
}

- (void)createMapView:(ISMapView *)mapView {
    _mapView = mapView;
    [self.mapContainerView addSubview:mapView];
    
    // Map switcher
    self.mapSwitcherButton.hidden = ([[[Insiteo currentSite].maps allValues] count] == 1);
    
    // Custom rendering according to selected example
    switch (_exampleMapMode) {
        case MapModeRTO:
            // Custom RTO rendering
            [self customRTORendering];
            break;
        case MapModeLoc:
            // User location rendering + customization
            [self userLocationRendering];
            break;
        case MapModeGeofence:
            // Geofencing areas rendering
            [self userLocationRendering];
            [self geofencingRendering];
            break;
        case MapModeItinerary:
            // Itineraries rendering + customization
            [self userLocationRendering];
            [self itinerariesRendering];
            break;
    }
    
    // Disable zoom gesture (you may still change the zoom level programatically)
    //_mapView.zoomEnabled = NO;
    
    // Disable rotation gesture (you may still change the rotation angle programatically)
    //_mapView.rotationEnabled = NO;
    
    // Disable pan gesture (you may still change the map center programatically)
    //_mapView.scrollEnabled = NO;
    
    // Start rendering
    [_mapView startRendering];
}



#pragma mark ISMapViewDelegate

- (void)onMapChangedWithNewMapId:(int)newMapId andMapName:(NSString *)mapName {
    self.title = mapName;
}

- (void)onMapClicked:(ISPosition *)touchPosition {
    NSLog(@"Map clicked");
}

- (void)onZoneClickedWithZone:(ISZone *)zone {
    // Get external zone pois associations for the clicked zone
    NSArray *zonesPois = [ISDBHelperMap getZonePoisForIdZone:zone.idZone andExternal:YES];
    
    if ([zonesPois count] > 0) {
        if (_exampleMapMode == MapModeGeofence) {
            // Display dynamically geofencing zone
            ISGeofenceProvider *geofenceProvider =
            (ISGeofenceProvider *)[[ISLocationProvider sharedInstance] getLbsModule:ISELbsModuleTypeGeofencing];
            
            for (ISZonePoi * zonePoi in zonesPois) {
                if ([geofenceProvider geofenceAreaExistsWithZonePoi:zonePoi]) {
                    [geofenceProvider removeGeofenceAreaWithZonePoi:zonePoi];
                } else {
                    [geofenceProvider addGeofenceAreaWithZonePoi:zonePoi andLabel:zonePoi.externalPoiId andMessage:nil];
                }
            }
            
        } else if (_exampleMapMode == MapModeRTO) {
            // Display POIs
            if (![_mapView getRTOsWithZoneId:zone.idZone]) {
                for (ISZonePoi * zonePoi in zonesPois) {
                    // Add a new one
                    ISGenericRTO *rto = [[ISGenericRTO alloc] initWithName:zonePoi.externalPoiId
                                                                  andLabel:nil
                                                         andMetersPosition:nil
                                               andWindowInitiallyDisplayed:NO
                                                andLabelInitiallyDisplayed:NO];
                    [_mapView addRTO:rto
                              inZone:zonePoi.zoneId
                          withOffset:cc3v(zonePoi.offset.x, zonePoi.offset.y, 0)];
                }
                
                // Set delegate for ISGenericRTO
                [_mapView setRTODelegate:self withRTOClass:[ISGenericRTO class]];
                
            } else {
                // Was already added so clear the zone
                [_mapView clearZone:zone.idZone];
            }
        }
    }
}

- (void)onMapMoved {
    
}

- (void)onMapReleased {
    
}

- (void)onZoomEnd:(double)newZoom {
    
}

#pragma mark -
#pragma mark Examples - Custom Rendering
#pragma mark -

// Example Custom Rendering
- (void)customRTORendering {
    // By default, if you do not specify a specific render for your custom RTO, the map view will use a
    // `ISGenericRenderer` to render and manage touch events. You can override this by creating your own `ISRenderer`
    // from scratch or you can create a class that inherits from `ISGenericRenderer` and override the methods you want.
    MyCustomRTORenderer *customRenderer = [[MyCustomRTORenderer alloc] initWithRTOClass:[MyCustomRTO class]
                                                                            andPriority:8];
    [customRenderer setRtoDelegate:self];
    [_mapView addRenderer:customRenderer];
    
    // Create custom RTOs with random position
    float xMin = 10.04, xMax = 60.59, yMin = 13;
    float padding = 10;
    int nbPOI = 10;
    
    ISMap *currentMap = [ISDBHelperMap getMapWithMapId:_mapView.currentMapId];
    int zoomMax = currentMap.zoomMax;
    
    int zoomLevel;
    float x = xMin, y = yMin;
    
    for (int i = 0; i < nbPOI; i++) {
        x += padding;
        if (x > xMax) {
            x = xMin;
            y += padding;
        }
        zoomLevel = arc4random_uniform(zoomMax) + 1;
        MyCustomRTO *rto = [[MyCustomRTO alloc] initWithPosition:[ISPosition ISPositionWithX:x
                                                                                        andY:y
                                                                                    andMapId:_mapView.currentMapId]
                                                    andZoomLevel:zoomLevel];
        // Add custom RTO
        [_mapView addRTO:rto];
    }
}

#pragma mark ISRTODelegate

- (void)onRTOSelected:(id<ISRTO>)rto andZone:(ISZone *)zone {
    if (_exampleMapMode == MapModeRTO) {
        // If you have multiple rto class, we recommand you to check the class before
        if ([rto isKindOfClass:[ISGenericRTO class]]) {
            // Update z-order for example to be on top
            ISGenericRTO *genericRTO = (ISGenericRTO *)rto;
            genericRTO.zOrder = 0;
            
            // Hide the current
            if (_currentRTO && _currentRTO.rtoId != genericRTO.rtoId) {
                [_currentRTO hideWindow];
                [_currentRTO hideLabel];
            }
            
            // Update
            _currentRTO = genericRTO;
            
            // You can center the map
            if (genericRTO.metersPosition) {
                // Meters position
                [_mapView centerMapWithPosition:genericRTO.metersPosition andAnimated:YES];
            } else {
                // Position from zone center and offset
                ISPosition *position = [ISPosition ISPositionWithX:(zone.center.x + rto.zoneOffset.x)
                                                              andY:(zone.center.y + rto.zoneOffset.y)
                                                          andMapId:zone.mapId];
                [_mapView centerMapWithPosition:position andAnimated:YES];
            }
        }
    }
}

- (void)onRTOClicked:(id<ISRTO>)rto andZone:(ISZone *)zone {
    NSLog(@"RTO clicked");
}

- (void)onRTOMoved:(id<ISRTO>)rto andZone:(ISZone *)zone {
    NSLog(@"RTO moved");
}

- (void)onRTOReleased:(id<ISRTO>)rto andZone:(ISZone *)zone {
    NSLog(@"RTO released");
    
    if (_exampleMapMode == MapModeItinerary) {
        // Get waypoints (they are not attached to any zone so ther zoneId = -1)
        NSArray *waypoints = [_mapView getRTOsWithZoneId:-1];
        if ([waypoints count] > 0) {
            ItineraryWaypoint *waypoint1 = waypoints[0];
            if ([waypoints count] == 1) {
                [self computeItineraryBetweenPosition:nil andOther:waypoint1.metersPosition];
            } else {
                ItineraryWaypoint *waypoint2 = waypoints[1];
                [self computeItineraryBetweenPosition:waypoint1.metersPosition andOther:waypoint2.metersPosition];
            }
        }
    }
}

#pragma mark -
#pragma mark Examples - Location Computation + Rendering
#pragma mark -

- (void)userLocationRendering {
    self.locationButton.hidden = NO;
    
    // Get the location renderer from provider
    ISLocationRenderer *locationRenderer = [ISLocationProvider sharedInstance].renderer;
    
    if (_exampleMapMode == MapModeLoc) {
        // Customize
        locationRenderer.locationColor = ccc3(0.0, 219.0, 102.0);
        locationRenderer.accuracyColor = ccc4f(0.0, 219.0, 102.0, 125.0);
        locationRenderer.locationLostColor = ccc3(255.0, 125.0, 125.0);
    }
    
    // Add it to the map view
    [_mapView addRenderer:locationRenderer];
}

- (void)computeUserLocation {
    // Check loc package
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeLocation]) {
        ISLocationProvider *locationProvider = [ISLocationProvider sharedInstance];
        if (!locationProvider.isStarted) {
            // Use plist configuration flags
            [locationProvider startWithDelegate:self];
            // Use custom flags
            //[locationProvider startWithFlags:kISNavigationFlags andDelegate:self];
            // Change location frequency to 3 sec (default is 2 sec)
            //[locationProvider startWithFlags:kISNavigationFlags andDelegate:self andScanFrequency:3000];
            
            // Add spinner on button
            UIActivityIndicatorView *spinner =
            [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
            spinner.tag = 1;
            spinner.frame = self.locationButton.bounds;
            [self.locationButton addSubview:spinner];
            self.locationButton.enabled = NO;
            [spinner startAnimating];
            
            if (_exampleMapMode == MapModeGeofence) {
                [self startGeofencingDetection:YES];
            }
            
        } else {
            [locationProvider stopLocation];
            // Re center the map
            [_mapView rotateWithAngle:0 andAnimated:YES];
            
            if (_exampleMapMode == MapModeGeofence) {
                [self startGeofencingDetection:NO];
            }
        }
    }
}

#pragma mark ISLocationDelegate

- (void)onLocationInitDoneWithSuccess:(Boolean)success andError:(ISError *)error {
    NSLog(@"Location init %@", (success) ? @"succeed" : @"failed");
}

- (void)onLocationReceived:(ISLocation *)location {
    NSLog(@"New location: (%.2f, %.2f)", location.x, location.y);
    
    // Really first loc
    if (![ISLocationProvider sharedInstance].lastLocation) {
        dispatch_async(dispatch_get_main_queue(), ^{
            // Remove spinner from button
            UIView *spinner = [self.locationButton viewWithTag:1];
            [spinner removeFromSuperview];
            self.locationButton.enabled = YES;
        });
    }
}

- (void)onAzimuthReceived:(float)azimuth {
    if ([ISLocationProvider sharedInstance].lastLocation) {
        // Rotate the map
        float angle = (_mapView.currentAzimuth - azimuth);
        [_mapView rotateWithAngle:angle andAnimated:NO];
    }
}

- (void)noRegisteredBeaconDetected {
    NSLog(@"No beacon found => you must be out of site");
}

#pragma mark -
#pragma mark Examples - Geofencing Computation + Rendering
#pragma mark -

- (void)geofencingRendering {
    // Get the geofencing module from location provider
    ISGeofenceProvider *geofenceProvider =
    (ISGeofenceProvider *)[[ISLocationProvider sharedInstance] getLbsModule:ISELbsModuleTypeGeofencing];
    // Get geofence areas renderer
    ISGeofenceAreaRenderer *geofenceAreaRenderer = geofenceProvider.renderer;
    // Add it to the map view
    [_mapView addRenderer:geofenceAreaRenderer];
}

- (void)startGeofencingDetection:(BOOL)start {
    // Check package
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeGeofencing]) {
        // Ask notification permission
        if ([[UIApplication sharedApplication] respondsToSelector:@selector(registerUserNotificationSettings:)]) {
            [[UIApplication sharedApplication] registerUserNotificationSettings:[UIUserNotificationSettings
                                                                                 settingsForTypes:
                                                                                 UIUserNotificationTypeAlert |
                                                                                 UIUserNotificationTypeSound
                                                                                 categories:nil]];
        }
        
        
        // Get the geofencing module from location provider
        ISGeofenceProvider *geofenceProvider =
        (ISGeofenceProvider *)[[ISLocationProvider sharedInstance] getLbsModule:ISELbsModuleTypeGeofencing];
        // "Start" by adding a delegate, "Stop" removing the delegate
        [geofenceProvider setDelegate:(start) ? self : nil];
    }
}

#pragma mark ISGeofenceDelegate

- (void)onGeofenceDataUpdateWithEnteredAreas:(NSArray *)enteredAreas
                              andStayedAreas:(NSArray *)stayedAreas
                                andLeftAreas:(NSArray *)leftAreas {
    // Here you can manage your notification such as `UILocalNotification` or alert view.
    
    // Entered areas
    for (ISGeofenceArea *area in enteredAreas) {
        NSLog(@"User entered area `%@`", area.label);
        
        // Example, present an alert view if the area has a message
        if (area.message) {
            if ([UIApplication sharedApplication].applicationState == UIApplicationStateActive) {
                // Present an alert view when application is active
                UIAlertController *controller = [UIAlertController alertControllerWithTitle:area.label
                                                                                    message:area.message
                                                                             preferredStyle:UIAlertControllerStyleAlert];
                [controller addAction:[UIAlertAction actionWithTitle:@"Show me!"
                                                               style:UIAlertActionStyleCancel
                                                             handler:nil]];
                [self presentViewController:controller animated:YES completion:nil];
            } else {
                // Otherwise a local notification
                UILocalNotification *notification = [[UILocalNotification alloc] init];
                if ([notification respondsToSelector:@selector(alertTitle)]) {
                    notification.alertTitle = area.label;
                }
                notification.alertBody = area.message;
                notification.soundName = UILocalNotificationDefaultSoundName;
                [[UIApplication sharedApplication] presentLocalNotificationNow:notification];
            }
        }
    }
    
    // Stayed areas
    for (ISGeofenceArea *area in stayedAreas) {
        NSLog(@"User stayed in area `%@`", area.label);
    }
    
    // Left areas
    for (ISGeofenceArea *area in leftAreas) {
        NSLog(@"User left area `%@`", area.label);
    }
}

- (void)onGeofenceDataCleared {
    NSLog(@"Geofence data cleared");
}

#pragma mark -
#pragma mark Examples - Itineraries Computation + Rendering
#pragma mark -

- (void)itinerariesRendering {
    self.itineraryButton.hidden = NO;
    
    // Check if Itinerary package is available
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeItinerary]) {
        ISItineraryProvider *itineraryProvider =
        (ISItineraryProvider *)[[ISLocationProvider sharedInstance] getLbsModule:ISELbsModuleTypeItinerary];
        ISItineraryRenderer *itineraryRenderer = itineraryProvider.renderer;
        [itineraryRenderer setDelegate:self];
        
        // Customization
        // Common both 2D/3D
        [itineraryRenderer setFrontFillColor:[UIColor colorWithRed:40.0/255.0 green:186.0/255.0 blue:156.0/255.0 alpha:1]];
        [itineraryRenderer setFrontStrokeThickness:2.0];
        
        if (_mapView.renderMode == ISERenderMode2D) {
            // 2D
            [itineraryRenderer setBackStrokeThickness:2.5];
            [itineraryRenderer setBackFillColor:[UIColor grayColor]];
            [itineraryRenderer setSelectedFillColor:[UIColor redColor]];
            [itineraryRenderer setProgressiveDrawing:YES];
            //[itineraryRenderer setOnlyPath:YES]; // To hide or not pictures
            
        } else if (_mapView.renderMode == ISERenderMode3D) {
            // 3D
            [itineraryRenderer setDefaultWaypointColor:[UIColor blackColor]];
            [itineraryRenderer setStartWaypointColor:[UIColor greenColor]];
            [itineraryRenderer setEndWaypointColor:[UIColor blueColor]];
            [itineraryRenderer setMapChangerWaypointColor:[UIColor orangeColor]];
            [itineraryRenderer setEntryWaypointColor:[UIColor redColor]];
        }
        
        [_mapView addRenderer:itineraryRenderer];
        
        // Create renderer to be notify on drag
        ISGenericRenderer *genericRenderer = [[ISGenericRenderer alloc] initWithRTOClass:[ItineraryWaypoint class]
                                                                             andPriority:7];
        [genericRenderer setRtoDelegate:self];
        [_mapView addRenderer:genericRenderer];
    }
    
}

- (void)computeItineraryBetweenPosition:(ISPosition *)p1 andOther:(ISPosition *)p2 {
    // Cancel itinerary if needed
    [self cancelItinerary];
    
    ISItineraryProvider *itineraryProvider =
    (ISItineraryProvider *)[[ISLocationProvider sharedInstance] getLbsModule:ISELbsModuleTypeItinerary];
    
    if (p1 && p2) {
        // Recompute itinerary with start and end
        _lastRouteRequest = [itineraryProvider requestItineraryWithStartPoint:p1.coordinates
                                                                andStartMapId:p1.mapId
                                                                  andEndPoint:p2.coordinates
                                                                  andEndMapId:p2.mapId
                                                                  andDelegate:self
                                                                       andPMR:NO]; // Use `YES` to include PMR paths
        
        ItineraryWaypoint *start = [[ItineraryWaypoint alloc] initWithPosition:p1 andName:@"START"];
        [_mapView addRTO:start];
        
        ItineraryWaypoint *end = [[ItineraryWaypoint alloc] initWithPosition:p2 andName:@"END"];
        [_mapView addRTO:end];
        
    } else if (p2) {
        if (![ISLocationProvider sharedInstance].isStarted || ![ISLocationProvider sharedInstance].lastLocation) {
            // Can't compute from location until started
            NSLog(@"Location is not started or not computed yet");
        } else {
            // Recompute with last user position and end position
            _lastRouteRequest = [itineraryProvider requestItineraryFromCurrentLocationWithEndPoint:p2.coordinates
                                                                                       andEndMapId:p2.mapId
                                                                                       andDelegate:self
                                                                                            andPMR:NO];
            
            ItineraryWaypoint *end = [[ItineraryWaypoint alloc] initWithPosition:p2 andName:@"END"];
            [_mapView addRTO:end];
        }
    }
}

- (void)computeItineraryBetweenRandomPositions {
    // Cancel itinerary
    [self cancelItinerary];
    
    // Define as much random positions as you want
    int nbPositions = 5;
    NSMutableArray * positions = [[NSMutableArray alloc] init];
    for (int i = 0; i < nbPositions; i++) {
        ISPosition *position = [ISPosition ISPositionWithX:arc4random_uniform(50)
                                                      andY:arc4random_uniform(50)
                                                  andMapId:arc4random_uniform(1) + 2];
        [positions addObject:position];
        
        ItineraryWaypoint *waypoint = [[ItineraryWaypoint alloc] initWithPosition:position andName:nil];
        waypoint.draggable = NO;
        [_mapView addRTO:waypoint];
    }
    
    // If you want to compute using the current location, insert at the beginning of the array
    // Or you can use `requestItineraryFromCurrentLocationWithEndPositions:andDelegate:andPMR:` directly.
    BOOL keepFirstPosition = NO;
    if ([ISLocationProvider sharedInstance].isStarted && [ISLocationProvider sharedInstance].lastLocation) {
        [positions insertObject:[ISLocationProvider sharedInstance].lastLocation.position atIndex:0];
        keepFirstPosition = YES; // Used to keep first position order
    }
    
    // Positions will be reordered, if you want to keep first and/or last position order, just change the
    // `andKeepFirstPosition` and/or `andKeepLastPosition` boolean parameters.
    ISItineraryProvider *itineraryProvider =
    (ISItineraryProvider *)[[ISLocationProvider sharedInstance] getLbsModule:ISELbsModuleTypeItinerary];
    _lastRouteRequest =
    [itineraryProvider requestOptimizedItineraryWithWaypoints:positions
                                                 andOptimMode:ISEOptimizationModeNearestNeighbourShortestPath
                                         andKeepFirstPosition:keepFirstPosition
                                          andKeepLastPosition:NO
                                                  andDelegate:self
                                                       andPMR:NO];
}

- (void)cancelItinerary {
    // Cancel last request
    [_lastRouteRequest cancel];
    _lastRouteRequest = nil;
    
    // Clear itinerary rendering only
    [_mapView clearRendererWithRTOClass:[ISGfxItinerary class]];
    
    // Clear itinerary waypoints
    [_mapView clearRendererWithRTOClass:[ItineraryWaypoint class]];
}

#pragma mark  ISItineraryRequestDelegate

// We usually recommand to use 10 meters for recomputation
#define kRecomputationDistance 10.0

- (void)onItineraryRequestDoneWithSuccess:(Boolean)success
                               andRequest:(ISItineraryBaseRequest *)request
                                 andError:(ISError *)error {
    NSLog(@"Itinerary request %@", (success) ? @"success" : @"failed");
    
    // Success => center on first position
    if (success) {
        ISPosition *startPosition;
        if ([request isKindOfClass:[ISItineraryOptimizedRequest class]]) {
            // Optimized itinerary with waypoints
            ISItineraryOptimizedRequest *optimRequest = (ISItineraryOptimizedRequest *)request;
            startPosition = [optimRequest.waypoints firstObject];
        } else {
            // Classic itinerary
            startPosition = [ISPosition ISPositionWithX:request.itinerary.startPoint.x
                                                   andY:request.itinerary.startPoint.y
                                               andMapId:request.itinerary.startMapId];
        }
        [_mapView centerMapWithPosition:startPosition andAnimated:YES];
    }
}

- (void)onItineraryChangedWithRequest:(ISItineraryBaseRequest *)request
               andDistanceToItinerary:(float)distanceToItinerary {
    // You can filter itinerary request according to its class
    if ([request isKindOfClass:[ISItineraryOptimizedRequest class]]) {
        // Ex: I used my location as departure, but I only want to have a route once and I
        // don't want to recompute each time.
        return;
    }
    
    NSLog(@"Itinerary changed with distance: %f", distanceToItinerary);
    
    // Compare the distance between user location to itinerary and your constant value
    if (distanceToItinerary >= kRecomputationDistance) {
        // Recompute
        [request recompute];
    }
    
    // Note: Itinerary recomputation can take times according to complexity of the route, so try to not recompute too
    // many times if you do not want to have issues.
}

#pragma mark ISItineraryRenderDelegate

- (void)onWaypointClickedWithItinerary:(ISItinerary *)itinerary
                   andInstructionIndex:(int)instructionIndex
                            andSection:(ISItinerarySection *)section {
    NSLog(@"Waypoint clicked");
}

- (void)onInstructionClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex {
    NSLog(@"Instruction clicked with index: %i", instructionIndex);
}

- (void)onMapSwitcherClickedWithNextPosition:(ISPosition *)nextPosition {
    NSLog(@"Map Switcher clicked");
    [_mapView centerMapWithPosition:nextPosition andAnimated:NO];
}

@end
