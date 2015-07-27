# InsiteoSDK

Insiteo is a provider of indoor location based services such as Map rendering, Location, Itinerary and Geofencing. For further integration documentation you can have a look at the developer's site: [http://dev.insiteo.com/api](http://dev.insiteo.com/api).

This sample application will demonstrate how to take full advantage of those services and integrate them in your application.

If you wish to evaluate indoor location in your own building, you can order our test pack including 8 BLE beacons here:
[http://www.insiteo.com/joomla/index.php/en/contact-us](http://www.insiteo.com/joomla/index.php/en/contact-us).

If you want more information on our services [http://www.insiteo.com/joomla/index.php](http://www.insiteo.com/joomla/index.php)

## Installation

### From CocoaPods

InsiteoSDK is available through CocoaPods. To install it, simply add the following line to your Podfile:

```ruby
platform :ios, '5.1.1'
pod 'InsiteoSDK', :podspec => 'http://dev.insiteo.com/api/download/ios/3.4.1/InsiteoSDK.podspec'
```

### Manual

Download the `InsiteoSDK` [here](http://dev.insiteo.com/api/download/ios/3.4.1/InsiteoSDK.zip).

INSITEO 's modules are provided as an iOS `library` and an iOS `bundle`. To use them, you will need to link it with your application project. To do that, simply add the `InsiteoSDK` folder to you project.

![alt tag](http://dev.insiteo.com/api/img/ios-project-integration.png)

> **Note** If you plan to use our 3D features, don't forget to add the `glsl` folder in your application resources.

Then you will need to add all the wanted frameworks in the `Link Binary With Libraries` panel. Please also check the framework dependencies below and add any additional required framework. The InsiteoSDK `library` requires the following frameworks and libraries:

- Apple `CoreBluetooth.framework` for location purposes
- Apple `CoreGraphics.framework` for rendering purposes
- Apple `CoreLocation.framework` for location purposes
- Apple `CoreMotion.framework` for location purposes
- Apple `CoreTelephony.framework` for analytics purposes
- Apple `CoreText.framework` for rendering purposes
- Apple `Foundation.framework`
- Apple `OpenAL.framework` for rendering purposes
- Apple `OpenGLES.framework` for rendering purposes
- Apple `QuartzCore.framework` for rendering purposes
- Apple `Security.framework`
- Apple `UIKit.framework`
- Apple `libstdc++.6.0.9.dylib`
- Apple `libz.dylib`
- Apple `libsqlite3.dylib`

Don't forget to add the `-ObjC` flag in your build settings `Other linker flags` section.

> **Requirements**
 - The INSITEO `library` requires `iOS 5.1.1` or later.
 - The library is optimized for `armv7` and `arm64`.

> **Note:** The Insiteo library is now fully ARC compatible.

> **Looking for an older version?** You can get an older version of the SDK in the [releases](https://github.com/Insiteo/iOS/releases) section.

## API reference

[http://dev.insiteo.com/api/doc/ios/3.4/index.html](http://dev.insiteo.com/api/doc/ios/3.4/index.html)

## Initialization

### Initialize the API and start a site

> **All your information in one single file** We highly recommend you to store all your account information, such as your API key, your server type and so on, in your application `.plist` file. We will provide you such information.

```xml
  ...
  <key>ISApiKey</key>
  <string>YOUR-API-KEY</string>
  <key>ISAnalyticsAutoStart</key>
  <true/>
  <!-- In order to get ready to use our map module, you will need to specify the render mode you plan to use. You can choose between ISERenderMode2D and ISERenderMode3D. Please note that the default mode is ISERenderMode2D. -->
  <key>ISERenderMode</key>
  <string>ISERenderMode3D</string>
  <!-- The initialization process requires a ISEServerType that can take the following values: ISEServerTypeDev, ISEServerTypeTest or ISEServerTypeProd. Depending on its values the downloaded data will be stored under the appropriate folder (respectively 'dev', 'test' and 'release'). -->
  <key>ISEServerType</key>
  <string>ISEServerTypeTest</string>
  ...
 </dict>
</plist>
```

The first step to access Insiteo's services, is to initialize our API via the [`Insiteo`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/Insiteo.html) singleton. This will be done with the [`launchWithInitializeHandler`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/Insiteo.html#//api/name/launchWithInitializeHandler:andChooseSiteHandler:andStartHandler:andUpdateHandler:andUpdateProgressHandler:). You will be then notified of API initialization through block handlers you specified.

Here is a snippet that will show you how to properly do the initialization process:

```objectivec++
//Initialize the API
[[Insiteo sharedInstance] launchWithInitializeHandler:^(ISError * error, ISUserSite * suggestedSite, Boolean fromLocalCache) {
    //Check initialization status
    Boolean initializationSuccess = (error == nil);
} andChooseSiteHandler:^CLLocation * {
    //You can return here a CLLocation that will determine the most suitable site to start
    return [[CLLocation alloc] initWithLatitude:latitude longitude:longitude];
} andStartHandler:^(ISError * error, NSArray * newPackages) {
    //Check start status
    if (error == nil) {
        //Success!
        Boolean updateAvailable = ([newPackages count] > 0);
    } else {
        //[1] It means that INSITEO servers could not be reached. If you want to use an INSITEO module, you have to check if your application has enough data to run. This can be done using hasPackageWithPackageType:andServerType on Insiteo singleton.
    }
} andUpdateHandler:^(ISError * error) {
    //Check update status
    if (error == nil) {
        //Success! You can now launch your application with all up to date data.
    } else {
        //An error occured, same as [1]
    }
} andUpdateProgressHandler:^(ISEPackageType packageType, Boolean download, int progress, int total) {
    //Here you get the current treated package type and you can know if we are currently downloading or installing it

    //And you can compute total progress to update your loading view for example
    float totalProgress = (float)progress / (float)total;
}];

//Note: The initialization process can be cancelled using the currentTask property of the Insiteo singleton (see ISPCancelable protocol documentation).
```

#### Handle the initialization process in background

The [`launchWithInitializeHandler`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/Insiteo.html#//api/name/launchWithInitializeHandler:andChooseSiteHandler:andStartHandler:andUpdateHandler:andUpdateProgressHandler:) method is asynchronous. Be sure to provide valid blocks handler to be notified of initialization events.

> **Note:** If you wish to handle all the initialization steps manually you can individually call `initializeWithInitializeHandler:`, `startWithSite:` and `updateCurrentSiteWithWantedPackages:`. For more details please refer to the documentation and the sample app example.

#### Change the current site

You can easily change the current site by calling the [`startAndUpdateWithSite`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/Insiteo.html#//api/name/startAndUpdateWithSite:andStartHandler:andUpdateHandler:andUpdateProgressHandler:) method on the [`Insiteo`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/Insiteo.html) singleton.

## Where to go from there?

- [Display your first map](readme/map.md).
- [Get your first location](readme/location.md).
- [Configure your iBeacons](readme/beacon.md).
- [Compute your first itinerary](readme/itinerary.md).
- [Setup your first geofencing zone](readme/geofence.md).
- [Enable analytics](readme/analytics.md).
