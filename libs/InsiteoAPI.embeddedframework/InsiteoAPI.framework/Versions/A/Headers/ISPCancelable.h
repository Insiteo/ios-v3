//
//  ISPCancelable.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 07/02/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPCancelable.h
 ISPCancelable
 */

#import <Foundation/Foundation.h>

/*!
 Protocol used to allow users to cancel intern task (init, update etc...).
 */

@protocol ISPCancelable <NSObject>

/*!
 Method called to cancel the related task.
 */
- (void)cancel;

@end
