# Beacons detection

## Requirements

- **Don't forget to create your regions on the back office** If you intend to use this service you have to make sure that your beacon regions have been properly created on the back office.

- **Only supported on iOS 7.0 or higher** This service is only supported in iOS 7.0 or higher.

- **iOS 8 and above compatibility** In order to be fully compatible with iOS 8 and above, you will need to add the `NSLocationAlwaysUsageDescription` in your `.plist`. You can leave the corresponding value empty or specify a custom message that will be displayed the first time the SDK will ask to use the location service.
- Successful SDK initialization and Site started (see [Getting Started Guide](../README.md)).


## 1. Start Beacon Regions Detection

In order to start beacon regions detection, you will need to work with the [`ISBeaconProvider`](http://dev.insiteo.com/api/doc/ios/3.5/Classes/ISBeaconProvider.html) class and call the start methode as soon as possible to be awaken and let the SDK the possibility to execute default behaviors in background.

> **Note:** We highly recommend to start the provider in the `application:didFinishLaunchingWithOptions:` method of your `AppDelegate` in order to be started when the application is launched.

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Start Beacon management
    [[ISBeaconProvider sharedInstance] startWithDelegate:self];
}
```

To be notified on region entry, on region exit, when a region is ranging beacons or if a specific beacon proximity (immediate/near/far) has been detected, you can set a [`ISBeaconDelegate`](http://dev.insiteo.com/api/doc/ios/3.5/Protocols/ISBeaconDelegate.html) when you start the provider or set it later through its [delegate](http://dev.insiteo.com/api/doc/ios/3.5/Classes/ISBeaconProvider.html#//api/name/delegate) property.

> **Note:** Beacon regions are represented by the [`ISBeaconRegion`](http://dev.insiteo.com/api/doc/ios/3.5/Classes/ISBeaconRegion.html) class and physical beacons by the [`ISBeacon`](http://dev.insiteo.com/api/doc/ios/3.5/Classes/ISBeaconRegion.html) class.
 
### Get ranged beacons for a region

When a user enters in a beacon region, the beacon provider starts ranging beacons for that specific region. In order to retrieve beacons ranging information, you should implement the [`rangedBeacons:andReachedProximityBeacons:inRegion:andUnknownCLBeacons:withError:`](http://dev.insiteo.com/api/doc/ios/3.5/Protocols/ISBeaconDelegate.html#//api/name/rangedBeacons:andReachedProximityBeacons:inRegion:andUnknownCLBeacons:withError:) method, which provides all ranged beacons (created on the back office or unknown but detected by the OS), and all beacons which have reached the `proximity` of the beacon region.


### Stop beacon management

Simply call the `ISBeaconProvider` stop method:

```objective-c
// Stop Beacon management
[[ISBeaconProvider sharedInstance] stop];
```

> **Warning:** Stopping the beacon provider will stop all beacon regions detection and your application **will not be waken in background**, unless you call the start method again.

## 2. Present a Notification on Region Entry

By default, if the message property a region exists and is not empty, a `UILocalNotification` will be presented to the user on region entry.

All region information will be stored into a `NSDictionary` using `ISBeaconRegionKeys` and set in the `userInfo` of the local notification (this can be useful to retrieve dynamically which region had send the notification and which message was displayed for example):

```objective-c
// User has clicked or swipped the notification
- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    // Get beacon region information
    NSDictionary *beaconRegionsKeys = [notification.userInfo objectForKey:ISBeaconRegionKeys];
    if (beaconRegionsKeys) {
    	// Then retrieve desired information using other specific keys provided by the ISBeaconProvider
    	// (ex: ISBeaconRegionUUIDKey, ISBeaconRegionMajorKey, ISBeaconRegionMinorKey, etc.)
    }
}
```

You can override the presentation of the `UILocalNotification` or tell the beacon provider to not send the notification by implementing the [`shouldPresentLocalNotificationOnBeaconRegionEntry:`](http://dev.insiteo.com/api/doc/ios/3.5/Protocols/ISBeaconDelegate.html#//api/name/shouldPresentLocalNotificationOnBeaconRegionEntry:) method.

To disable the `UILocalNotification` presentation for all beacon regions just return `NO`. Then, if you only want to disable the notification for a specific region, return `NO` for that specific one and `YES` for the others. Finally, if you want to display by yourself the notification, implement your code then return `NO`:

```objective-c
- (BOOL)shouldPresentLocalNotificationOnBeaconRegionEntry:(ISBeaconRegion *)beaconRegion {
    // First case, disable notification for each Beacon Region
    return NO;

    // Second case, only disable for a specific Beacon Region (ex: customId == @"no-notif")
    if ([beaconRegion.customId isEqualToString:@"no-notif"]) {
        return NO;
    } else {
        return YES;
    }

    // Third case, disable notification and present a UILocalNotification on your own
    UILocalNotification *notification = [[UILocalNotification alloc] init];
    notification.alertBody = @"My custom message";
    [[UIApplication sharedApplication] presentLocalNotificationNow:notification];

    return NO;
}
```

### Delayed the notification presentation on entry

You can specify a delay to schedule the default notification on region entry (which will be cancelled on region exit) using the `Custom` field on the back office. The field should be a valid `JSON string` like: `{"delay": 15}` (present notification after 15 seconds).


## 3. Update Beacon Configuration Periodically

As your beacon regions may have changed since your application was killed, the beacon provider will automatically check on the back office, if the region is always available or if its notification message has changed, before sending the notification on region entry.

> **Note:** If data network connections are not available, the last known configuration will be used.

If you attempt to force SDK initialization on application wake up, you could for example implements the code snippet below into your `AppDelegate`:

```objective-c
#define kTimeToReinit 3600 //ex: every 1 hour, beacon regions are updated on the back office

- (void)applicationDidBecomeActive:(UIApplication *)application {
    ...
    // Check if user is authenticated
    if ([[Insiteo sharedInstance] isAuthenticated]) {
        // Get last API initialization date
        NSDate *lastInit = [Insiteo currentUser].lastInitializationDate;
        // Check the interval between now
        double interval = [[NSDate date] timeIntervalSinceDate:lastInit];
        if (interval > kTimeToReinit) {
            // Reinit the API, using the previous configuration
            [[Insiteo sharedInstance] initializeWithInitializeHandler:nil
                                                 andChooseSiteHandler:nil];
        }
    }
    ...
}
```


## Where To Go From Here?

- Map rendering:
	- [Display your first map](map.md).
	- [Add graphical objects on map](map.md#2-add-graphical-objects-on-map)
- Location:
	- [Get your first location](location.md).
	- [Setup your first geofencing zone](geofence.md).
	- [Room counting with iBeacons](room_counting.md).
- Itinerary:
	- [Compute your first itinerary](itinerary.md).
- Analytics tracking events:
	- [Track Custom Events](analytics.md).