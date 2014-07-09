//
//  ExtChangeStatusRequest.h
//  LocationAPI
//
//  Created by INSITEO on 15/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeExtChangeStatusRequest.h
 ISMeetMeExtChangeStatusRequest
 */

#import "ISAbstractMeetMeRequest.h"
#import "ISMeetMePerson.h"

/*!
 ISMeetMeExtChangeStatusRequest
 */
@interface ISMeetMeExtChangeStatusRequest : ISAbstractMeetMeRequest 

@property (readwrite) UserStatus newStatus;
@property (retain) NSArray * changedGroupIds;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupIds:(NSArray *)aGroupIds andNewStatus:(UserStatus)aNewStatus;


@end
