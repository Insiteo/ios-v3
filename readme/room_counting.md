## Room Counting

### Pre-requisites

> **Important**: In order to use the room counting feature, your application must enable the  [iBeacon configuration](beacon.md). Also keep in mind that users must have **enabled their bluetooth** on their phone to detect iBeacons. 

Room counting is based on iBeacon location service and Insiteo analytics. You must have intialized the SDK properly at least once with analytics enabled for the system to work (.plist configuration or using initialization parameters). Analytics configuration and iBeacon regions are retrieved from the server and stored in your client configuration.


### Best Practices

The best way to report background location data through Insiteo SDK is to initialize the SDK as soon as possible. Indeed, when your application is woken up from iBeacon service, the OS starts your application for ~10 seconds in the background. The Insiteo class provides a local initialization method `-initializeLocallyWithLastConfiguration` which uses your last known configuration to avoid server synchronization that could take a long time. You don't need to start an Insiteo site.

> **Note:** Such as with standard initialization methods, a full local initialization method with parameters is available.


### Usage

- Start the Beacon Provider as soon as possible in `application:didFinishLaunchingWithOptions:`

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    // Start Beacon Provider with nil or delegate.
    [[ISBeaconProvider sharedInstance] startWithDelegate:nil];
    ...
    return YES;
}
```

- Detect if the application is woken up from location service (in the background):

```objective-c
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    // Typically from iBeacon region entry/exit (the application is launched in the background)
    // You can store it in AppDelegate or elsewhere to retrieve the value later.
    BOOL isWokenUpFromLocation = [launchOptions objectForKey:UIApplicationLaunchOptionsLocationKey] != nil);
    ...
    return YES;
}
```

- According to `launchOptions` you can either choose to initialize the SDK locally or remotely:

```objective-c
- (void)viewDidLoad {
    [super viewDidLoad];
    
    ...
    
    BOOL localInit = NO;
    BOOL wasLaunchFromBG = YES; // Check launch options
    
    // Launch from BG ? => local init
    if (wasLaunchFromBG) {
    	// If an error occured, it seems you never have synchronized the SDK with the server
        ISError *error = [[Insiteo sharedInstance] initializeLocallyWithLastConfiguration];
        localInit = (error == nil);
    }
    
    if (!localInit) {   
    	// If local init failed, try the standard way (remotely)
        [[Insiteo sharedInstance] initializeWithInitializeHandler:^(ISError *error, ISUserSite *suggestedSite, Boolean fromLocalCache) {
            if (error) {
                // Init error...
            } else {
				// Init succeed, do you stuff !
            }
        } andChooseSiteHandler:nil];
        
    } else {
        // Local init succeed, you can do your stuff !
    }
    
    ...
}
```



## Missing something?

- [Project setup](../README.md).
- [Configure your iBeacons](beacon.md).

