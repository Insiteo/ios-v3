//
//  ISGenericRTO.h
//  InsiteoAPI
//
//  Created by dev_iphone on 16/04/14.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISGenericRTO.h
 ISGenericRTO
 */

#import <Foundation/Foundation.h>

//Intern const used to scroll text
extern int const RTO_LABEL_MAX_LENGTH;

//Intern value used to handle touch move on RTO
extern int const CLICKABLE_RTO_SIZE;

#import "CCNode.h"
#import "ISPRTO.h"
#import "ISPosition.h"
#import "ISGenericRTONode.h"
#import "ISReverseRect.h"

@class CC3Billboard;

/*!
 Class which represent a basic RTO object (name + pin image).
 */
@interface ISGenericRTO : CCNode <ISPRTO> {
    
@protected
    
#pragma mark - Attributes
    
    //RTO position in meters
    ISPosition * m_metersPosition;
    //Displayed name
    NSString * m_name;
    NSString * m_label;
        
#pragma mark - Rendering
    
    //RTO unique identifier (Map rendering)
    int m_rtoId;
    
    ISGenericRTONode * m_rtoNode;
    
    //Internal boolean use to know if the textBox is hidden or not
    Boolean m_windowDisplayed;
    //Last angle
    float m_lastAngle;
    CGPoint m_currentOffset;
    float m_currentRatio;
    ISMap * m_currentMap;
    
#pragma mark - Touch
    
    //Boolean used to know if the RTO is draggable
    Boolean m_draggable;
    //Internal point used to handle touch events
	CGPoint m_referencePoint;
    //Boolean used to know if its pin was touched
	Boolean m_markerTouched;
    //Boolean used to know if the icon was touched
    Boolean m_actionButtonTouched;
    //Boolean used to know if its textbox was touched
	Boolean m_annotationTouched;
    //Boolean used to know if the icon is clicked
    Boolean m_actionButtonClicked;
    
#pragma mark - 3D
    
    //Zone offset to apply (if needed)
    CC3Vector m_zoneOffset;
    //Current render mode
    ISERenderMode m_renderMode;
    //3D main rendering node
    CC3Node * m_cocos3dNode;
    //3D billboard (for 3D rendering only)
    CC3Billboard * m_billboard;
    //Current 3D scene (for 3D rendering only)
    CC3Scene * m_currentScene;
    //Related Zone/Poi association (could be nil)
    ISZonePoi * m_zonePoi;
    
#pragma mark - ISGenericRTONode
    
    //Annotation
    UIColor * m_windowBackgroundColorNormal;
    UIColor * m_windowBackgroundColorHighlighted;
    
    //Action
    NSString * m_actionImagePath;
    UIColor * m_actionBackgroundColorNormal;
    UIColor * m_actionBackgroundColorHighlighted;
    
    //Indicator
    NSString * m_indicatorImagePath;
    
    //Anchor
    NSString * m_windowAnchorImagePath;
    
    //Marker
    NSString * m_markerImagePath;
}

/*!
 RTO position in meters.
 */
@property (nonatomic, retain) ISPosition * metersPosition;

/*!
 Current rendering map.
 */
@property (nonatomic, retain) ISMap * currentMap;

/*!
 Boolean used to know if the RTO is draggable.
 */
@property (nonatomic, readwrite) Boolean draggable;

/*!
 Boolean used to know if the action button was clicked.
 */
@property (nonatomic, readonly) Boolean actionButtonClicked;

/*!
 Related 2D render node.
 */
@property (nonatomic, retain) ISGenericRTONode * rtoNode;

/*!
 Current 3D scene (for 3D rendering only).
 */
@property (nonatomic, assign) CC3Scene * currentScene;

#pragma mark - ISGenericRTONode

/*!
 RTO window background color for normal state.
 */
@property (nonatomic, retain) UIColor * windowBackgroundColorNormal;

/*!
 RTO window background color for highlighted state.
 */
@property (nonatomic, retain) UIColor * windowBackgroundColorHighlighted;

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
 RTO indicator sprite image path.
 */
@property (nonatomic, retain) NSString * indicatorImagePath;

/*!
 RTO window anchor sprite image path.
 */
@property (nonatomic, retain) NSString * windowAnchorImagePath;

/*!
 RTO marker sprite image path.
 */
@property (nonatomic, retain) NSString * markerImagePath;

/*!
 Main constructor
 @param name RTO displayed name.
 @param label RTO displayed label.
 @param metersPosition RTO position in meters (could be nil in case of zone rendering).
 @param windowDisplayed Boolean used to know if the RTO window has to be displayed.
 @param labelDisplayed Boolean used to know if the RTO label has to be displayed.
 */
- (id)initWithName:(NSString *)name andLabel:(NSString *)label andMetersPosition:(ISPosition *)metersPosition andWindowDisplayed:(Boolean)windowDisplayed andLabelDisplayed:(Boolean)labelDisplayed;

- (id)initWithName:(NSString *)name andLabel:(NSString *)label andMetersPosition:(ISPosition *)metersPosition andWindowDisplayed:(Boolean)windowDisplayed andLabelDisplayed:(Boolean)labelDisplayed andWindowBackgroundColorNormal:(UIColor *)windowBackgroundColorNormal andWindowBackgroundColorHighlighted:(UIColor *)windowBackgroundColorHighlighted andActionImagePath:(NSString *)actionImagePath andActionBackgroundColorNormal:(UIColor *)actionBackgroundColorNormal andActionBackgroundColorHighlighted:(UIColor *)actionBackgroundColorHighlighted andIndicatorImagePath:(NSString *)indicatorImagePath andWindowAnchorImagePath:(NSString *)windowAnchorImagePath andMarkerImagePath:(NSString *)markerImagePath;

/*!
 Method used to set the RTO label as displayed or not.
 @param displayed Boolean used to set the label display state.
 */
- (void)setLabelDisplayed:(Boolean)displayed;

/*!
 Method used to knwo if the RTO toggle its window when the marker was clicked.
 @return <b>YES</b> if you want a toggle action, otherwise <b>NO</b>.
 */
- (Boolean)shouldToggleWindowOnMarkerClicked;

/*!
 Method called to hide the window.
 */
- (void)hideWindow;

/*!
 Method called to show the window.
 */
- (void)showWindow;

/*!
 Method called to toggle RTO appearance.
 */
- (void)toggleWindow;

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

@end
