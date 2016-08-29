//
//  ItineraryWaypoint.m
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-present Insiteo. All rights reserved.
//

#import "ItineraryWaypoint.h"

@interface ItineraryWaypoint () {
    // Custom pin marker
    CCSprite *_pinMarker;
}

@end

@implementation ItineraryWaypoint

- (instancetype)initWithPosition:(ISPosition *)position andName:(NSString *)name {
    self = [super initWithName:nil
                      andLabel:name
             andMetersPosition:position
   andWindowInitiallyDisplayed:NO
         andWindowShouldToggle:NO
    andLabelInitiallyDisplayed:YES
          andLabelShouldToggle:NO];
    if (self) {
        // Set draggable
        self.draggable = YES;
    }
    return self;
}

#pragma mark - Inheritance override

- (void)setResources {
    [super setResources];
    
    // Add new marker into rto node (check that you image is in the bundle or it will crash !)
    _pinMarker = [[CCSprite alloc] initWithFile:[[NSBundle mainBundle] pathForResource:@"flag" ofType:@"png"]];
    [_pinMarker setPosition:ccp(0.0, 28.0)];
    [self.rtoNode addChild:_pinMarker];
}

@end
