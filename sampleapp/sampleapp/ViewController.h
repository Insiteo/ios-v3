//
//  ViewController.h
//  sampleapp
//
//  Created by dev_iphone on 15/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <InsiteoAPI/InsiteoAPIGraphicsLocation.h>

@interface ViewController : UIViewController <ISPInitListener, ISPMapListener, ISPLocationListener, ISPGeofenceListener, ISPItineraryRequestListener, ISPItineraryRenderListener, UIActionSheetDelegate> {

@private
        
    MBProgressHUD * m_hud;
    ISMap2DView * m_map2DView;
    
    ISGfxLocationProvider * m_locationProvider;
    ISGfxItineraryProvider * m_itineraryProvider;
    ISGeofenceProvider * m_geofenceProvider;
}

@property (nonatomic, retain) IBOutlet UIView * mapContentView;

@end
