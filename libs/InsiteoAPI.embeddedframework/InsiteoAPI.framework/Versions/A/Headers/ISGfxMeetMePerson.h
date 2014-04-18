//
//  ISGfxMeetMePerson.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 18/05/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISGfxMeetMePerson.h
 ISGfxMeetMePerson
 */

#import <Foundation/Foundation.h>

#import "ISPRTO.h"
#import "ISMeetMePerson.h"

#import "cocos2d.h"

/*!
 Class used to render an ISMeetMePerson on the map.
 */
@interface ISGfxMeetMePerson : CCNode <ISPRTO> {
    
@private
    
#pragma mark - Structure
    
    //Related person information
    ISMeetMePerson * m_person;
    
#pragma mark - Rendering
    
    //RTO unique identifier
    int m_rtoId;
    //Renderer current ratio
	double m_currentRatio;
	//Renderer current offset
	CGPoint m_currentOffset;
    //Last angle
    float m_lastAngle;
    
    //Picture image
    CCSprite * m_picture;
    //Person textbox image
    CCSprite * m_textBoxImage;
    //Person name label
    CCLabelTTF * m_personLabel;
    //Internal boolean use to know if the textBox is hidden
    Boolean m_textBoxHide;
    
#pragma mark - Touch
    
    //Boolean used to know if its textbox was touched
	Boolean m_textBoxTouched;
    //Internal point used to handle touch events
	CGPoint m_referencePoint;
    //Boolean used to know if its pin was touched
    Boolean m_pinTouched;
    ISERenderMode m_renderMode;
}

/*!
 Main constructor.
 @param person Person used for rendering (position, color, etc...).
 */
- (id)initWithPerson:(ISMeetMePerson *)person;

/*!
 Method called to update related person information.
 @param person Person to update from.
 */
- (void)updatePerson:(ISMeetMePerson *)person;

@end
