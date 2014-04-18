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
@interface ISMeetMeRenderer : NSObject <ISPRenderer> {
    
@private
    
#pragma mark - General
    
    //Renderer priority
	int m_priority;
    //Current displayed map
    id<ISPMapData> m_currentMap;
    
    
#pragma mark - Rendering
    
	//Boolean used to know if the rendering is activated
	Boolean m_displayEnabled;
    
#pragma mark - Touch
    
	//Boolean used to know if the renderer handle touch events
	Boolean m_touchEnabled;
	//Touch person listeners
	id<ISPRTOListener> m_touchMeetMeListener;
    
#pragma mark - Specific
    
    //Current persons to render
	NSMutableDictionary * m_persons;
    //Persons mutex
    NSLock * m_personsLock;
    
    ISERenderMode m_renderMode;
}

/*!
 Map view layer.
 */
@property (assign) ISLayer * layer;

/*!
 Method used to update displayed ISGfxPersons.
 @param persons Array of persons that need to be updated.
 */
- (void)updatePersons:(NSMutableDictionary *)persons;

@end
