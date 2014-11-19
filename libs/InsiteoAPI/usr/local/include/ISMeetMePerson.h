//
//  ISMeetMePerson.h
//  LocationAPI
//
//  Created by INSITEO on 06/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISMeetMePerson.h
 ISMeetMePerson
 */

#import <Foundation/Foundation.h>

#import "ISPosition.h"

/*!
 Enum used to manage MeetMe user's states in groups.
 @constant MEET_ME_STATUS_DISCONNECTED The person is disconnected.
 @constant MEET_ME_STATUS_VISIBLE The user is visible.
 @constant MEET_ME_STATUS_HIDDEN The user is hidden.
 */
typedef enum {
    MEET_ME_STATUS_DISCONNECTED = 0,
    MEET_ME_STATUS_VISIBLE = 1,
	MEET_ME_STATUS_HIDDEN = 2,
} UserStatus;

/*!
 Class used to represent a MeetMe person.
 */
@interface ISMeetMePerson : NSObject

/*!
 Person position.
 */
@property (nonatomic, retain) ISPosition * position;

/*!
 Person unique identifier.
 */
@property (nonatomic, retain) NSString * userId;

/*!
 Person external identifier (could be nil).
 */
@property (nonatomic, retain) NSString * externalUserId;

/*!
 Person external name (nickname: could be nil).
 */
@property (nonatomic, retain) NSString * externalName;

/*!
 Groups Id list.
 */
@property (nonatomic, retain) NSMutableIndexSet * groupIds;

#pragma mark - Rendering

/*!
 Person rendering color.
 */
@property (nonatomic, retain) UIColor * color;

/*!
 Person picture URL.
 */
@property (nonatomic, retain) NSString * userPictureUrl;

/*!
 Main constructor.
 @param position Person position.
 @param userId Person unique identifier.
 @param externalUserId Person external identifier (could be nil).
 @param externalName Person external name (nickname: could be nil).
 @param color Person rendering color.
 */
- (id)initWithPosition:(ISPosition *)position andUserId:(NSString *)userId andExternalUserId:(NSString *)externalUserId andExternalName:(NSString *)externalName andColor:(UIColor *)color;

/*!
 Static main constructor.
 @param position Person position.
 @param userId Person unique identifier.
 @param externalUserId Person external identifier (could be nil).
 @param externalName Person external name (nickname: could be nil).
 @param color Person rendering color.
 */
+ (id)ISMeetMePersonWithPosition:(ISPosition *)position andUserId:(NSString *)userId andExternalUserId:(NSString *)externalUserId andExternalName:(NSString *)externalName andColor:(UIColor *)color;

/*!
 Method used to know if the person has a currrent position.
 @return <b>YES</b> if the person has a position, otherwise <b>NO</b>.
 */
- (Boolean)hasLocation;

/*!
 Method used to update the person with another one.
 @param person ISMeetMePerson to use for update.
 */
- (void)updateWithPerson:(ISMeetMePerson *)person;

/*!
 Method used to add a new group identifier for this person.
 @param groupId Group identifier to add.
 @return Return how many groups the person is linked to.
 */
- (int)addGroupId:(int)groupId;

/*!
 Method used to remove a group identifier for this person.
 @param groupId Group identifier to remove.
 @return Return how many groups the person is linked to.
 */
- (int)removeGroupId:(int)groupId;

@end
