//
//  MyRTO.m
//  InsiteoSDKDemo
//
//  Created by Lionel on 08/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import "MyRTO.h"

@interface MyRTO () {
    //Custom pin marker
    CCSprite * m_pinMarker;
}

@end

@implementation MyRTO

- (id)initWithLabel:(NSString *)label  {
    self = [super initWithName:nil andLabel:label andMetersPosition:nil andWindowInitiallyDisplayed:NO andWindowShouldToggle:NO andLabelInitiallyDisplayed:YES andLabelShouldToggle:NO];
    if (self) {

    }
    return self;
}

#pragma mark - Inheritance override

- (void)setResources {
    [super setResources];
    
    //Add new marker into rto node
    m_pinMarker = [[CCSprite alloc] initWithFile:[[NSBundle mainBundle] pathForResource:@"pin" ofType:@"png"]];
    [m_pinMarker setPosition:ccp(0.0, 20.0)];
    [self.rtoNode addChild:m_pinMarker];
}

@end
