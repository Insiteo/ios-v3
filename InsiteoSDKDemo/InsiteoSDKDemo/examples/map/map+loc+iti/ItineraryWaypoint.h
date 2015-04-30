//
//  ItineraryWaypoint.h
//  InsiteoSDKDemo
//
//  Created by Lionel on 10/04/2015.
//  Copyright (c) 2015 Insiteo. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <InsiteoSDK/ISGenericRTO.h>

@interface ItineraryWaypoint : ISGenericRTO

- (id)initWithPosition:(ISPosition *)position andName:(NSString *)name;

@end
