//
//  ISCommonConstants.h
//  CommonAPI
//
//  Created by INSITEO on 15/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISCommonConstants.h
 ISCommonConstants
 */

#import <UIKit/UIKit.h>

#define INSITEO_DEBUG_PREFIX @"[INSITEO] "
#define ISLog(fmt, ...) do { if([ISCommonConstants getDebugMode]) { NSLog(INSITEO_DEBUG_PREFIX#fmt, ##__VA_ARGS__); }} while(0)

//Macros to declare a preference key (as a string)
#define USERPREF_STR_ROOT               @"USERPREF_"
#define DECL_USERPREF_STR(n)            NSString * const n = USERPREF_STR_ROOT#n

//Macros to build the getters (prototype and implementation)
#define GET_USERPREF_DECL(t, n)         +(t) get##n
#define GET_USERPREF_IMPL(t, n, v)      GET_USERPREF_DECL(t, n) { \
                                            t const USERPREF_DEFAULT_##n = v; \
                                            NSUserDefaults * p = [NSUserDefaults standardUserDefaults]; \
                                            t ret = [p objectForKey:USERPREF_STR_ROOT#n]; \
                                            return (ret == nil) ? USERPREF_DEFAULT_##n : ret; \
                                        }

//Macros to build the setters (prototype and implementation)
#define SET_USERPREF_DECL(t, n)         +(void) set##n:(t)v
#define SET_USERPREF_IMPL(t, n)         SET_USERPREF_DECL(t, n) { \
                                            NSUserDefaults * p = [NSUserDefaults standardUserDefaults]; \
                                            [p setValue:v forKey:n]; \
                                            [p synchronize]; \
                                        }

//
#define RESET_USERPREF_DECL(n)          +(void) reset##n
#define RESET_USERPREF_IMPL(n, v)       RESET_USERPREF_DECL(n) { \
                                            NSUserDefaults * p = [NSUserDefaults standardUserDefaults]; \
                                            [p setValue:v forKey:n]; \
                                            [p synchronize]; \
                                        }

//Macro to build all the declarations for a given preference key
#define USERPREF_DECL(t, n)             SET_USERPREF_DECL(t, n); \
                                        GET_USERPREF_DECL(t, n); \
                                        RESET_USERPREF_DECL(n)

//Macro to build all the implementations for a given preference key (t : type, n : name, v : default value)
#define USERPREF_IMPL(t, n, v)          DECL_USERPREF_STR(n); \
                                        SET_USERPREF_IMPL(t, n) \
                                        GET_USERPREF_IMPL(t, n, v) \
                                        RESET_USERPREF_IMPL(n, v)

//How to declare:
//in MY_CLASS.h: USERPREF_DECL(NSNumber *, MeasureTime);

//How to implement:
//in MY_CLASS.m: USERPREF_IMPL(NSNumber *, MeasureTime, [NSNumber numberWithInt:2]);

//How to set/get: [MY_CLASS getMeasureTime] and [MY_CLASS setMeasureTime]

#pragma mark - General

/*!
 Version code for this API
 */
extern NSString * const API_VERSION;

/*!
 Version code for this API, used in URLs
 */
extern NSString * const URL_VERSION;

/*!
 -1
 */
extern int const NULL_ID;

/*!
 @""
 */
extern NSString * const NIL_STRING;

#pragma mark - Internet Communication

/*!
 10.0  //In seconds
 */
extern float const REQUEST_TIMEOUT;

#pragma mark - MapAPI

/*!
 16
 */
extern int const LRU_CACHE_SIZE;

/*!
 4.0
 */
extern int const ZONE_THICKNESS;

/*!
 4.0
 */
extern int const ITINERARY_THICKNESS;

/*!
 15 //Margin in pixel
 */
extern int const CLICKABLE_ZONE_SIZE;

/*!
 256  //In pixels
 */
extern int const TILE_WIDTH;

/*!
 256 //In pixels
 */
extern int const TILE_HEIGHT;

/*!
 0
 */
extern int const INITIAL_ZOOM_LEVEL;

/*!
 -1
 */
extern int const ISPRENDERER_BACKGROUND_PRIORITY;

/*!
 0
 */
extern int const ISPRENDERER_TILES_PRIORITY;

#pragma mark - Pre-calculated ratios for smooth animations

/*!
 60
 */
extern int const COS_SQUARE_NB_VALUES;

/*!
 {
 0.25000,   0.29077,   0.33434,   0.38035,   0.42838,   0.47795,   0.52852,   0.57950,   0.63027,   0.68017,   
 0.72855,   0.77476,   0.81814,   0.85807,   0.89398,   0.92533,   0.95166,   0.97256,   0.98773,   0.99692,   
 1.00000,   0.99692,   0.98773,   0.97256,   0.95166,   0.92533,   0.89398,   0.85807,   0.81814,   0.77476,   
 0.72855,   0.68017,   0.63027,   0.57950,   0.52852,   0.47795,   0.42838,   0.38035,   0.33434,   0.29077,   
 0.25000,   0.21231,   0.17790,   0.14690,   0.11936,   0.09527,   0.07453,   0.05700,   0.04248,   0.03072,   
 0.02145,   0.01435,   0.00912,   0.00543,   0.00297,   0.00145,   0.00060,   0.00019,   0.00004,   0.00000
 }
 */
extern double const COS_SQUARE_THETA[];

/*!
 28.98797
 */
extern float const COS_SQUARE_THETA_SUM;

/*!
 Class used to provide general constants.
 */
@interface ISCommonConstants : NSObject {

}

/*!
 Method used to know if we are in DEBUG mode.
 @return <b>YES</b> if we are in DEBUG mode, otherwise, <b>NO</b>.
 */
+ (Boolean)getDebugMode;

/*!
 Method used to set the DEBUG mode.
 @param debugMode Boolean parameter used to set the DEBUG mode status.
 */
+ (void)setDebugMode:(Boolean)debugMode;

@end
