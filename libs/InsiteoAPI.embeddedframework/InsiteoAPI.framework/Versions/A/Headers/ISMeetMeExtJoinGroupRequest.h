//
//  ISMeetMeExtJoinGroupRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeExtJoinGroupRequest.h
 ISMeetMeExtJoinGroupRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeExtJoinGroupRequest
 */
@interface ISMeetMeExtJoinGroupRequest : ISAbstractMeetMeRequest

@property (retain) NSString * groupExtID;
@property (retain) NSString * groupName;
@property (readwrite) NSTimeInterval beginDate;
@property (readwrite) NSTimeInterval endDate;
@property (readwrite) Boolean isExclusive;


- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupExtID:(NSString *)aGroupExtID andGroupName:(NSString *)aGroupName andBeginDate:(NSTimeInterval)aBeginDate andEndDate:(NSTimeInterval)aEndDate andExclu:(Boolean)aExclu;



@end
