//
//  ISPMeetMeListener.h
//  LocationAPI
//
//  Created by INSITEO on 15/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPMeetMeListener.h
 ISPMeetMeListener
 */

#import <Foundation/Foundation.h>

@class ISInsiteoError;

/*!
 Protocol used to handle general MeetMe events.
 */
@protocol ISPMeetMeListener <NSObject>

/*!
 Method called when new persons and new groups are available.
 @param persons The new available persons.
 @param groups The new available groups.
 */
- (void)onPersonsReceived:(NSDictionary *)persons andGroups:(NSDictionary *)groups;

/*!
 Method called when a MeetMe error occured.
 @param error The related ISInsiteoError (code, message).
 */
- (void)onMeetMeError:(ISInsiteoError *)error;

@end
