//
//  ISGfxMeetMeProvider.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 06/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISGfxMeetMeProvider.h
 ISGfxMeetMeProvider
 */

#import "ISMeetMeProvider.h"

#import "ISMeetMeRenderer.h"

@interface ISGfxMeetMeProvider : ISMeetMeProvider {
    
@private
    
    //ISMeetMeRenderer
    ISMeetMeRenderer * m_renderer;
}

/*!
 MeetMe renderer (used to render ISGfxPerson).
 */
@property (readonly) ISMeetMeRenderer * renderer;

@end
