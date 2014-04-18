//
//  ISMeetMeGroup.h
//  LocationAPI
//
//  Created by INSITEO on 21/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISMeetMeGroup.h
 ISMeetMeGroup
 */

#import <Foundation/Foundation.h>

#import "ISMeetMePerson.h"

/*!
 Class used to represent a MeetMe group with its information and persons.
 */
@interface ISMeetMeGroup : NSObject {
    
@private
    
	//Group identifier
	int m_groupId;
    //Group name
    NSString * m_groupName;
    //Group owner identifier
    NSString * m_ownerId;
    //Integer used to know how many people are linked to this group
	int m_usersCount;
    //External identifier
	NSString * m_externalId;
    //User status for this group
	UserStatus m_userStatus;
    //List of persons identifier for this group
    NSMutableArray * m_personIds;
}

/*!
 Group identifier.
 */
@property (nonatomic, readwrite) int groupId;

/*!
 Group identifier key.
 */
@property (nonatomic, retain) NSNumber * idKey;

/*!
 Group name.
 */
@property (nonatomic, retain) NSString * groupName;

/*!
 Group owner identifier.
 */
@property (nonatomic, retain) NSString * ownerId;

/*!
 Integer used to know how many people are linked to this group.
 */
@property (nonatomic, readwrite) int usersCount;

/*!
 Group external identifier.
 */
@property (nonatomic, retain) NSString * externalId;

/*!
 Users status for this group.
 */
@property (nonatomic, readwrite) UserStatus userStatus;

/*!
 List of persons identifier for this group.
 */
@property (nonatomic, retain) NSMutableArray * personIds;

/*!
 Main constructor.
 @param groupId Group identifier.
 @param groupName Group name.
 @param groupOwnerId Group owner identifier.
 @param usersCount Integer used to know how many people are linked to this group.
 @param externalId Group external identifier.
 @param userStatus Users status for this group.
 @param personIds List of persons identifier for this group.
 */
- (id)initWithGroupId:(int)groupId andName:(NSString *)groupName andGroupOwnerId:(NSString *)groupOwnerId andUsersCount:(int)usersCount andExternalId:(NSString *)externalId andUserStatus:(UserStatus)userStatus andPersonIds:(NSMutableArray *)personIds;

/*!
 Static main constructor.
 @param groupId Group identifier.
 @param groupName Group name.
 @param groupOwnerId Group owner identifier.
 @param usersCount Integer used to know how many people are linked to this group.
 @param externalId Group external identifier.
 @param userStatus Users status for this group.
 @param personIds List of persons identifier for this group.
 */
+ (id)ISMeetMeGroupWithGroupId:(int)groupId andName:(NSString *)groupName andGroupOwnerId:(NSString *)groupOwnerId andUsersCount:(int)usersCount andExternalId:(NSString *)externalId andUserStatus:(UserStatus)userStatus andPersonIds:(NSMutableArray *)personIds;

/*!
 Method used to update the group with anoter one.
 @param group Group to use for update.
 */
- (void)updateWithGroup:(ISMeetMeGroup *)group;

/*!
 Method used to add a person identifier to this group.
 @param personId Person identifier to add.
 */
- (void)addPersonId:(NSString *)personId;

@end
