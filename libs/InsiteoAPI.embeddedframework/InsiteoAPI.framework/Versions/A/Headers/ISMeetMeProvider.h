//
//  ISMeetMeManager.h
//  LocationAPI
//
//  Created by INSITEO on 21/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISMeetMeProvider.h
 ISMeetMeProvider
 */

#import <Foundation/Foundation.h>

#import "ISPLbsModule.h"
#import "ISMeetMePerson.h"
#import "ISMeetMeGroup.h"
#import "ISPMeetMeRequestListener.h"
#import "ISPMeetMeListener.h"
#import "ISAbstractMeetMeRequest.h"

#import "ISMeetMeInsChangeStatusRequest.h"
#import "ISMeetMeInsConnectRequest.h"
#import "ISMeetMeInsCreateGroupRequest.h"
#import "ISMeetMeInsCreateTmpUserRequest.h"
#import "ISMeetMeInsCreateUserRequest.h"
#import "ISMeetMeInsGetGroupsRequest.h"
#import "ISMeetMeInsJoinGroupRequest.h"
#import "ISMeetMeInsLeaveGroupsRequest.h"
#import "ISMeetMeInsRefreshGroupsRequest.h"
#import "ISMeetMeExtChangeStatusRequest.h"
#import "ISMeetMeExtConnectRequest.h"
#import "ISMeetMeExtJoinGroupRequest.h"
#import "ISMeetMeExtLeaveGroupsRequest.h"
#import "ISMeetMeExtRefreshGroupsRequest.h"

@protocol PResponseParser;

/*!
 Class used to manage MeetMe methods.
 */
@interface ISMeetMeProvider : NSObject <ISPLbsModule> {
    
@protected
    
	//Boolean used to know if the user is connected
	Boolean m_isConnected;
    
    //MeetMe listener
    id<ISPMeetMeListener> m_listener;
    
    //Groups list
	NSMutableDictionary * m_groups;
	//Persons list
	NSMutableDictionary * m_persons;
    //User id
	NSString * m_userId;
	//User nickname
	NSString * m_userName;
}

#pragma mark - Accessors

/*!
 MeetMe events listener (Requests).
 */
@property (assign) id<ISPMeetMeListener> listener;

/*!
 User nickname.
 */
@property (readonly) NSString * userName;

/*!
 User identifier.
 */
@property (readonly) NSString * userId;

/*!
 Boolean used to know if the user is connected.
 */
@property (readonly) Boolean isConnected;

/*!
 Current groups list.
 */
@property (readonly) NSDictionary * groups;

/*!
 Array of groups the user is connected to.
 */
@property (readonly) NSArray * connectedGroupsIDs;

/*!
 Method used to get a specific group with its identifier.
 @param groupId Wanted group identifier.
 @return The wanted group (could be nil).
 */
- (ISMeetMeGroup *)getGroupByID:(int)groupId;

/*!
 Method used to get a specific group with its name.
 @param groupName Wanted group name.
 @return The wanted group (could be nil).
 */
- (ISMeetMeGroup *)getGroupByName:(NSString *)groupName;

/*!
 Method used to get a specific group with its external identifier.
 @param groupExtID Wanted external group identifier.
 @return The wanted group (could be nil).
 */
- (ISMeetMeGroup *)getGroupByExtID:(NSString *)groupExtID;

/*!
 Method used to get all related persons from a specific group.
 @param groupId Wanted group identifier.
 @return An array of all persons from the wanted group (could be nil).
 */
- (NSArray *)getPersonsFromGroup:(int)groupId;

#pragma mark - Insiteo requests

/*!
 Method used to disconnect the user from our servers.
 */
- (void)disconnect;

/*!
 Method used to connect a user to the MeetMe service.
 @param listener Listener to notify (for MeetMeRequest events).
 @param login User login.
 @param password User password.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestConnectionWithListener:(id<ISPMeetMeRequestListener>)listener andLogin:(NSString *)login andPassword:(NSString *)password;

/*!
 Intern callback called when the "connect" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onConnectionDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to create a temporary user and connect him to the MeetMe service.
 @param listener Listener to notify (for MeetMeRequest events).
 @param name User name.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestTmpConnectionWithListener:(id<ISPMeetMeRequestListener>)listener andName:(NSString *)name;

/*!
 Intern callback called when the "create temp user" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onTmpConnectionDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to create a user in our MeetMe service.
 @param listener Listener to notify (for MeetMeRequest events).
 @param login User login.
 @param password User password.
 @param name User name.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestUserRegistrationWithListener:(id<ISPMeetMeRequestListener>)listener andLogin:(NSString *)login andPassword:(NSString *)password andName:(NSString *)name;

/*!
 Intern callback called when the "create user" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onUserRegistrationDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to refresh the INSITEO MeetMe groups.
 @param listener Listener to notify (for MeetMeRequest events).
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestGroupsWithListener:(id<ISPMeetMeRequestListener>)listener;

/*!
 Intern callback called when the "refresh groups" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onGetGroupsDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to refresh the INSITEO MeetMe groups where the user is active.
 @param listener Listener to notify (for MeetMeRequest events).
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestActiveGroupsWithListener:(id<ISPMeetMeRequestListener>)listener;

/*!
 Intern callback called when the "refresh active groups" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onGetActiveGroupsDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to create an INSITEO MeetMe group.
 @param listener Listener to notify (for MeetMeRequest events).
 @param groupName Name of the group we want to create.
 @param groupPassword Password of the group we want to create.
 @param endDate Date when the group will be deleted.
 @param closeDate Date when the group will no longer accept users.
 @param isExclusive Boolean used to know if we disconnect the user from all the other groups (by default we connect the user to the just created group).
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestGroupCreationWithListener:(id<ISPMeetMeRequestListener>)listener andGroupName:(NSString *)groupName andGroupPassword:(NSString *)groupPassword andEndDate:(NSTimeInterval)endDate andCloseDate:(NSTimeInterval)closeDate andExclu:(Boolean)isExclusive;

/*!
 Intern callback called when the "create group" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onCreateGroupDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to join an INSITEO MeetMe group.
 @param listener Listener to notify (for MeetMeRequest events).
 @param groupId Wanted group identifier.
 @param groupName Wanted group name.
 @param groupPassword Wanted group password.
 @param isExclusive Boolean used to know if we disconnect the user from all the other groups (by default we connect the user to the just created group).
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestJoinGroupWithListener:(id<ISPMeetMeRequestListener>)listener andGroupId:(int)groupId andGroupName:(NSString *)groupName andGroupPassword:(NSString *)groupPassword andExclu:(Boolean)isExclusive;

/*!
 Intern callback called when the "join group" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onJoinGroupDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to join an INSITEO MeetMe group.
 @param listener Listener to notify (for MeetMeRequest events).
 @param groupIds Array of group identifiers we want to leave.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestLeaveGroupsWithListener:(id<ISPMeetMeRequestListener>)listener andGroupIds:(NSArray *)groupIds;

/*!
 Intern callback called when the "leave groups" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onLeaveGroupsDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to change the user status for INSITEO MeetMe groups.
 @param listener Listener to notify (for MeetMeRequest events).
 @param groupIds Array of group identifiers we want to change the status.
 @param newStatus New user status to update.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestStatusChangeWithListener:(id<ISPMeetMeRequestListener>)listener andGroupIds:(NSArray *)groupIds andNewStatus:(UserStatus)newStatus;

/*!
 Intern callback called when the "change status" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onStatusChangeDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

#pragma mark - External requests

/*!
 Method used to connect an external MeetMe user.
 @param listener Listener to notify (for MeetMeRequest events).
 @param userExtID User external identifier.
 @param userName User name.
 @param extGroupIds User external group identifiers.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestExternalConnectionWithListener:(id<ISPMeetMeRequestListener>)listener andUserExtID:(NSString *)userExtID andUserName:(NSString *)userName andExtGroupIds:(NSArray *)extGroupIds;

/*!
 Intern callback called when the "external connect" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onExternalConnectionDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to join an external MeetMe group.
 @param listener Listener to notify (for MeetMeRequest events).
 @param extGroupId External group identifier.
 @param extGroupName External group name.
 @param beginDate Group begin date.
 @param endDate Group end date.
 @param isExclusive Boolean used to know if we disconnect the user from all the other groups (by default we connect the user to the just created group).
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestExternalJoinGroupWithListener:(id<ISPMeetMeRequestListener>)listener andExtGroupId:(NSString *)extGroupId andExtGroupName:(NSString *)extGroupName andBeginDate:(NSTimeInterval)beginDate andEndDate:(NSTimeInterval)endDate andExclu:(Boolean)isExclusive;

/*!
 Intern callback called when the "external join group" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onExternalJoinGroupDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to leave external MeetMe groups.
 @param listener Listener to notify (for MeetMeRequest events).
 @param groupIds Group identifiers to leave from.
 @param extGroupIds External group identifiers to leave from.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestExternalLeaveGroupsWithListener:(id<ISPMeetMeRequestListener>)listener andGroupIds:(NSArray *)groupIds andExtGroupIds:(NSArray *)extGroupIds;

/*!
 Intern callback called when the "external leave groups" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onExternalLeaveGroupsDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to refresh external MeetMe groups.
 @param listener Listener to notify (for MeetMeRequest events).
 @param extGroupIds External group identifiers to refresh.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestExternalGroupsWithListener:(id<ISPMeetMeRequestListener>)listener andExtGroupIds:(NSArray *)extGroupIds;

/*!
 Intern callback called when the "external refresh groups" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onExternalRefreshGroupsDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

/*!
 Method used to change the user status for MeetMe groups.
 @param listener Listener to notify (for MeetMeRequest events).
 @param groupIds Array of group identifiers we want to change the status.
 @param newStatus New user status to update.
 @return The resulted MeetMe request.
 */
- (ISAbstractMeetMeRequest *)requestExternalStatusChangeWithListener:(id<ISPMeetMeRequestListener>)listener andGroupIds:(NSArray *)groupIds andNewStatus:(UserStatus)newStatus;

/*!
 Intern callback called when the "external change status" request succeeded or failed.
 @param request Related request.
 @param error The error (could be nil).
 @param parser The parser to use.
 */
- (void)onExternalStatusChangeDoneWithRequest:(ISAbstractMeetMeRequest *)request andError:(ISInsiteoError *)error andParser:(id<PResponseParser>)parser;

@end
