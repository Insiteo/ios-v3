//
//  ISMeetMeExtConnectRequest.h
//  LocationAPI
//
//  Created by INSITEO on 19/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISMeetMeExtConnectRequest.h
 ISMeetMeExtConnectRequest
 */

#import <Foundation/Foundation.h>

#import "ISAbstractMeetMeRequest.h"

/*!
 ISMeetMeExtConnectRequest
 */
@interface ISMeetMeExtConnectRequest : ISAbstractMeetMeRequest

@property (retain) NSString * userExtID;
@property (retain) NSString * userName;
@property (retain) NSArray * groupExtIDs;

- (id)initWithProvider:(ISMeetMeProvider *)aProvider andListener:(id<ISPMeetMeRequestListener>)aListener andUserExtID:(NSString *)aUserExtID andUserName:(NSString *)aUserName andGroupExtIDs:(NSArray *)aGroupExtIDs;

@end
