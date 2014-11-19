//
//  ISMapView.h
//  MapAPI
//
//  Created by INSITEO on 10/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISMapView.h
 ISMapView
 */

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import "cocos2d.h"
#import "CC3Scene.h"

#import "ISPRenderer.h"
#import "ISPRTO.h"
#import "ISPMapListener.h"
#import "ISRectF.h"
#import "ISMap.h"

@class MapDataManager;
@class MapViewLayer;
@class CCScene;
@class TiledMapRenderer;
@class ZoneRenderer;

/*!
 Class used to represent the ISMapView (EAGLView).
 */
@interface ISMapView : CCGLView {

@protected
    
    //Rendering mode (2D or 3D)
    ISERenderMode m_renderMode;
    
    //Last computed offset
    CGPoint m_currentOffset;
    //Last computed ratio
    double m_currentRatio;
    
#pragma mark - Structure
    
    //MapView controller
    MapDataManager * m_mapDataManager;
    //Map view events listener
    id<ISPMapListener> m_mapListener;
    
#pragma mark - Cocos
    
    //Cocos2d MapView layer
    CCLayer * m_mapLayer;
    
#pragma mark - Rendering
    
    //Intern lock for Touch/Render interactions
    NSLock * m_renderersLock;
    
    //TiledMap Renderer (internal)
    TiledMapRenderer * m_tiledMapRenderer;
    //Zone Renderer (internal)
    ZoneRenderer * m_zoneRenderer;
    
    //Renderers display keys
    NSMutableArray * m_rendererDisplayKeys;
    //MapView renderers
    NSMutableDictionary * m_renderers;
    
#pragma mark - Touch
    
    //Renderers touch keys
    NSMutableArray * m_rendererTouchKeys;
    
#pragma mark - Behaviour
    
    //Boolean used to know if the map slides on pan gestures
    Boolean m_mapSlideActived;
    //Boolean used to know if we lock the map to its boundaries (see: ISZoomLevel)
    Boolean m_boundariesActivated;
}

/*!
 Rendering mode (2D or 3D)
 */
@property (nonatomic, readonly) ISERenderMode renderMode;

/*!
 Last computed ratio.
 */
@property (nonatomic, readonly) double currentRatio;

/*!
 Last computed offset.
 */
@property (nonatomic, readonly) CGPoint currentOffset;

/*!
 MapView manager.
 */
@property (nonatomic, retain) MapDataManager * mapDataManager;

/*!
 Map view events listener.
 */
@property (assign) id<ISPMapListener> mapListener;

/*!
 MapView Cocos layer.
 */
@property (nonatomic, retain) CCLayer * mapLayer;

/*!
 Current displayed map identifier.
 */
@property (nonatomic, readonly) int currentMapId;

/*!
 Current displayed map azimuth.
 */
@property (nonatomic, readonly) float currentAzimuth;

/*!
 Current zoom level.
 */
@property (nonatomic, readonly) float currentZoomLevel;

/*!
 Current rotation angle (in degrees).
 */
@property (nonatomic, readonly) float rotationAngle;

/*!
 Current screen center (in meters).
 */
@property (nonatomic, readonly) CGPoint currentScreenCenter;

/*!
 Tile renderer.
 */
@property (nonatomic, retain) TiledMapRenderer * tiledMapRenderer;

/*!
 Zone renderer.
 */
@property (nonatomic, retain) ZoneRenderer * zoneRenderer;

/*!
 Boolean used to know if the map slides on pan gestures.
 */
@property (nonatomic, readwrite) Boolean mapSlideActived;

/*!
 Boolean used to know if we lock the map to its boundaries (see: ISZoomLevel).
 */
@property (nonatomic, readwrite) Boolean boundariesActivated;

/*!
 Static method used to konw if the Cocos2d engine is initialized.
 @return <b>YES</b> if  it's initialized, otherwise <b>NO</b>.
 */
+ (Boolean)isCocos2dInitialized;

/*!
 Static method used to get a unique render identifier for ISPRTO.
 @return InitProvider unique instance.
 */
+ (int)generateCocos2dUniqueId;

/*
 Intern method used to create the map data manager.
 */
- (void)createMapDataManager;

/*
 Intern method used to start the rendering.
 */
- (void)start;

#pragma mark - Navigation

/*!
 @name Navigation
 */

/*!
 Method used to reset the current map with its default zoom level and start center.
 */
- (void)resetMap;

#pragma mark - Center

/*!
 Method used to center the map on a specific zone.
 @param zoneId Related zone identifer.
 @param animated Boolean used to know if an animation needs to be performed.
 */
- (void)centerMapWithZone:(int)zoneId andAnimated:(Boolean)animated;

/*!
 Method used to center the map on a specific zone.
 @param zoneId Related zone identifer.
 @param animated Boolean used to know if an animation needs to be performed.
 @param duration Wanted animation duration.
 */
- (void)centerMapWithZone:(int)zoneId andAnimated:(Boolean)animated andDuration:(float)duration;

/*!
 Method used to center the map on a specific zone.
 @param zoneId Related zone identifer.
 @param zoomLevel Wanted zoom level.
 @param animated Boolean used to know if an animation needs to be performed.
 @param duration Wanted animation duration.
 */
- (void)centerMapWithZone:(int)zoneId andZoomLevel:(float)zoomLevel andAnimated:(Boolean)animated andDuration:(float)duration;

/*!
 Method used to center the map on a specific position (in meters).
 @param position The position (in meters) to center on (x, y, mapId).
 @param animated Boolean used to know if an animation needs to be performed.
 */
- (void)centerMapWithPosition:(ISPosition *)position andAnimated:(Boolean)animated;

/*!
 Method used to center the map on a specific position (in meters).
 @param position The position (in meters) to center on (x, y, mapId).
 @param animated Boolean used to know if an animation needs to be performed.
 @param duration Wanted animation duration.
 */
- (void)centerMapWithPosition:(ISPosition *)position andAnimated:(Boolean)animated andDuration:(float)duration;

/*!
 Method used to center the map on a specific position (in meters).
 @param position The position (in meters) to center on (x, y, mapId).
 @param rotationAngle Wanted rotation angle.
 @param animated Boolean used to know if an animation needs to be performed.
 */
- (void)centerMapWithPosition:(ISPosition *)position andRotationAngle:(float)rotationAngle andAnimated:(Boolean)animated;

/*!
 Method used to center the map on a specific position (in meters).
 @param position The position (in meters) to center on (x, y, mapId).
 @param rotationAngle Wanted rotation angle.
 @param animated Boolean used to know if an animation needs to be performed.
 @param duration Wanted animation duration.
 */
- (void)centerMapWithPosition:(ISPosition *)position andRotationAngle:(float)rotationAngle andAnimated:(Boolean)animated andDuration:(float)duration;

/*!
 Method used to center the map on a specific position (in meters).
 @param position The position (in meters) to center on (x, y, mapId).
 @param zoomLevel Wanted zoom level.
 @param rotationAngle Wanted rotation angle.
 @param animated Boolean used to know if an animation needs to be performed.
 @param duration Wanted animation duration.
 */
- (void)centerMapWithPosition:(ISPosition *)position andZoomLevel:(float)zoomLevel andRotationAngle:(float)rotationAngle andAnimated:(Boolean)animated andDuration:(float)duration;

#pragma mark - Zoom

/*!
 Method called to zoom in (zoom level++).
 @param animated Boolean used to know if an animation needs to be performed.
 */
- (void)zoomIn:(Boolean)animated;

/*!
 Method called to zoom out (zoom level--).
 @param animated Boolean used to know if an animation needs to be performed.
 */
- (void)zoomOut:(Boolean)animated;

/*!
 Method called to zoom to a zoom level for a specific map. We keep the current center position.
 @param zoomLevel Wanted zoom level.
 @param animated A Boolean used to know if we zoom with animation.
 */
- (void)zoomWithZoomLevel:(float)zoomLevel andAnimated:(Boolean)animated;

/*!
 Method called to zoom to a zoom level for a specific map. We keep the current center position.
 @param zoomLevel Wanted zoom level.
 @param animated A Boolean used to know if we zoom with animation.
 @param duration Wanted animation duration.
 */
- (void)zoomWithZoomLevel:(float)zoomLevel andAnimated:(Boolean)animated andDuration:(float)duration;

/*!
 Method called to zoom to a span rect (in meters).
 @param span A rectangle defining the viewport to match.
 @param animated A Boolean used to know if we zoom with animation.
 */
- (void)zoomToSpan:(ISRectF *)span andAnimated:(Boolean)animated;

/*!
 Method called to zoom to a span rect (in meters).
 @param span A rectangle defining the viewport to match.
 @param animated A Boolean used to know if we zoom with animation.
 @param duration Wanted animation duration.
 */
- (void)zoomToSpan:(ISRectF *)span andAnimated:(Boolean)animated andDuration:(float)duration;

#pragma mark - Rotate

/*!
 Method called to rotate the map according a specific angle.
 @param angle The angle to rotate.
 @param animated A Boolean used to know if we rotate with animation.
 */
- (void)rotateWithAngle:(float)angle andAnimated:(Boolean)animated;

/*!
 Method called to rotate the map according a specific angle.
 @param angle The angle to rotate.
 @param animated A Boolean used to know if we rotate with animation.
 @param duration Wanted animation duration.
 */
- (void)rotateWithAngle:(float)angle andAnimated:(Boolean)animated andDuration:(float)duration;

#pragma mark - Change

/*!
 Method used to show a Map with its id.
 @param mapId The Map id to show.
 @param keepPosition Boolean used to know if we keep the current position when changing map.
 @param keepZoomLevel Boolean used to know if we keep the current zoom level when changing map.
 @param keepRotationAngle Boolean used to know if we keep the current rotation angle when changing map.
 */
- (Boolean)changeMapWithMapId:(int)mapId andKeepPosition:(Boolean)keepPosition andKeepZoomLevel:(Boolean)keepZoomLevel andKeepRotationAngle:(Boolean)keepRotationAngle;

#pragma mark - Rendering

/*
 Intern method used to update all map renderers.
 */
- (void)updateRenderers;

/*!
 Method used to start map rendering.
 */
- (void)startRendering;

/*!
 Method used to stop map rendering.
 */
- (void)stopRendering;

/*!
 Method used to know if the map is currently rendering.
 @return <b>YES</b> if the map is currently rendering, otherwise <b>NO</b>.
 */
- (Boolean)isRendering;

/*!
 Method used to hide the background color (transparent behaviour).
 */
- (void)disableBackground;

#pragma mark - Renderer Management

/*!
 Method used to get a specific map Renderer.
 @param rtoClass The Renderer corresponding class.
 @return The corresponding Renderer, nil if not exists.
 */
- (id<ISPRenderer>)getRendererWithRTOClass:(Class)rtoClass;

/*!
 Method used to know if the map view has a specific renderer.
 @param rtoClass The Renderer corresponding class.
 @return <b>YES</b> if the map has the specified renderer, otherwise <b>NO</b>.
 */
- (Boolean)hasRenderer:(Class)rtoClass;

/*!
 Method used to add a specific Renderer (layer).
 @param renderer The Renderer to add.
 @return Boolean used to know if the Renderer has been successfully added.
 */
- (Boolean)addRenderer:(id<ISPRenderer>)renderer;

/*!
 Method used to remove a specific Renderer (layer) according to its related RTO class.
 @param rtoClass The related RTO class.
 */
- (void)removeRendererWithRtoClass:(Class)rtoClass;

/*!
 Method used to remove a specific Renderer.
 @param renderer The renderer to remove.
 */
- (void)removeRenderer:(id<ISPRenderer>)renderer;

/*!
 Method used to clear a specific Renderer.
 @param rtoClass The related RTO class.
 */
- (void)clearRendererWithRTOClass:(Class)rtoClass;

/*!
 Method called to set a priority to a specific Renderer.
 @param rtoClass The related RTO class.
 @param priority The priority to update.
 */
- (void)setRendererPriorityWithRTOClass:(Class)rtoClass andPriority:(int)priority;

/*!
 Method called to specify if a Renderer need to be displayed.
 @param rtoClass The related RTO class.
 @param display Boolean used to set if the Renderer will be displayed.
 */
- (void)setRendererDisplayWithRTOClass:(Class)rtoClass andDisplay:(Boolean)display;

/*!
 Method called to specify if a Renderer need to answer on a touch event.
 @param rtoClass The related RTO class.
 @param touch Boolean used to set if the Renderer will handle touch events.
 */
- (void)setRendererTouchWithRTOClass:(Class)rtoClass andTouch:(Boolean)touch;

#pragma mark - RTO Management

/*!
 Method used to add a simple RenderingTouchObject.
 @param rto The RTO to add.
 @return Boolean used to know if a new ISGenericRenderer was created.
 */
- (Boolean)addRTO:(id<ISPRTO>)rto;

/*!
 Method used to add a RTO on a specific Zone.
 @param rto The RTO to add.
 @param zoneId The Zone id in which add the RTO.
 @return Boolean used to know if a new ISGenericRenderer was created.
 */
- (Boolean)addRTO:(id<ISPRTO>)rto inZone:(int)zoneId;

/*!
 Method used to add a RTO on a specific Zone with a specific offset.
 @param rto The RTO to add.
 @param zoneId The Zone id in which add the RTO.
 @param offset Zone offset to consider.
 @return Boolean used to know if a new ISGenericRenderer was created.
 */
- (Boolean)addRTO:(id<ISPRTO>)rto inZone:(int)zoneId withOffset:(CC3Vector)offset;

/*!
 Method used to add a RTO with a specific Zone/Poi association.
 @param rto The RTO to add.
 @param zonePoi The Zone/Poi association to add from.
 @return Boolean used to know if a new ISGenericRenderer was created.
 */
- (Boolean)addRTO:(id<ISPRTO>)rto inZonePoi:(ISZonePoi *)zonePoi;

/*!
 Method called to remove an RTO from all zones where it's located.
 @param rto The RTO to remove.
 */
- (void)removeRTO:(id<ISPRTO>)rto;

/*!
 Method called to remove an RTO from a specific Zone.
 @param rto The RTO to remove.
 @param zoneId The Zone id from which remove the RTO.
 */
- (void)removeRTO:(id<ISPRTO>)rto fromZone:(int)zoneId;

/*!
 Method called to remove all the RTO present in the Zone.
 @param zoneId id The concerned Zone.
 */
- (void)clearZone:(int)zoneId;

/*!
 Method called to remove all the RTO.
 */
- (void)clear;

/*!
 Method used to get all RTO from a given zone identifier.
 @param zoneId Corresponding zone identifier.
 @return An array of all linked RTO (could be nil).
 */
- (NSArray *)getRTOsWithZoneId:(int)zoneId;

#pragma mark - Touch

/*!
 @name Touch
 */

/*!
 Method called to set a listener to a specific renderer.
 @param rtoListener The listener to set.
 @param rtoClass The related RTO class.
 */
- (void)setRTOListener:(id<ISPRTOListener>)rtoListener withRTOClass:(Class)rtoClass;

/*
 Method called when the user put his finger over the screen of the iPhone.
 */
- (Boolean)touchesBeganWithTouch:(ISTouch *)touch;

/*
 Method called when the user moves his finger over the screen of the iPhone.
 */
- (Boolean)touchesMovedWithTouch:(ISTouch *)touch;

/*
 Method called when the user releases the screen of the iPhone with his finger.
 */
- (Boolean)touchesEndedWithTouch:(ISTouch *)touch;

@end
