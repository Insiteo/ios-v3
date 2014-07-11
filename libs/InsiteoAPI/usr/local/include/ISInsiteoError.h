//
//  ISInsiteoError.h
//  CommonAPI
//
//  Created by INSITEO on 28/03/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISInsiteoError.h
 ISInsiteoError
 */

#import <Foundation/Foundation.h>

#pragma mark - General

/*!
 @"IS_NO_ERROR_CODE"
 */
extern NSString * const IS_NO_ERROR_CODE;

/*!
 @"IS_API_NOT_INIT_ERROR_CODE"
 */
extern NSString * const IS_API_NOT_INIT_ERROR_CODE;

/*!
 @"IS_API_NOT_INIT_ERROR_MESSAGE"
 */
extern NSString * const IS_API_NOT_INIT_ERROR_MESSAGE;

/*!
 @"MODABSERR"
 */
extern NSString * const IS_LBS_MODULE_ABSENT_ERROR_CODE;

#pragma mark - Init

/*!
 @"IS_INIT_FAIL_ERROR_CODE"
 */
extern NSString * const IS_INIT_FAIL_ERROR_CODE;

/*!
 @"IS_INIT_FAIL_ERROR_MESSAGE"
 */
extern NSString * const IS_INIT_FAIL_ERROR_MESSAGE;

/*!
 @"IS_INIT_DOWNLOAD_ERROR_CODE"
 */
extern NSString * const IS_INIT_DOWNLOAD_ERROR_CODE;

/*!
 @"IS_INIT_UNZIP_ERROR_CODE"
 */
extern NSString * const IS_INIT_UNZIP_ERROR_CODE;

/*!
 @"IS_UPDATE_CANCEL_ERROR_CODE"
 */
extern NSString * const IS_UPDATE_CANCEL_ERROR_CODE;

/*!
 Class used to represent an Insiteo error.
 */
@interface ISInsiteoError : NSObject {

@private
    
    //Error code
    NSString * m_errorCode;
    //Error message
    NSString * m_errorMessage;
}

/*!
 Error code.
 */
@property (nonatomic, retain) NSString * errorCode;

/*!
 Error message.
 */
@property (nonatomic, retain) NSString * errorMessage;

/*!
 Main constructor.
 @param errorCode Error code.
 @param errorMessage Error message.
 */
- (id)initWithErrorCode:(NSString *)errorCode andErrorMessage:(NSString *)errorMessage;

/*!
 Static constructor.
 @param errorCode Error code.
 @param errorMessage Error message.
 */
+ (id)ISInsiteoErrorWithErrorCode:(NSString *)errorCode andErrorMessage:(NSString *)errorMessage;

@end
