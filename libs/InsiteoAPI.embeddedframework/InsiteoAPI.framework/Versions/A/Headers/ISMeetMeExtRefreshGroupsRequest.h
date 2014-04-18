//
//  ISMeetMeExtRefreshGroupsRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeExtRefreshGroupsRequest.h
 ISMeetMeExtRefreshGroupsRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeExtRefreshGroupsRequest
 */
@interface ISMeetMeExtRefreshGroupsRequest : ISAbstractMeetMeRequest

@property (retain) NSArray * groupExtIDs;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId andGroupExtIDs:(NSArray *)aGroupExtIDs;


@end
