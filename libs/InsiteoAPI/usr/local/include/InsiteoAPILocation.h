//
//  InsiteoAPI.h
//  APICompilator
//
//  Created by Baptiste LE GUELVOUIT on 04/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "InsiteoAPI.h"

#pragma mark - Common

#import "ISMapSettings.h"
#import "ISPLbsModule.h"

#pragma mark - Location

#import "ISLocationProvider.h"
#import "ISPLocationListener.h"
#import "ISLocation.h"
#import "ISPMotionListener.h"

#pragma mark - iBeacon

#import "ISBeaconProvider.h"
#import "ISPBeaconListener.h"
#import "ISBeaconRegion.h"

#pragma mark - Itinerary

#import "ISItineraryProvider.h"
#import "ISItineraryBaseRequest.h"
#import "ISItineraryOptimizedRequest.h"
#import "ISItineraryRequest.h"
#import "ISItinerary.h"
#import "ISItinerarySection.h"
#import "ISItineraryInstruction.h"
#import "ISPItineraryRenderListener.h"
#import "ISPItineraryRequestListener.h"

#pragma mark - Geofence

#import "ISPGeofenceListener.h"
#import "ISGeofenceProvider.h"
#import "ISGeofenceArea.h"

#pragma mark - MeetMe

#import "ISMeetMeProvider.h"
#import "ISPMeetMeListener.h"
#import "ISMeetMePerson.h"
#import "ISAbstractMeetMeRequest.h"
#import "ISPMeetMeRequestListener.h"
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
