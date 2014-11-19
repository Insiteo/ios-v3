//
//  ISMeetMeInsLeaveGroupsRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsLeaveGroupsRequest.h
 ISMeetMeInsLeaveGroupsRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsLeaveGroupsRequest
 */
@interface ISMeetMeInsLeaveGroupsRequest : ISAbstractMeetMeRequest

@property (retain) NSArray * groupIds;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupIds:(NSArray *)aGroupIds;

@end
