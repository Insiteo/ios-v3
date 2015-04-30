## Map

> **2D or 3D** Be aware, that you can't use both 2D and 3D in the same running application. Don't forget to add the `glsl` folder in your application resources, otherwise the 3D engine won't work.

> **Packages dependencies** Be aware that you need to have installed at least the following packages:
- A `ISEPackageTypeMapData` package, which contains maps information such as zoom levels and scales.
- A `ISEPackageTypeTiles` package, which contains `.3cm` files that will be displayed.
- **3D only** A `ISEPackageTypeMap3d` package, which contains all 3D files.

> You can easily check if the package is available on the device with the following method: `[[Insiteo currentSite] hasPackage:ISEPackageTypeMapData]`.

### Display a MapView

A [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) is provided and can be used to display a 2D/3D map component with specific interactive areas. The API also provides advanced features such as additional rendering layouts management (promotional, special areas etc &#8230;) or specific events handling. To use this component you have to make sure that you have downloaded all the required packages.

The [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) will display a 2D tiled map or 3D plane of the site (depending on your `ISERenderMode`), and provide common map interaction (such as move, center, and pinch to zoom), animation and more. It also handle the [`ISZone`](http://dev.insiteo.com/api/doc/ios/Classes/ISZone.html) rendering and touch behavior.

The [`ISMap2DView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMap2DView.html) uses the [`Cocos2D`](http://cocos2d.spritebuilder.com/) Objective-C 2D engine and you can refer to its documentation [here](http://www.cocos2d-swift.org/docs/).

The [`ISMap3DView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMap3DView.html) uses the [`Cocos3D`](http://cocos3d.org/) Objective-C 3D engine (based on Cocos2D) and you can refer to its documentation [here](http://cocos3d.org/api/index.html).

In order to use our `MapAPI`, you will need to get an [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html):

```objectivec++
//ISMap2DView initialization
[ISMap2DView getMap2DViewWithFrame:self.view.frame andDelegate:self andHandler:^(ISMap2DView * map2DView) {
    //At this point, the map view is correctly initialized
    [self.view addSubView:map2DView];
}];

//ISMap3DView initialization
[ISMap3DView getMap3DViewWithFrame:self.view.frame andDelegate:self andHandler:^(ISMap3DView * map3DView) {
    //At this point, the map view is correctly initialized
    [self.view addSubView:map3DView];
}];
```

> **Prerequisites** You will need to initialize the [`Insiteo`](http://dev.insiteo.com/api/doc/ios/Classes/Insiteo.html) singleton before instantiating [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html). [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) events will be notified via the [`ISMapViewDelegate`](http://dev.insiteo.com/api/doc/ios/Protocols/ISMapViewDelegate.html) protocol.

### Adding graphical objects on map

The [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) also allows you to display custom interactive objects. This can be done by implementing the renderer interface [`ISRenderer`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html) and the Render Touch Object interface [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) or by simply extending the [`ISGenericRenderer`](http://dev.insiteo.com/api/doc/ios/Classes/ISGenericRenderer.html) and [`ISGenericRTO`](http://dev.insiteo.com/api/doc/ios/Classes/ISGenericRTO.html) that already provide common behavior (icon and label rendering, touch handling and so on, you can check their behavior in our SampleApp).

The [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) will also detect touches, and dispatch them to all [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html). A delegate can be set on the map view, to be notified of clicks on specific [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) class (see [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) class documentation).

Adding, removing [`ISGenericRTO`](http://dev.insiteo.com/api/doc/ios/Classes/ISGenericRTO.html) to the [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) and listening for their events:

```objectivec++
//This method will add the rto at a given position
ISGenericRTO * rto = [[ISGenericRTO alloc] initWithName:@"My RTO name" andLabel:@"My RTO" andMetersPosition:givenPosition andWindowDisplayed:YES andLabelDisplayed:YES];
[m_mapView addRTO:rto];
[rto release];

//And to remove it
[m_mapView removeRTO:rto];

//This method will add the rto to the given zone
ISGenericRTO * rto = [[ISGenericRTO alloc] initWithName:zonePoi.externalPoiId andLabel:@"My RTO" andMetersPosition:nil andWindowDisplayed:YES andLabelDisplayed:YES];
[m_mapView addRTO:rto inZone:zonePoi.zoneId];
[rto release];

//And to remove it
[m_mapView removeRTO:rto fromZone:zoneId];

//Add a delegate for this type of IRTO
[m_mapView setRTODelegate:rtoDelegate withRTOClass:[GfxRTO class]];
```

### Create your own ISRenderer

A renderer is a class that defines drawing and touch behavior for a certain type of [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html). Once added to the [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) a renderer will have its [`render2D`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html#//api/name/render2DWithLayer:andRatio:andOffset:andAngle:) or [`render3D`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html#//api/name/render3DWithScene:andRatio:andAngle:) method call by the map rendering loop to enable to do its rendering operation and it will also be notify when to handle touch events ([`onTouchDown`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html#//api/name/onTouchDown:), [`onTouchMove`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html#//api/name/onTouchMove:), [`onTouchUp`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html#//api/name/onTouchUp:)). If you want to use your own customized renderer, you will need to create a class that implements the [`ISRenderer`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html) interface. Then you will be able to specify your own renderering and touch behavior. 

[`ISRenderer`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html) uses a priority value that will define it's 2D rendering and touch order. Highest priority renderered last (so on the top) and notify by touch first.

To register a new renderer as a map's renderer, simply do like this:

```objectivec++
//How to add a custom renderer
[mapView addRenderer:aRenderer]];
```

### Create your own ISRTO

To draw a customized rendering object on the map, you will need to create a class that implements the [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) interface. Then you will be able to specify your object's behavior through methods like:

```objectivec++
//The 2D method you will need to override in order to manually manage your object rendering
- (void)render2DWithLayer:(CCLayer *)layer andRatio:(double)ratio andOffset:(CGPoint)offset andAngle:(float)angle andPriority:(int)priority;

//The 3D method you will need to override in order to manually manage your object rendering
- (void)render3DWithScene:(CC3Scene *)scene andLayer:(CC3Node *)layer andCurrentMap:(ISMap *)map andRatio:(float)ratio andAngle:(float)angle andPriority:(int)priority;

//Because once added to the world a 3D object will always be drawn it is up to you to remove the object from the world when required
- (void)remove3DFromLayer:(CC3Node *)layer;

//Method that gets called when the IRTO have to handle a touch down event
- (ISETouchObjectResult)onTouchDown:(ISTouch *)touch;
```

#### Where to find my ISRTO?

All [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) of class corresponding to the custom renderer class, when added via [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html), will be put in custom renderer. If you add an [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) and there are no [`ISRenderer`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html) defined for that specific class, the [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html) will automatically create a [`ISGenericRenderer`](http://dev.insiteo.com/api/doc/ios/Classes/ISGenericRenderer.html) to handle it. So creating your own [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) does not mean that you necessarily have to create you own [`ISRenderer`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html).

#### Zone offsets in 3D

In 3D, you can specify an offset through the z axis still by using the following method [`addRTO:inZone:withOffset:`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html#//api/name/addRTO:inZone:withOffset:).

### Link with external content

With the Insiteo framework, you can link your content to our zone based system. To do that you will have to register this content through our back office. For example you can link a shop to one of our zone and then, get back this content in your application, simply by requesting our framework.

[![alt tag](http://img.youtube.com/vi/CLvNfQuzyUw/0.jpg)](https://www.youtube.com/watch?v=CLvNfQuzyUw)

[Insiteo Interactive maps - 2 minutes tutorial](https://www.youtube.com/watch?v=CLvNfQuzyUw)

To get all related Insiteo zones for a given external POI, you can use the [`ISDBHelperMap`](http://dev.insiteo.com/api/doc/ios/Classes/ISDBHelperMap.html) class like so:

```objectivec++
//Get all Zone/POI assocations for a given external identifier
NSArray * zonesPois = [ISDBHelperMap getExternalZonePoisForExtIdPoi:externalPoiId];
```

> **Note:** An array is returned, because you can link a POI to several zones and a zone can contains several POIs.

To get all POIs related to a given Insiteo zone, you can use the [`ISDBHelperMap`](http://dev.insiteo.com/api/doc/ios/Classes/ISDBHelperMap.html) class like so:

```objectivec++
//Get all external Zone/POI assocations for a given zone identifier
NSArray * zonesPois = [ISDBHelperMap getZonePoisForIdZone:zoneId andExternal:YES];
```

Each method returns an [`ISZonePoi`](http://dev.insiteo.com/api/doc/ios/Classes/ISZonePoi.html) object which contains a position in meters and an offset (if specified) in order to place your on [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) on our map.

#### Zone/Poi associations offsets

If you want an offset to be used when drawing an [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) in a [`ISZone`](http://dev.insiteo.com/api/doc/ios/Classes/ISZone.html) you have to explicitly set it we adding the [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) to the [`ISMapView`](http://dev.insiteo.com/api/doc/ios/Classes/ISMapView.html).

### Best practices

We recommend you to start and stop the map rendering according to the parent UIViewController state changes.

```objectivec++
//Insiteo
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [mapView startRendering];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    [mapView stopRendering];
}
```

## Where to go from there?

- [Get your first location](location.md).
- [Configure your iBeacons](beacon.md).
- [Compute your first itinerary](itinerary.md).
- [Setup your first geofencing zone](geofence.md).
- [Enable analytics](analytics.md).

## You missed a thing?

- [Project setup](../README.md).
