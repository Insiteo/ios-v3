//
//  ISAbstractMeetMeRequest.h
//  LocationAPI
//
//  Created by INSITEO on 03/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ISPMeetMeRequestListener.h"

@class ISMeetMeProvider;

@interface ISAbstractMeetMeRequest : NSObject {
    
@protected

    NSLock * m_cancelLock;     //isCanceled semaphore
    Boolean m_isCanceled;
    int m_requestId;
    NSString * m_userId;
    id<ISPMeetMeRequestListener> m_listener;
    ISMeetMeProvider * m_provider;
    
    NSString * m_urlConnection;
}

@property (nonatomic, readonly) int requestId;

@property (nonatomic, readonly) Boolean isCanceled;

@property (assign) id<ISPMeetMeRequestListener> listener;

- (id)initWithProvider:(ISMeetMeProvider *)provider andListener:(id<ISPMeetMeRequestListener>)listener andUserId:(NSString *)userId;

- (void)start;

- (void)preExecute;

- (void)execute;

- (void)cancel;

- (void)notifyListenerWithSuccess:(Boolean)success andError:(ISInsiteoError *)error;

@end
