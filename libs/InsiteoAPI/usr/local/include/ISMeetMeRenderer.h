//
//  ISMeetMeRenderer.h
//  LocationAPI
//
//  Created by INSITEO on 23/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISMeetMeRenderer.h
 ISMeetMeRenderer
 */

#import <Foundation/Foundation.h>

#import "ISPRenderer.h"

/*!
 Class used to handle ISGfxPerson rendering.
 */
@interface ISMeetMeRenderer : NSObject <ISPRenderer> 

/*!
 Map view layer.
 */
@property (assign) CCLayer * layer;

/*!
 Method used to update displayed ISGfxPersons.
 @param persons Array of persons that need to be updated.
 */
- (void)updatePersons:(NSMutableDictionary *)persons;

@end
