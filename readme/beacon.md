## Beacons

> **Don't forget to create your regions on the back office** If you intend to use this service you have to make sure that your beacon regions have been properly created on the back office.

> **Only supported on iOS 7.0 or higher** This service is only supported in iOS 7.0 or higher.

> **iOS 8 compatibility** In order to be iOS 8 fully compatible, you will need to add the `NSLocationWhenInUseUsageDescription` key and the `NSLocationAlwaysUsageDescription` in your `.plist`. You can leave the corresponding value empty or specify a custom message that will be displayed the first time the SDK will ask to use the location service.

> **Prerequisites**
- The API has to be initialized at least once to retrieve your back office configuration.

### Start beacon regions management

In order to start the beacon regions management, you need to start the [`ISBeaconProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconProvider.html) singleton with the [`startWithDelegate`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconProvider.html#//api/name/startWithDelegate:) method. We highly recommend to start the provider in the `application:didFinishLaunchingWithOptions:` method of your `AppDelegate` in order to be started when the application is launched.

In order to use our the beacon regions management, you will need to start the [`ISBeaconProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconProvider.html) singleton. To be notified on region entry, exit, etc. you have to pass a [`ISBeaconDelegate`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html)

```objectivec++
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    //Start the beacon provider and set the ISBeaconDelegate (your AppDelegate for example)
    [[ISBeaconProvider sharedInstance] startWithDelegate:self];
    ...
}
```

> **Note:** A beacon region is represented by the [`ISBeaconRegion`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconRegion.html) object and a physical beacon device is represented by the [`ISBeacon`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeacon.html) object. The regions will be created according to your back office configuration.

### Beacon region notifications

The [`ISBeaconDelegate`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html) protocol provides a couple of callback methods to be notified when a user enters or exits an [`ISBeaconRegion`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconRegion.html) or if an [`ISBeacon`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeacon.html) has reached its beacon region `proximity`, according to your back office configuration.

### Notifications on Entry and Exit

The [`onEnterBeaconRegion:`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html#//api/name/onEnterBeaconRegion:) and the [`onExitBeaconRegion:`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html#//api/name/onExitBeaconRegion:) methods are called when a user enters or exits a specific beacon region (those two methods are required when implemeting the protocol).

You could also implement two optionnal methods: [`onEnterBeacon:forRegion:`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html#//api/name/onEnterBeacon:forRegion:) and [`onExitBeacon:forRegion:`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html#//api/name/onExitBeacon:forRegion:) to be notified when a beacon has reached its beacon region `proximity` (enter) or when the beacon proximity does not match anymore (exit).

### Customize a Beacon Region Entry

> **Note:** The notification will be presented only if the message field is not empty on the back office.

By defaut, on beacon region entry, the SDK presents a `UILocalNotification` displaying the beacon region [`message`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconRegion.html#//api/name/message) and store all its information in a `NSDictionary` into the `notification.userInfo` which could be retrieved using the `ISBeaconRegionKeys` specific key.

To retrieve a specific beacon region information from the `NSDictionary` when user swipe the presented notification on screen, you could use the specific keys defined in the [`ISBeaconProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconProvider.html), in the `application:didReceiveLocalNotification:`:

```objectivec++
- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    //Get entered beacon region information
    NSDictionary * beaconRegionsKeys = [notification.userInfo objectForKey:ISBeaconRegionKeys];
    //Then retrieve desired information using other specific keys provided by the ISBeaconProvider
    //(ex: ISBeaconRegionUUIDKey, ISBeaconRegionMajorKey, ISBeaconRegionMinorKey, etc.)
}
```

You could override the presentation of the `UILocalNotification` or only tell the SDK to display nothing, by implementing the [`shouldPresentLocalNotificationOnBeaconRegionEntry:`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html#//api/name/shouldPresentLocalNotificationOnBeaconRegionEntry:) method.

To disable the `UILocalNotification` presentation for all beacon regions just `return NO`. Then, if you only want to disable the notification for a specific region, `return NO` for that one, and `return YES` for the others. Finally, if you want to display by yourself the notification, implement your code then `return NO`:

```objectivec++
- (BOOL)shouldPresentLocalNotificationOnBeaconRegionEntry:(ISBeaconRegion *)beaconRegion {
    //First case, disable notification for each Beacon Region
    return NO;

    //Second case, only disable for a specific Beacon Region (ex: customId == @"no-notif")
    if ([beaconRegion.customId isEqualToString:@"no-notif"]) {
        return NO;
    } else {
        return YES;
    }

    //Third case, disable notification and present a UILocalNotification on your own
    UILocalNotification * notification = [[UILocalNotification alloc] init];
    notification.alertBody = [NSString stringWithFormat:@"%@", beaconRegion.customId];
    notification.soundName = UILocalNotificationDefaultSoundName;
    [[UIApplication sharedApplication] presentLocalNotificationNow:notification];

    return NO;
}
```

Finally, you could specify a delay to schedule the default notification on region entry (which will be cancelled on region exit) using the Custom field in the Back Office. The field should be a JSON string like : `{"delay": <delay_in_seconds>}`.

### Get ranged beacons for an entered beacon region

When a user enters in a beacon region, the beacon provider starts ranging beacons for that specific region. In order to retrieve beacons ranging information, you should implement the [`rangedBeacons:andReachedProximityBeacons:inRegion:andUnknownCLBeacons:withError:`](http://dev.insiteo.com/api/doc/ios/Protocols/ISBeaconDelegate.html#//api/name/rangedBeacons:andReachedProximityBeacons:inRegion:andUnknownCLBeacons:withError:) method, which provides all ranged beacons (created on the back office or unknown but detected by the OS), and all beacons which have reached the `proximity` of the beacon region.

### Check for beacons configuration update

As your beacon regions may have changed since your application was killed, the [`ISBeaconProvider`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISBeaconProvider.html) will automatically check on the back office, if the region is always available or if its notification message has changed, before any notification on region entry.

> **Note:** If data network connections are not available, the last known configuration will be used.

If you attempt to force an API initialization on application wake up, you could for example implements the code snippet below into your `AppDelegate`:

```objectivec++
#define kTimeToReinit 3600 //ex: every 1 hour, beacon regions are updated on the back office

- (void)applicationDidBecomeActive:(UIApplication *)application {
    ...
    //Check if user is authenticated
    if ([[Insiteo sharedInstance] isAuthenticated]) {
        //Get last API initialization date
        NSDate * lastInit = [Insiteo currentUser].lastInitializationDate;
        //Check the interval between now
        double interval = [[NSDate date] timeIntervalSinceDate:lastInit];
        if (interval > kTimeToReinit) {
            //Reinit the API, using the previous configuration
            [[Insiteo sharedInstance] initializeWithInitializeHandler:nil
                                                 andChooseSiteHandler:nil];
        }
    }
    ...
}
```

## Where to go from there?

- [Compute your first itinerary](itinerary.md).
- [Setup your first geofencing zone](geofence.md).
- [Enable analytics](analytics.md).

## You missed a thing?

- [Project setup](../README.md).
- [Display your first map](map.md).
- [Get your first location](location.md).