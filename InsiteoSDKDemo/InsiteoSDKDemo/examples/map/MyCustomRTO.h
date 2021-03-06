//
//  MyCustomRTO.h
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import <InsiteoSDK/ISGenericRTO.h>

@interface MyCustomRTO : ISGenericRTO

// Zoom level to be visible on map.
@property (nonatomic, assign, readonly) NSInteger zoomLevel;

// Boolean used to disable interaction when hidden from the renderer
@property (nonatomic, assign, readwrite, getter=isHidden) BOOL hidden;

// Initializes a RTO with a position and a zoom level restriction visibility
- (instancetype)initWithPosition:(ISPosition *)position andZoomLevel:(NSInteger)zoomLevel;

@end
