//
//  ISGenericRTONode.h
//  lbs
//
//  Created by dev_iphone on 17/07/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISGenericRTONode.h
 ISGenericRTONode
 */

#import "cocos2d.h"

/*!
 Class used to handle cocos2d rendering of an ISGenericRTO.
 */
@interface ISGenericRTONode : CCNode {
    
@private
    
    //Window
    CCNode * m_windowNode;
    
    //Annotation
    UIColor * m_windowBackgroundColorNormal;
    UIColor * m_windowBackgroundColorHighlighted;
    CCLayerColor * m_annotationLayerColor;
    
    //Action
    CCSprite * m_actionBackgroundSprite;
    CCSprite * m_actionSprite;
    
    Boolean m_actionEnabled;
    NSString * m_actionImagePath;
    
    UIColor * m_actionBackgroundColorNormal;
    UIColor * m_actionBackgroundColorHighlighted;
    
    //Indicator
    CCSprite * m_indicatorBackgroundSprite;
    CCSprite * m_indicatorSprite;
    
    Boolean m_indicatorVisible;
    NSString * m_indicatorImagePath;

    //Anchor
    CCSprite * m_windowAnchorSprite;
    
    NSString * m_windowAnchorImagePath;
    
    //Marker
    NSString * m_markerImagePath;
    CCSprite * m_markerSprite;
    
    //Name
    CCLabelTTF * m_descriptionName;
    
    //Description label
    CCLabelTTF * m_descriptionStrokeLabel;
    CCLabelTTF * m_descriptionLabel;
}

/*!
 RTO window cocos2d node.
 */
@property (nonatomic, retain) CCNode * windowNode;

/*!
 RTO window background color for normal state.
 */
@property (nonatomic, retain) UIColor * windowBackgroundColorNormal;

/*!
 RTO window background color for highlighted state.
 */
@property (nonatomic, retain) UIColor * windowBackgroundColorHighlighted;

/*!
 RTO annotation cocos2d layer color.
 */
@property (nonatomic, retain) CCLayerColor * annotationLayerColor;

/*!
 RTO action button background cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * actionBackgroundSprite;

/*!
 RTO action button cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * actionSprite;

/*!
 Boolean used to know if an action is enabled.
 */
@property (nonatomic, readwrite) Boolean actionEnabled;

/*!
 RTO action button sprite image path.
 */
@property (nonatomic, retain) NSString * actionImagePath;

/*!
 RTO action button background color for normal state.
 */
@property (nonatomic, retain) UIColor * actionBackgroundColorNormal;

/*!
 RTO action button background color for highlighted state.
 */
@property (nonatomic, retain) UIColor * actionBackgroundColorHighlighted;

/*!
 RTO indicator background cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * indicatorBackgroundSprite;

/*!
 RTO indicator cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * indicatorSprite;

/*!
 Boolean used to know if an indicator is visible.
 */
@property (nonatomic, readwrite) Boolean indicatorVisible;

/*!
 RTO indicator sprite image path.
 */
@property (nonatomic, retain) NSString * indicatorImagePath;

/*!
 RTO window anchor cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * windowAnchorSprite;

/*!
 RTO window anchor sprite image path.
 */
@property (nonatomic, retain) NSString * windowAnchorImagePath;

/*!
 RTO marker sprite image path.
 */
@property (nonatomic, retain) NSString * markerImagePath;

/*!
 RTO marker cocos2d sprite.
 */
@property (nonatomic, retain) CCSprite * markerSprite;

/*!
 RTO description cocos2d name.
 */
@property (nonatomic, retain) CCLabelTTF * descriptionName;

/*!
 RTO description cocos2d stroke label.
 */
@property (nonatomic, retain) CCLabelTTF * descriptionStrokeLabel;

/*!
 RTO description cocos2d label.
 */
@property (nonatomic, retain) CCLabelTTF * descriptionLabel;

/*!
 Main constructor.
 @param name RTO name.
 @param label RTO label.
 */
- (id)initWithName:(NSString *)name andLabel:(NSString *)label;

- (id)initWithName:(NSString *)name andLabel:(NSString *)label andWindowBackgroundColorNormal:(UIColor *)windowBackgroundColorNormal andWindowBackgroundColorHighlighted:(UIColor *)windowBackgroundColorHighlighted andActionImagePath:(NSString *)actionImagePath andActionBackgroundColorNormal:(UIColor *)actionBackgroundColorNormal andActionBackgroundColorHighlighted:(UIColor *)actionBackgroundColorHighlighted andIndicatorImagePath:(NSString *)indicatorImagePath andWindowAnchorImagePath:(NSString *)windowAnchorImagePath andMarkerImagePath:(NSString *)markerImagePath;

/*!
 Method called to update RTO resources.
 */
- (void)updateResources;

/*!
 Method called to render the annotation as touched or not.
 @param over <b>YES</b> if you want a touched effect, otherwise <b>NO</b>.
 */
- (void)setOver:(Boolean)over;

/*!
 Method called to render the action button as touched or not.
 @param over <b>YES</b> if you want a touched effect, otherwise <b>NO</b>.
 */
- (void)setOverAction:(Boolean)over;

/*!
 Method called to hide the window.
 */
- (Boolean)hideWindow;

/*!
 Method called to show the window.
 */
- (Boolean)showWindow;

/*!
 Method called to toggle RTO appearance.
 */
- (Boolean)toggleWindow;

@end
