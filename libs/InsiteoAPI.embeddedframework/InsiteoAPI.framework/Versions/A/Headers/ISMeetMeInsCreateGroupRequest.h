//
//  ISMeetMeInsCreateGroupRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsCreateGroupRequest.h
 ISMeetMeInsCreateGroupRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsCreateGroupRequest
 */
@interface ISMeetMeInsCreateGroupRequest : ISAbstractMeetMeRequest

@property (retain) NSString * groupName;
@property (retain) NSString * groupPassword;
@property (readwrite) NSTimeInterval endDate;
@property (readwrite) NSTimeInterval closeDate;
@property (readwrite) Boolean isExclusive;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupName:(NSString *)aGroupName andGroupPassword:(NSString *)aGroupPassword andEndDate:(NSTimeInterval)aEndDate andCloseDate:(NSTimeInterval)aCloseDate andExclu:(Boolean)aExclu;

@end
