//
//  ISMap3DView.h
//  MapAPI
//
//  Created by dev_iphone on 04/12/13.
//  Copyright (c) 2013 INSITEO. All rights reserved.
//

/*!
 @header ISMap3DView.h
 ISMap3DView
 */

#import "ISMapView.h"

@class Map3DScene;
@class CC3DeviceCameraOverlayUIViewController;

/*!
 Class used to handle 3D map rendering (using Cocos3d).
 */
@interface ISMap3DView : ISMapView

/*!
 Corresponding map 3D scene.
 */
@property (nonatomic, readonly) Map3DScene * scene;

/*!
 Cocos3d view controller.
 */
@property (nonatomic, retain) CC3DeviceCameraOverlayUIViewController * cc3viewController;

/*!
 Static constructor.
 @param frame Wanted rendering frame.
 @param mapListener Listener used to handle map events.
 */
+ (ISMap3DView *)map3DViewWithFrame:(CGRect)frame andMapListener:(id<ISPMapListener>)mapListener;

/*
 Intern method called to start the rendering.
 */
- (void)start;

@end
