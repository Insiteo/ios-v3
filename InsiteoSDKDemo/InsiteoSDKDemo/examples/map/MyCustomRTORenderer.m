//
//  MyCustomRTORenderer.m
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import "MyCustomRTORenderer.h"

#import "MyCustomRTO.h"

@implementation MyCustomRTORenderer

#pragma mark - Override 2D

// For example this renderer will render `MyCustomRTO` objects only at a specific zoom level
- (void)render2DWithLayer:(CCLayer *)layer andRatio:(double)ratio andOffset:(CGPoint)offset andAngle:(float)angle {
    [super render2DWithLayer:layer andRatio:ratio andOffset:offset andAngle:angle];
    
    // Current zoom level
    float currentZoomLevel = log(ratio * self.currentMap.scale) / log(2);
    
    // Get rtos
    NSArray *rtos = [self getRTOsWithZoneId:-1];
    
    for (MyCustomRTO *rto in rtos) {
        // Check
        BOOL checkZoomLevel = (rto.zoomLevel <= currentZoomLevel);
        if (checkZoomLevel && self.currentMap.mapId == rto.mapId) {
            // Visible
            rto.hidden = NO;
            [rto render2DWithLayer:layer andRatio:ratio andOffset:offset andAngle:angle andPriority:self.priority];
        } else {
            // Hidden
            rto.hidden = YES;
            [rto remove2DFromLayer:layer];
        }
    }
}

@end
