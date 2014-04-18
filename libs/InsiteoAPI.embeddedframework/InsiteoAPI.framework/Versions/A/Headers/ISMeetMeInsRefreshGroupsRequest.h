//
//  ISMeetMeInsRefreshGroupsRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsRefreshGroupsRequest.h
 ISMeetMeInsRefreshGroupsRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsRefreshGroupsRequest
 */
@interface ISMeetMeInsRefreshGroupsRequest : ISAbstractMeetMeRequest

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserId:(NSString *)aUserId;

@end
