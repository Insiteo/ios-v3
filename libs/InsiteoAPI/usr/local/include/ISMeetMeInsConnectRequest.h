//
//  ISMeetMeInsConnectRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeInsConnectRequest.h
 ISMeetMeInsConnectRequest
 */

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeInsConnectRequest
 */
@interface ISMeetMeInsConnectRequest : ISAbstractMeetMeRequest

@property (retain) NSString * login;

@property (retain) NSString * password;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andLogin:(NSString *)aLogin andPassword:(NSString *)aPassword;

@end
