//
//  MapRtoViewController.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 08/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "MapRtoViewController.h"

#import "MyRTO.h"

#import <MBProgressHUD/MBProgressHUD.h>

@interface MapRtoViewController () {
    //Map view
    ISMapView * m_mapView;
    //Info HUD
    MBProgressHUD * m_hud;
}

@end

@implementation MapRtoViewController

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
    
    //Check if map data package is available before trying to create anything
    if ([[Insiteo currentSite] hasPackage:ISEPackageTypeMapData]) {
        //Initialize the map controller using the render mode (actually used from the .plist file).
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
    
    //By default, ISGenericRTOs will be rendered using the default ISGenericRenderer
    //so you don't need to implement anything. But if you want to use the ISPRTOListener, you need to create manually the renderer and add a listener.
    //ISGenericRenderer * isGenericRenderer = [[ISGenericRenderer alloc] initWithRTOClass:[ISGenericRTO class] andPriority:7];
    //[isGenericRenderer setRtoListener:self];
    //[m_mapView addRenderer:isGenericRenderer];
    
    //Specify a renderer to render your custom RTO class
    ISGenericRenderer * genericRenderer = [[ISGenericRenderer alloc] initWithRTOClass:[MyRTO class] andPriority:7];
    //If you want to control action on your custom RTO class you need to set a listener
    [genericRenderer setRtoDelegate:self];
    //Add it to the map view
    [m_mapView addRenderer:genericRenderer];
    
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
    //Clear all RTOs
    //[m_mapView clearRendererWithRTOClass:[ISGenericRTO class]];
    //[m_mapView clearRendererWithRTOClass:[MyRTO class]];
}

- (void)onMapReleased {
    
}

- (void)onZoneClickedWithZone:(ISZone *)zone {
    //Get external zone pois associations for the clicked zone
    NSArray * zonesPois = [ISDBHelperMap getZonePoisForIdZone:zone.idZone andExternal:YES];
    
    if ([zonesPois count] > 0) {
        //Clear all other ISGenericRTO/MyRto
        [m_mapView clearRendererWithRTOClass:[ISGenericRTO class]];
        [m_mapView clearRendererWithRTOClass:[MyRTO class]];
        
        for (ISZonePoi * zonePoi in zonesPois) {
            //And add a new one
            ISGenericRTO * rto = [[ISGenericRTO alloc] initWithName:zonePoi.externalPoiId andLabel:@"My label" andMetersPosition:nil andWindowInitiallyDisplayed:NO andLabelInitiallyDisplayed:NO];
            [m_mapView addRTO:rto inZone:zone.idZone withOffset:cc3v(zonePoi.offset.x, zonePoi.offset.y, 0)];
        }
        
        //Center map
        if ([zonesPois count] > 1) {
            [m_mapView centerMapWithPosition:zone.center andAnimated:YES];
            
        } else {
            ISZonePoi * zonePoi = [zonesPois objectAtIndex:0];
            [m_mapView centerMapWithPosition:zonePoi.position andAnimated:YES];
        }
    }
}

- (void)onZoomEnd:(double)newZoom {
    
}

#pragma mark - ISRTODelegate

- (void)onRTOSelected:(id<ISRTO>)rto andZone:(ISZone *)zone {
    //If you have multiple rto class, we recommand you to check the class before
    if ([rto isKindOfClass:[MyRTO class]]) {
        //Do your specific stuff
        MyRTO * myRto = (MyRTO *)rto;
        [myRto toggleLabel];
        
    } else if ([rto isKindOfClass:[ISGenericRTO class]]) {
        
    }
}

- (void)onRTOClicked:(id<ISRTO>)rto andZone:(ISZone *)zone {
    NSLog(@"RTO clicked");
}

- (void)onRTOMoved:(id<ISRTO>)rto andZone:(ISZone *)zone {
    
}

- (void)onRTOReleased:(id<ISRTO>)rto andZone:(ISZone *)zone {
    
}

#pragma mark - IBActions

#define kActionSheetMap 100
#define kActionSheetPois 101

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

- (IBAction)presentPoiActionSheet:(id)sender {
    UIActionSheet * actionSheet = [[UIActionSheet alloc] initWithTitle:@"Pois"
                                                              delegate:self
                                                     cancelButtonTitle:@"Cancel"
                                                destructiveButtonTitle:@"Clear all pois"
                                                     otherButtonTitles:@"Locate external poi", nil];
    [actionSheet setTag:kActionSheetPois];
    [actionSheet showInView:self.view];
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
            
        } else if (actionSheet.tag == kActionSheetPois) {
            if (buttonIndex != actionSheet.destructiveButtonIndex) {
                //Find and external poi
                UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"Locate an external POI" message:@"Please type its external identifier" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Search", nil];
                [alertView setAlertViewStyle:UIAlertViewStylePlainTextInput];
                UITextField *textField = [alertView textFieldAtIndex:0];
                [textField setPlaceholder:@"ex: 26G,7"];
                [alertView show];
                
            } else {
                //Clear all
                [m_mapView clear];
            }
        }
    }
}

#pragma mark - UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex != alertView.cancelButtonIndex) {
        //Search for the typing external POI
        NSString * extId = [alertView textFieldAtIndex:0].text;
        NSArray * zonesPois = [ISDBHelperMap getExternalZonePoisForExtIdPoi:extId];
        
        if ([zonesPois count] == 0) {
            //No POI found
            UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"POI not found"
                                                                 message:[NSString stringWithFormat:@"No POI found with external id, %@", extId]
                                                                delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alertView show];
            
        } else {
            //Clear all other ISGenericRTO/MyRto
            [m_mapView clearRendererWithRTOClass:[ISGenericRTO class]];
            [m_mapView clearRendererWithRTOClass:[MyRTO class]];
            
            //Create all POIs found
            for (ISZonePoi * zonePoi in zonesPois) {
                MyRTO * rto = [[MyRTO alloc] initWithLabel:zonePoi.externalPoiId];
                [m_mapView addRTO:rto inZone:zonePoi.zoneId withOffset:cc3v(zonePoi.offset.x, zonePoi.offset.y, 0)];
            }
            
            //Center on first association
            ISZonePoi * zonePoi = [zonesPois objectAtIndex:0];
            [m_mapView centerMapWithPosition:zonePoi.position andAnimated:YES];
        }
    }
}

#pragma mark - UI

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.view setBackgroundColor:[UIColor whiteColor]];
    
    //Actions item
    UIBarButtonItem * actionsItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAction target:self action:@selector(presentPoiActionSheet:)];
    [self.navigationItem setRightBarButtonItem:actionsItem];
    
    //Launch API
    [self launchAPI];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    //Best practise: stop map rendering when no needed anymore
    if (m_mapView) {
        [m_mapView clear];
        [m_mapView stopRendering];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
