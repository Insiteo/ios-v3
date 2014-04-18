//
//  ISPRTOListener.h
//  CommonAPI
//
//  Created by INSITEO on 11/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISPRTOListener.h
 ISPRTOListener
 */

#import <UIKit/UIKit.h>

#import "ISPRTO.h"

@protocol ISPZone;

/*!
 Protocol used to specify the behaviour of an RTO touch listener.
 @warning When one of theses callbacks is called you need to create a another thread if you want to use ISMapViewController methods.
 */
@protocol ISPRTOListener

/*!
 Method called when an RTO is selected.
 @param rto The related RTO.
 @param zone The related zone (could be nil).
 @warning When the callback is called you need to create a another thread if you want to use ISMapViewController methods.
 */
- (void)onRTOSelected:(id<ISPRTO>)rto andZone:(id<ISPZone>)zone;

/*!
 Method called when an RTO is released.
 @param rto The related RTO.
 @param zone The related zone (could be nil).
 @warning When the callback is called you need to create a another thread if you want to use ISMapViewController methods.
 */
- (void)onRTOReleased:(id<ISPRTO>)rto andZone:(id<ISPZone>)zone;

/*!
 Method called when an RTO is clicked.
 @param rto The related RTO.
 @param zone The related zone (could be nil).
 @warning When the callback is called you need to create a another thread if you want to use ISMapViewController methods.
 */
- (void)onRTOClicked:(id<ISPRTO>)rto andZone:(id<ISPZone>)zone;

/*!
 Method called when an RTO is moved.
 @param rto The related RTO.
 @param zone The related zone (could be nil).
 @warning When the callback is called you need to create a another thread if you want to use ISMapViewController methods.
 */
- (void)onRTOMoved:(id<ISPRTO>)rto andZone:(id<ISPZone>)zone;

@end
