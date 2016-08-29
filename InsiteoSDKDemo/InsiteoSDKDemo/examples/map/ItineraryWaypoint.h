//
//  ItineraryWaypoint.h
//  InsiteoSDKDemo
//
//  Copyright (c) 2015-present Insiteo. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <InsiteoSDK/ISGenericRTO.h>

@interface ItineraryWaypoint : ISGenericRTO

- (instancetype)initWithPosition:(ISPosition *)position andName:(NSString *)name;

@end
