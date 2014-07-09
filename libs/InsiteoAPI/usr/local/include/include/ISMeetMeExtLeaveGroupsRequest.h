//
//  ISMeetMeExtLeaveGroupsRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeExtLeaveGroupsRequest.h
 ISMeetMeExtLeaveGroupsRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeExtLeaveGroupsRequest
 */
@interface ISMeetMeExtLeaveGroupsRequest : ISAbstractMeetMeRequest

@property (retain) NSArray * groupExtIDs;
@property (retain) NSArray * groupIds;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupIds:(NSArray *)aGroupIds andGroupExtIDs:(NSArray *)aGroupExtIDs;


@end
