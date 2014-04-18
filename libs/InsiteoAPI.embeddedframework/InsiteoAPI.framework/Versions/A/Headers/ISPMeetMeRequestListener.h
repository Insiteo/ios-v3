//
//  ISMeetMeRequestListener.h
//  LocationAPI
//
//  Created by INSITEO on 03/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPMeetMeRequestListener.h
 ISPMeetMeRequestListener
 */

#import <Foundation/Foundation.h>

@class ISInsiteoError;
@class ISAbstractMeetMeRequest;

/*!
 Procotol used to handle MeetMe request events.
 */
@protocol ISPMeetMeRequestListener <NSObject>

/*!
 Method called when a MeetMe request succeeded.
 @param success Boolean used to know if the request succeeded.
 @param request The related request.
 @param error The related error if success == false.
 */
- (void)onMeetMeRequestDoneWithSuccess:(Boolean)success andRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error;

@end
