//
//  ISPItineraryRenderListener.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 11/04/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPItineraryRenderListener.h
 ISPItineraryRenderListener
 */

#import <Foundation/Foundation.h>

#import "ISItinerary.h"
#import "ISItinerarySection.h"
#import "ISPosition.h"

/*!
 Protocol used to handle Itinerary special touch events.
 */
@protocol ISPItineraryRenderListener <NSObject>

/*!
 Method called when an Itinerary section was touched.
 @param itinerary The related ISItinerary.
 @param instructionIndex The related ISItineraryInstruction index.
 @param section The touched ISItinerarySection.
 */
- (void)onWaypointClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex andSection:(ISItinerarySection *)section;

/*!
 Method called when an Itinerary instruction was touched (edges).
 @param itinerary The related ISItinerary.
 @param instructionIndex The related ISItineraryInstruction index.
 */
- (void)onInstructionClickedWithItinerary:(ISItinerary *)itinerary andInstructionIndex:(int)instructionIndex;

/*!
 Method called when an Itinerary map switcher was touched (waypoint used to change map).
 @param nextPosition The next position to display.
 */
- (void)onMapSwitcherClickedWithNextPosition:(ISPosition *)nextPosition;

@end
