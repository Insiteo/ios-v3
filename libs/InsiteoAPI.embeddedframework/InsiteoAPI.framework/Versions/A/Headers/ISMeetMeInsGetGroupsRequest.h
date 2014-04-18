//
//  ISMeetMeInsGetGroupsRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsGetGroupsRequest.h
 ISMeetMeInsGetGroupsRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsGetGroupsRequest
 */
@interface ISMeetMeInsGetGroupsRequest : ISAbstractMeetMeRequest

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener;

@end
