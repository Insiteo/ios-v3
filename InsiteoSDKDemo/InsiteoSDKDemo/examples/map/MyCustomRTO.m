//
//  MyCustomRTO.m
//  InsiteoSDKDemo
//
//  Copyright © 2015-present Insiteo. All rights reserved.
//

#import "MyCustomRTO.h"

@implementation MyCustomRTO

#pragma mark - Initialization

- (instancetype)initWithPosition:(ISPosition *)position andZoomLevel:(NSInteger)zoomLevel {
    // Get your images path
    NSString *markerPath = [[NSBundle mainBundle] pathForResource:@"marker-toilet" ofType:@"png"];
    NSString *favPath = [[NSBundle mainBundle] pathForResource:@"favorite" ofType:@"png"];
    
    // Use the full constructor to pass as many parameters as you want
    self = [super initWithName:@"Women & Men Toilets"
                      andLabel:nil
             andMetersPosition:position
   andWindowInitiallyDisplayed:NO
         andWindowShouldToggle:YES
    andLabelInitiallyDisplayed:NO
          andLabelShouldToggle:NO
andWindowBackgroundColorNormal:[UIColor colorWithRed:0.9 green:0.9 blue:0.9 alpha:1]
andWindowBackgroundColorHighlighted:nil
              andActionEnabled:YES
            andActionImagePath:favPath
andActionBackgroundColorNormal:[UIColor colorWithRed:0.2 green:0.48 blue:1 alpha:1]
andActionBackgroundColorHighlighted:[UIColor colorWithRed:0.25 green:0.52 blue:1 alpha:1]
           andIndicatorVisible:YES
         andIndicatorImagePath:nil
      andWindowAnchorImagePath:nil
            andMarkerImagePath:markerPath];
    if (self) {
        _zoomLevel = zoomLevel;
    }
    return self;
}

#pragma mark - Override ISGenericRTO methods

// This method is called when a RTO is clicked, by default it returns `YES` so you can override or
// add specific feature
- (Boolean)shouldToggleWindowOnMarkerClicked {
    // For example, we will specified that this clicked RTO should be drawn on top of the other
    // so I change its z-order to 0.
    self.zOrder = 0; // Will be drawn on top
    return YES;
}

// This is in this method that all customization should be done, in order to be called only once
- (void)setResources {
    // Call super in order to initialize properly each default resources
    [super setResources];
    
    // Then do your customization here...
    
    // Adjust window positions to be as you want (according to your marker image size)
    CGPoint windowPosition = self.rtoNode.annotationLayerColor.position;
    [self.rtoNode.annotationLayerColor setPosition:CGPointMake(windowPosition.x, windowPosition.y + 8)];
    
    CGPoint anchorPosition = self.rtoNode.windowAnchorSprite.position;
    [self.rtoNode.windowAnchorSprite setPosition:CGPointMake(anchorPosition.x, anchorPosition.y + 8)];
    
    CGPoint actionBGPosition = self.rtoNode.actionBackgroundSprite.position;
    [self.rtoNode.actionBackgroundSprite setPosition:CGPointMake(actionBGPosition.x, actionBGPosition.y + 8)];
    
    CGPoint indicatorBGPosition = self.rtoNode.indicatorBackgroundSprite.position;
    [self.rtoNode.indicatorBackgroundSprite setPosition:CGPointMake(indicatorBGPosition.x, indicatorBGPosition.y + 8)];
    
    // Name
    CGPoint namePosition = self.rtoNode.descriptionName.position;
    [self.rtoNode.descriptionName setPosition:CGPointMake(namePosition.x, namePosition.y + 8)];
    [self.rtoNode.descriptionName setFontName:[UIFont systemFontOfSize:18 weight:UIFontWeightThin].fontName]; // Change the font
    [self.rtoNode.descriptionName setFontSize:18]; // New font size
    
    // Label
    CGPoint labelPosition = self.rtoNode.descriptionLabel.position;
    [self.rtoNode.descriptionLabel setPosition:CGPointMake(labelPosition.x, labelPosition.y - 10)];
    [self.rtoNode.descriptionLabel setFontName:[UIFont systemFontOfSize:14 weight:UIFontWeightMedium].fontName];
    [self.rtoNode.descriptionLabel setFontSize:14];
    [self.rtoNode.descriptionLabel setColor:ccc3(51, 123, 255)]; // New text color
    
    // We do not want the default stroke label
    [self.rtoNode.descriptionStrokeLabel removeFromParent];
}

@end
