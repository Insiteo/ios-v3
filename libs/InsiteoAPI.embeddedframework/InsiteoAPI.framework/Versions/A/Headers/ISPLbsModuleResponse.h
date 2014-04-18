//
//  ISPLbsModuleResponse.h
//  LocationAPI
//
//  Created by INSITEO on 16/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISPLbsModuleResponse.h
 ISPLbsModuleResponse
 */

#import <Foundation/Foundation.h>

/*!
 Enum used to handle INSITEO protocol types.
 @constant LOC_PROTOCOL_PROTOBUF Protocol Buffers protocol.
 */
typedef enum {
    LOC_PROTOCOL_PROTOBUF
} ELocProtocol;

/*!
 Protocol used to handle LBS module response.
 */
@protocol ISPLbsModuleResponse <NSObject>

/*!
 Method called to get the current used protocol.
 @return Current used protocol.
 */
- (ELocProtocol)getProtocol;

@end
