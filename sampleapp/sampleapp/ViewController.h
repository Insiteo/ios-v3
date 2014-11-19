//
//  ViewController.h
//  sampleapp
//
//  Created by dev_iphone on 15/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "InsiteoAPIGraphicsLocation.h"
#import "MBProgressHUD.h"

@interface ViewController : UIViewController <ISPMapListener, ISPLocationListener, ISPGeofenceListener, ISPItineraryRequestListener, ISPItineraryRenderListener, UIActionSheetDelegate> {

@private
    
    id<ISPCancelable> m_currentTask;
        
    MBProgressHUD * m_hud;
    ISMapView * m_mapView;
    
    ISLocationProvider * m_locationProvider;
    ISItineraryProvider * m_itineraryProvider;
    ISGeofenceProvider * m_geofenceProvider;
}

@property (nonatomic, retain) IBOutlet UIView * mapContentView;

@property (nonatomic, retain) id<ISPCancelable> currentTask;

@end
