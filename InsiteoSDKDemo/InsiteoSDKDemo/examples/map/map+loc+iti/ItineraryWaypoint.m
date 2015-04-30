//
//  ItineraryWaypoint.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 10/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "ItineraryWaypoint.h"

@implementation ItineraryWaypoint

- (id)initWithPosition:(ISPosition *)position andName:(NSString *)name {
    self = [super initWithName:name andLabel:nil andMetersPosition:position andWindowInitiallyDisplayed:YES andWindowShouldToggle:NO andLabelInitiallyDisplayed:NO andLabelShouldToggle:NO];
    if (self) {
        [self setDraggable:YES];
    }
    return self;
}

@end
