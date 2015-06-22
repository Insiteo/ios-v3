## Location

> **Packages dependencies** If you intend to use this service you have to make sure that the `location` package have been properly downloaded. You can easily check if the package is available on the device with the following method: `[[Insiteo currentSite] hasPackage:ISEPackageTypeLocation]`.

> **iOS 8 compatibility** In order to be iOS 8 fully compatible, you will need to add the `NSLocationWhenInUseUsageDescription` key in your `.plist`. You can leave the corresponding value empty or specify a custom message that will be displayed the first time the SDK will ask to use the location service.

### Location process

![alt tag](http://dev.insiteo.com/api/img/LocationLost.png)

![alt tag](http://dev.insiteo.com/api/img/StartNoBeacons.png)

![alt tag](http://dev.insiteo.com/api/img/StartNoLoc.png)

### Get your first location

You can use our `LocationAPI` to obtain location information. The `LocationAPI` needs initialization information in order to communicate with our servers. You can easily link this library to the INSITEO map, so the location can be displayed on it.

In order to use our `LocationAPI`, you will need to get the [`ISLocationProvider`](http://dev.insiteo.com/api/doc/ios/Classes/3.4/ISLocationProvider.html) singleton.

To receive location, you will need to start the [`ISLocationProvider`](http://dev.insiteo.com/api/doc/ios/Classes/3.4/ISLocationProvider.html), with a [`ISLocationDelegate`](http://dev.insiteo.com/api/doc/ios/Protocols/ISLocationDelegate.html):

> **Which flags to use** By default we will use the location flags described in your `.plist`. Please contact us to get the appropriate location settings.

```xml
  ...
  <key>ISELocationFlag</key>
  <array>
   <string>ISELocationFlagGps</string>
   <string>ISELocationFlagBle</string>
   <string>ISELocationFlagCompass</string>
   <string>ISELocationFlagMems</string>
  </array>
 </dict>
</plist>
```

```objectivec++
//Start location
[[ISLocationProvider sharedInstance] startWithDelegate:aDelegate];

//Add location renderer to the ISMapView, thus location is displayed on map
[mapView addRenderer:[locProvider renderer]];
```

> **Prerequisites**
- The API needs to be initialized.
- You can now be notified when no registered beacons were detected, which probably means that the user started the location whereas he is not on site.

### Available services

Available location-based services are:

- `ISELbsModuleTypeItinerary`: this module computes the route between an arrival point, and a departure point (could be the user current location).
- `ISELbsModuleTypeGeofencing`: this module detects when user location is in "active" areas, and notify the application that the user entered/stayed in/left these areas.

#### Get a specific LBS module

To use them, you have to request them from [`ISLocationProvider`](http://dev.insiteo.com/api/doc/ios/Classes/3.4/ISLocationProvider.html) with the [`getLbsModule`](http://dev.insiteo.com/api/doc/ios/Classes/3.4/ISLocationProvider.html#//api/name/getLbsModule:) method.

## Where to go from there?

- [Configure your iBeacons](beacon.md).
- [Compute your first itinerary](itinerary.md).
- [Setup your first geofencing zone](geofence.md).
- [Enable analytics](analytics.md).

## You missed a thing?

- [Project setup](../README.md).
- [Display your first map](map.md).
