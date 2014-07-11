//
//  ISMeetMeInsCreateUserRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsCreateUserRequest.h
 ISMeetMeInsCreateUserRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsCreateUserRequest
 */
@interface ISMeetMeInsCreateUserRequest : ISAbstractMeetMeRequest

@property (retain) NSString * name;
@property (retain) NSString * login;
@property (retain) NSString * password;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andLogin:(NSString *)aLogin andName:(NSString *)aName andPassword:(NSString *)aPassword ;


@end
