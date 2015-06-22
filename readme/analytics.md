## Analytics

### Starting the Analytics service

In order to use the analytics service you have to make sure it gets started during the API initialization. If you did not specify the analytics behavior in the API initialization method the service will be started automatically if the packages depedencies prerequisite is met. Otherwise this will depends on the value passed as the analyticsAutoStart as true will try to start it and false will keep it turned off and no data will be stored during the session.

### Location events

If you have decided to use the analytics service then the user's location will be automatically sent for datamining analysis. In order to avoid internet requests overload location will be aggregated according to a given frequency that can be set in the back office.

### Generic events

For any other type of events you would like to keep track of you can use the [`ISAnalyticsGenericEvent`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISAnalyticsGenericEvent.html). This event enables you to add up to 2 NSString, 2 int, 2 double, 2 [`ISPosition`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISPosition.html) and a label to match most cases.

Adding a [`ISAnalyticsGenericEvent`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISAnalyticsGenericEvent.html) to the [`ISAnalyticsManager`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISAnalyticsManager.html).

```objectivec++
ISAnalyticsGenericEvent * zoneEvent = [[ISAnalyticsGenericEvent alloc] initWithEventType:@"generic_event"];

[zoneEvent setSParam1:@"product a"];
[zoneEvent setPositions:[NSArray arrayWithObject:aLocation.position]];

[[ISAnalyticsManager instance] addGenericEvent:zoneEvent];
```

Insiteo's API already trace some basic events among them:
- Location start and stop
- Geofence entered, stayed and left
- Map changes, zone clicks and [`ISRTO`](http://dev.insiteo.com/api/doc/ios/Protocols/ISRTO.html) added with [`ISZonePoi`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISZonePoi.html)
- Itinerary requests
- iBeacon events

#### Tracking products displayed on map

If you want to trace when a product is added to the map you can use [`addRTO:inZonePoi:`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISMapView.html#//api/name/addRTO:inZonePoi:). This will generate a [`ISAnalyticsGenericEvent`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISAnalyticsGenericEvent.html) with the String1 set with the external id of the Poi defined in the [`ISZonePoi`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISZonePoi.html).

#### Completing a generic event

It can be useful in some cases to add information to a [`ISAnalyticsGenericEvent`](http://dev.insiteo.com/api/doc/ios/3.4/Classes/ISAnalyticsGenericEvent.html) for that you must set a [`ISAnalyticsDelegate`](http://dev.insiteo.com/api/doc/ios/Protocols/ISAnalyticsDelegate.html) that will be notified everytime a new generic event is added. Returning false in this method will dismiss the event.

## You missed a thing?

- [Project setup](../README.md).
- [Display your first map](map.md).
- [Get your first location](location.md).
- [Configure your iBeacons](beacon.md).
- [Compute your first itinerary](itinerary.md).
- [Setup your first geofencing zone](geofence.md).
