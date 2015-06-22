## Geofencing

> **Packages dependencies** If you intend to use the this service you have to make sure that the `geofencing` package have been properly downloaded. You can easily check if the package is available on the device with the following method: `[[Insiteo currentSite] hasPackage:ISEPackageTypeGeofencing]`.

### Start the Geofencing module

To start the `Geofencing` module, simply do like so:

```objectivec++
//Get the geofencing module from the location provider
ISGeofenceProvider * geofenceProvider = [m_locationProvider getLbsModule:ISEPackageTypeGeofencing];
    
//"Start" geofencing
[geofenceProvider setdelegate:delegate];
```

### Understand geonotifications

After starting the module, your delegate will be notified with 3 arrays of [`ISGeoFenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html).

- The first one contains all zones the user just entered.
- The second one contains all zones where the user still is and has spent a certain time.
- The third one contains all zones the user just left.

```objectivec++
//Method alled when geofencing module has new data available
- (void)onGeofenceDataUpdateWithEnteredAreas:(NSArray *)enteredAreas andStayedAreas:(NSArray *)stayedAreas andLeftAreas:(NSArray *)leftAreas {
    //Entered areas
  for (ISGeofenceArea * geoArea in enteredAreas) {
        NSLog(@"User entered area %@", geoArea.GUID);
    }

    //Stayed areas
    for (ISGeofenceArea * geoArea in stayedAreas) {
        NSLog(@"User still is in area %@", geoArea.GUID);
    }

    //Left areas
    for (ISGeofenceArea * geoArea in leftAreas) {
        NSLog(@"User has left area %@", geoArea.GUID);
    }
}
```

### Dynamic geofencing

In the last version of our API, geopush content can be added to the [`ISGeofenceProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceProvider.html) directly from your application in addition to the one fetched from the server. This enables, for example, your content to be more accurate to a specific user's behaviour or using context.

- The created [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html)'s polygon will be based on the specific [`ISZone`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISZone.html) parameters that have to be provided in the back office.
- If the [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html) parameters (ie width, enteredTime, enteredEnabled...) are not set they will be fetched from the configuration file. This configuration file defines those parameters by [`ISMap`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISMap.html) and not by [`ISZone`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISZone.html).
- If the creation succeeded the [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html) will be automatically added to the [`ISGeofenceProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceProvider.html).

#### Adding content to a specific zone or for a specific zone/poi association

To add a geopush content to a specific [`ISZone`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISZone.html) or [`ISZonePoi`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISZonePoi.html), you can use the methods shown below.

A polygon based on the ISZone parameters and the provided [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html) width will be created and this [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html) will be automatically added to the [`ISGeofenceProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceProvider.html).

```objectivec++
//For a ISZone
- (ISGeofenceArea *)addGeofenceAreaWithZoneId:(int)zoneId andLabel:(NSString *)label andMessage:(NSString *)message;

- (ISGeofenceArea *)addGeofenceAreaWithZoneId:(int)zoneId andPolygon:(NSMutableArray *)polygon andLabel:(NSString *)label andMessage:(NSString *)message;
...

//For a ISZonePoi association
- (ISGeofenceArea *)addGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi andLabel:(NSString *)label andMessage:(NSString *)message;

- (ISGeofenceArea *)addGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi andPolygon:(NSMutableArray *)polygon andLabel:(NSString *)label andMessage:(NSString *)message;
...
```

#### Adding content for a given position

To add a geopush content at a specific [`ISPosition`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISPosition.html), you can use the methods shown below.

A square of size on the given parameter (or by default 4 time the size defined in the configuration file) and center on the given position will be created.

```objectivec++
- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andLabel:(NSString *)label andMessage:(NSString *)message;

- (ISGeofenceArea *)addGeofenceAreaWithGUID:(NSString *)guid andCenter:(ISPosition *)center andLabel:(NSString *)label andMessage:(NSString *)message andEventTime:(float)eventTime;
...
```

#### Removing a dynamic geofence area

To remove a [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html) from the [`ISGeofenceProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceProvider.html) call the appropriate remove method based on how it was added.

```objectivec++
- (void)removeGeofenceAreaWithGuid:(NSString *)guid;

- (void)removeGeofenceAreaWithZoneId:(int)zoneId;

- (void)removeGeofenceAreaWithZonePoi:(ISZonePoi *)zonePoi;

- (void)removeGeofenceAreaWithArea:(ISGeofenceArea *)area;
```

### Geofencing rendering

You can now view your [`ISGeofenceArea`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISGeofenceArea.html) on your [`ISMapView`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISMapView.html). Like all other LBS services, you will have to retrieve its [`ISRenderer`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRenderer.html) and pass it to the [`ISMapView`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISMapView.html). All the geofencing zone will be displayed ie the one define on the back office that one created dynamically.

> **Note:** 3D rendering is not available for this module.

## Where to go from there?

- [Enable analytics](analytics.md).

## You missed a thing?

- [Project setup](../README.md).
- [Display your first map](map.md).
- [Get your first location](location.md).
- [Configure your iBeacons](beacon.md).
- [Compute your first itinerary](itinerary.md).