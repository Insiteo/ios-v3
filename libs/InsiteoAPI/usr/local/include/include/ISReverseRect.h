//
//  ISReverseRect.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 03/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISReverseRect.h
 ISReverseRect
 */

#import "ISRect.h"

/*!
 Class used to represent a rectangle defined by 4 int values (left, top, right, bottom) but whith the Y axis reversed (ex: 0/150/50/0).
 */
@interface ISReverseRect : ISRect

@end
