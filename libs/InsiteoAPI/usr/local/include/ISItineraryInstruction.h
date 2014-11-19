//
//  ISItineraryInstruction.h
//  lbs
//
//  Created by dev_iphone on 17/10/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISItineraryInstruction.h
 ISItineraryInstruction
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 Class used to define an itinerary instruction.
 */
@interface ISItineraryInstruction : NSObject

/*!
 Instruction identifier.
 */
@property (nonatomic, retain) NSString * instructionId;

/*!
 Instruction label.
 */
@property (nonatomic, retain) NSString * instructionInformation;

/*!
 Instruction bounding rect (in ext coordinates).
 */
@property (nonatomic, readwrite) CGRect boundingRect;

/*!
 Instruction related map identifier.
 */
@property (nonatomic, readwrite) int mapId;

/*!
 An array that contains all the instruction steps (array of ISItinerarySection).
 */
@property (nonatomic, retain) NSMutableArray * steps;

/*!
 Related picture url.
 */
@property (nonatomic, retain) NSString * pictureUrl;

/*!
 Related overlay url (image to put on top of the picture: could be nil).
 */
@property (nonatomic, retain) NSString * overlayUrl;

/*!
 Distance to arrival.
 */
@property (nonatomic, readwrite) float remainingDistance;

/*!
 Length in meters.
 */
@property (nonatomic, readwrite) float lengthInMeters;

/*!
 Time to arrival.
 */
@property (nonatomic, readwrite) float remainingTime;

/*!
 Duration in seconds.
 */
@property (nonatomic, readwrite) float durationInSeconds;

/*!
 Boolean used to know if the section corresponds to a map change.
 */
@property (nonatomic, readwrite) Boolean isMapChanger;

/*!
 Method used to know if the instruction has a related picture.
 @return <b>YES</b> if the instruction has a related picture, otherwise <b>NO</b>.
 */
- (Boolean)hasPicture;

/*!
 Method used to know if the instruction has a related picture url.
 @return <b>YES</b> if the instruction has a related picture url, otherwise <b>NO</b>.
 */
- (Boolean)hasPictureUrl;

@end
