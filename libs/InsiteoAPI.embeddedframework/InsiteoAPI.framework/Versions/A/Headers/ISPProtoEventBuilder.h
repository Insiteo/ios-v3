//
//  ISPProtoEventBuilder.h
//  CommonAPI
//
//  Created by dev_iphone on 28/03/13.
//
//

/*!
 @header ISPProtoEventBuilder.h
 ISPProtoEventBuilder
 */

#import <Foundation/Foundation.h>

@class PBAnalyticsAbstractEvent;

/*!
 Protocol used to handles analytics protobuf events.
 */
@protocol ISPProtoEventBuilder <NSObject>

/*!
 Method called to get an abstract event for each analytics event type.
 */
- (PBAnalyticsAbstractEvent *)getProtoEvent;

@end
