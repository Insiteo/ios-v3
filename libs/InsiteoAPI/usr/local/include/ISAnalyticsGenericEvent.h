//
//  ISAnalyticsGenericEvent.h
//  CommonAPI
//
//  Created by dev_iphone on 27/03/13.
//
//

/*!
 @header ISAnalyticsGenericEvent.h
 ISAnalyticsGenericEvent
 */

#import <Foundation/Foundation.h>

#import "ISAnalyticsAbstractEvent.h"
#import "ISPosition.h"

/*!
 Class used to represent an analytics generic event.
 */
@interface ISAnalyticsGenericEvent : ISAnalyticsAbstractEvent

/*!
 An NSString which identify the event.
 */
@property (nonatomic, retain) NSString * eventType;

/*
 Internal Boolean used to know if the first integer parameter is set.
 */
@property (nonatomic, readwrite) Boolean hasIParam1;

/*
 First integer field.
 */
@property (nonatomic, readwrite) int iParam1;

/*
 Internal Boolean used to know if the second integer parameter is set.
 */
@property (nonatomic, readwrite) Boolean hasIParam2;

/*
 Second integer field.
 */
@property (nonatomic, readwrite) int iParam2;

/*
 Internal Boolean used to know if the first double parameter is set.
 */
@property (nonatomic, readwrite) Boolean hasDParam1;

/*
 First double field.
 */
@property (nonatomic, readwrite) double dParam1;

/*
 Internal Boolean used to know if the second double parameter is set.
 */
@property (nonatomic, readwrite) Boolean hasDParam2;

/*
 Second integer field.
 */
@property (nonatomic, readwrite) double dParam2;

/*
 First NSString field.
 */
@property (nonatomic, retain) NSString * sParam1;

/*
 Second NSString field.
 */
@property (nonatomic, retain) NSString * sParam2;

/*
 An array of ISPosition.
 */
@property (nonatomic, retain) NSMutableArray * positions;

/*!
 Main constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param dParam1 First double field.
 @param dParam2 Second double field.
 @param sParam1 First NSString field.
 @param sParam2 Second NSString field.
 @param pParam1 First ISPosition.
 @param pParam2 Second ISPosition.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andDParam1:(double)dParam1 andDParam2:(double)dParam2 andSParam1:(NSString *)sParam1 andSParam2:(NSString *)sParam2 andPParam1:(ISPosition *)pParam1 andPParam2:(ISPosition *)pParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 */
- (id)initWithEventType:(NSString *)eventType;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param sParam1 First NSString field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andSParam1:(NSString *)sParam1;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param sParam1 First NSString field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andSParam1:(NSString *)sParam1;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param sParam1 First NSString field.
 @param sParam2 Second NSString field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andSParam1:(NSString *)sParam1 andSParam2:(NSString *)sParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param dParam1 First double field.
 */
- (id)initWithEventType:(NSString *)eventType andDParam1:(double)dParam1;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param dParam1 First double field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andDParam1:(double)dParam1;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param dParam1 First double field.
 @param dParam2 Second double field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andDParam1:(double)dParam1 andDParam2:(double)dParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param dParam1 First double field.
 @param dParam2 Second double field.
 @param sParam1 First NSString field.
 @param sParam2 Second NSString field.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andDParam1:(double)dParam1 andDParam2:(double)dParam2 andSParam1:(NSString *)sParam1 andSParam2:(NSString *)sParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param sParam1 First NSString field.
 @param sParam2 Second NSString field.
 */
- (id)initWithEventType:(NSString *)eventType andSParam1:(NSString *)sParam1 andSParam2:(NSString *)sParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param pParam1 First ISPosition.
 @param pParam2 Second ISPosition.
 */
- (id)initWithEventType:(NSString *)eventType andPParam1:(ISPosition *)pParam1 andPParam2:(ISPosition *)pParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param pParam1 First ISPosition.
 @param pParam2 Second ISPosition.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andPParam1:(ISPosition *)pParam1 andPParam2:(ISPosition *)pParam2;

/*!
 Constructor.
 @param eventType An NSString which identify the event.
 @param iParam1 First integer field.
 @param iParam2 Second integer field.
 @param pParam1 First ISPosition.
 @param pParam2 Second ISPosition.
 */
- (id)initWithEventType:(NSString *)eventType andIParam1:(int)iParam1 andIParam2:(int)iParam2 andPParam1:(ISPosition *)pParam1 andPParam2:(ISPosition *)pParam2;

@end
