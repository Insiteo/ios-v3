//
//  ISMeetMeInsCreateTmpUserRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsCreateTmpUserRequest.h
 ISMeetMeInsCreateTmpUserRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsCreateTmpUserRequest
 */
@interface ISMeetMeInsCreateTmpUserRequest : ISAbstractMeetMeRequest

@property (retain) NSString * name;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserName:(NSString *)aUserName;


@end
