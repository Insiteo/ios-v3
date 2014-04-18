//
//  ISPLbsModuleRequest.h
//  LocationAPI
//
//  Created by INSITEO on 16/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPLbsModuleRequest.h
 ISPLbsModuleRequest
 */

#import <Foundation/Foundation.h>

#import "ISPLbsModuleResponse.h"

/*!
 Protocol used to handle LBS module request.
 */
@protocol ISPLbsModuleRequest <NSObject>

/*!
 Method called to get the current used protocol.
 @return Current used protocol.
 */
- (ELocProtocol)getProtocol;

@end
