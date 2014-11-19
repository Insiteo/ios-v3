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

#import "cocos2d.h"

#import "ISPRTO.h"
#import "ISMeetMePerson.h"

/*!
 Class used to render an ISMeetMePerson on the map.
 */
@interface ISGfxMeetMePerson : CCNode <ISPRTO>

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
