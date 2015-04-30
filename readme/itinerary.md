## Itinerary

> **Packages dependencies** If you intend to use the this service you have to make sure that the `itinerary` package have been properly downloaded. You can easily check if the package is available on the device with the following method: `[[Insiteo currentSite] hasPackage:ISEPackageTypeItinerary]`.

### Enable itinerary rendering

To use location-based services, such as `Itinerary` or `GeoFencing` you have to get the module from the location provider. If you want it to be displayed on an INSITEO map, do as below:

```objectivec++
//Get the itinerary provider
ISGfxItineraryProvider * itineraryProvider = (ISGfxItineraryProvider *)[locProvider getLbsModule:ISEPackageTypeItinerary];

//Get itinerary renderer linked to provider
ISItineraryRenderer * itineraryRenderer = [itineraryProvider renderer];

//Register for itinerary rendering user interaction (such as clicks).
[itineraryRenderer setDelegate:Delegate];

//Add renderer so itinerary is displayed on map
[mapView addRenderer:itineraryRenderer];
```

### Request an itinerary between two points

To compute an itinerary between two points, simply do like this:

```objectivec++
//Request an itinerary between two points (A on map "1", the other on map "2")
ISItineraryRequest * request = [itineraryProvider requestItineraryWithStartPoint:CGPointMake(50, 50) andStartMapId:1 andEndPoint:CGPointMake(200, 100) andEndMapId:2 andDelegate:itineraryDelegate andPMR:NO];
```

> **Note:** An [`ISItineraryRequest`](http://dev.insiteo.com/api/doc/ios/Classes/ISItineraryRequest.html) is returned in order to identify sender through callbacks.

### Request an itinerary from user location

To compute an itinerary from the user location, please do like this:

```objectivec++
//Request an itinerary from the user location to a point A
ISItineraryRequest * request = [itineraryProvider requestItineraryFromCurrentLocationWithEndPoint:CGPointMake(200, 100) andEndMapId:2 andDelegate:itineraryDelegate andPMR:NO];
```

### Request an optimized route

If you want to compute an optimized route between several points, you can proceed as follow:

```objectivec++
//Request an optimized route between several waypoints (an ISItineraryOptimizedRequest is returned)
ISItineraryOptimizedRequest * optimizedRequest = [itineraryProvider requestOptimizedItineraryWithWaypoints:waypoints andOptimMode:ISEOptimizationModeNearestNeighbourShortestPath andKeepFirstPosition:YES andKeepLastPosition:NO andDelegate:itineraryDelegate andPMR:NO];
```

> **Note:** You can specify if you want to keep the first position, last position, or both.

> **Note:** There are multiple optimization modes available but we highly recommend to keep `ISEOptimizationModeNearestNeighbourShortestPath` as the default one.

### Recomputation

When using the itinerary service along with the location you can refresh the route according to the user's position in the following way:

```objectivec++
//Method called when the user position changed
- (void)onItineraryChangedWithRequest:(ISItineraryBaseRequest *)request andDistanceToItinerary:(float)distanceToItinerary {
    //You can check if the distance between the user location and the computed itineray needs a recomputation
    if (distanceToItinerary > MAX_RECOMPUTATION_DISTANCE) {
        //Recompute the itinerary
        [request recompute];
    }
}
```

> **Note:** We usually use `10.0` meters as `MAX_RECOMPUTATION_DISTANCE`.

## Where to go from there?

- [Setup your first geofencing zone](geofence.md).
- [Enable analytics](analytics.md).

## You missed a thing?

- [Project setup](../README.md).
- [Display your first map](map.md).
- [Get your first location](location.md).
- [Configure your iBeacons](beacon.md).
