//
//  InsiteoAPI.h
//  APICompilator
//
//  Created by Baptiste LE GUELVOUIT on 04/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "InsiteoAPI.h"

#pragma mark - LocationAPI

#import "ISAbstractMeetMeRequest.h"
#import "ISEmbeddedItineraryProvider.hpp"
#import "ISGeofenceProvider.h"
#import "ISGeofenceZone.h"
#import "ISItineraryProvider.h"
#import "ISItineraryRequest.h"
#import "ISItineraryStructures.h"
#import "ISLocation.h"
#import "ISLocationProvider.hpp"
#import "ISMapSettings.h"
#import "ISMeetMeExtChangeStatusRequest.h"
#import "ISMeetMeExtConnectRequest.h"
#import "ISMeetMeExtJoinGroupRequest.h"
#import "ISMeetMeExtLeaveGroupsRequest.h"
#import "ISMeetMeExtRefreshGroupsRequest.h"
#import "ISMeetMeGroup.h"
#import "ISMeetMeInsChangeStatusRequest.h"
#import "ISMeetMeInsConnectRequest.h"
#import "ISMeetMeInsCreateGroupRequest.h"
#import "ISMeetMeInsCreateTmpUserRequest.h"
#import "ISMeetMeInsCreateUserRequest.h"
#import "ISMeetMeInsGetGroupsRequest.h"
#import "ISMeetMeInsJoinGroupRequest.h"
#import "ISMeetMeInsLeaveGroupsRequest.h"
#import "ISMeetMeInsRefreshGroupsRequest.h"
#import "ISMeetMePerson.h"
#import "ISMeetMeProvider.h"
#import "ISPCompassListener.h"
#import "ISPGeofenceListener.h"
#import "ISPItineraryRenderListener.h"
#import "ISPItineraryRequestListener.h"
#import "ISPLbsModule.h"
#import "ISPLbsModuleRequest.h"
#import "ISPLbsModuleResponse.h"
#import "ISPLocationListener.h"
#import "ISPMeetMeListener.h"
#import "ISPMeetMeRequestListener.h"
#import "ISPMotionListener.h"