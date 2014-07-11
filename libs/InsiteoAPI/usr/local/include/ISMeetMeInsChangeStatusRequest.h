//
//  ISMeetMeInsChangeStatusRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsChangeStatusRequest.h
 ISMeetMeInsChangeStatusRequest
 */

#import "ISAbstractMeetMeRequest.h"
#import "ISMeetMePerson.h"

/*!
 ISMeetMeInsChangeStatusRequest
 */
@interface ISMeetMeInsChangeStatusRequest : ISAbstractMeetMeRequest

@property (retain) NSArray * changedGroupIds;
@property (readwrite) UserStatus newStatus;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupIds:(NSArray *)aGroupIds andNewStatus:(UserStatus)aNewStatus;

@end
