//
//  ISMeetMeInsJoinGroupRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsJoinGroupRequest.h
 ISMeetMeInsJoinGroupRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsJoinGroupRequest
 */
@interface ISMeetMeInsJoinGroupRequest : ISAbstractMeetMeRequest

@property (readwrite) int groupId;

@property (retain) NSString * groupName;

@property (retain) NSString * groupPassword;

@property (readwrite) Boolean isExclusive;


- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupId:(int)aGroupId andGroupName:(NSString *)aGroupName andGroupPassword:(NSString *)aGroupPassword andExclu:(Boolean)aExclu;

@end
