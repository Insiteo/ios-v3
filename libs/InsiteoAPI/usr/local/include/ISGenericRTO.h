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

/*!
 Class which represent a basi RTO object (name + pin image).
 */
@interface ISGenericRTO : CCNode <ISPRTO> {
    
@protected
    
#pragma mark - Attributes
    
    //Related map identifier
    ISPosition * m_position;
    //Displayed name
    NSString * m_name;
        
#pragma mark - Rendering
    
    //RTO unique identifier (Map rendering)
    int m_rtoId;
    //RTO pin image
    CCSprite * m_pinImage;
    //RTO textbox image
    CCSprite * m_textBoxImage;
    //RTO name label
    CCLabelTTF * m_label;
    //Internal boolean use to know if the textBox is hidden or not
    Boolean m_textBoxHide;
    //Last angle
    float m_lastAngle;
    
#pragma mark - Scrolling Text
    
    //Scrolling text value
    int m_scrollingTextValue;
    //RTO label default size
    CGSize m_labelSize;
    //Intern scroll count variable
    int m_scrollCount;
    
#pragma mark - Touch
    
    //Boolean used to know if its textbox was touched
	Boolean m_textBoxTouched;
    //Boolean used to know if its pin was touched
	Boolean m_pinTouched;
    //Internal point used to handle touch events
	CGPoint m_referencePoint;
    
    //Zone offset to apply (if needed)
    CC3Vector m_zoneOffset;
    //Current render mode
    ISERenderMode m_renderMode;
    //Related zone identifier (if needed)
    int m_zoneId;
}

/*!
 Main constructor
 @param name RTO displayed label.
 @param position RTO position in meters (could be nil in case of zone rendering).
 */
- (id)initWithName:(NSString *)name andPosition:(ISPosition *)position;

/*!
 Method called to hide the annotation.
 */
- (void)hideTextBox;

/*!
 Method called to show the annotation.
 */
- (void)showTextBox;

/*!
 Method called to toggle RTO appearance.
 */
- (void)showHide;

/*!
 Method called to render the annotation as touched or not.
 @param over <b>YES</b> if you want a touched effect, otherwise <b>NO</b>.
 */
- (void)setOver:(Boolean)over;

@end
