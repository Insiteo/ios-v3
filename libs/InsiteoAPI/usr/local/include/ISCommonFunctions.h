//
//  ISCommonFunctions.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 07/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISCommonFunctions.h
 ISCommonFunctions
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <mach/mach.h>
#import <mach/mach_host.h>

#import "CC3Foundation.h"

/*!
 Static class used to provide general help functions.
 */
@interface ISCommonFunctions : NSObject {
    
}

/*!
 Method called to compare two bytes array.
 @param array1 First bytes array to compare.
 @param array2 Second bytes array to compare.
 @param length Arrays length.
 @return <b>YES</b> if equals, else <b>NO</b>.
 */
+ (Boolean)compareBytesArrayWithArray1:(unsigned char *)array1 andArray2:(unsigned char *)array2 andLength:(int)length;

/*!
 Method used to convert hexadecimal NSString in NSData.
 @param hexString The hexadecimal NSString to convert.
 @return The converted NSData.
 */
+ (NSData *)hexToBytes:(NSString *)hexString;

/*!
 Method used to get the eucledian distance between two points.
 @param from First point.
 @param to Second point.
 @return The resulted eucledian distance.
 */
+ (float)eucledianDistanceFromPoint:(CGPoint)from toPoint:(CGPoint)to;

/*!
 Method used to get the MD5 NSString of a specific file.
 @param path Path where the file to use is located.
 @return The resulted NSString MD5.
 */
+ (NSString *)fileMD5:(NSString *)path;

/*!
 Method used to get the MD5 NSString of a specific NSString.
 @param str NSString to hash.
 @return The resulted NSString MD5.
 */
+ (NSString *)stringMD5:(NSString *)str;

/*!
 Method used to check the NSString nullity.
 @param stringToCheck The NSString to check.
 @return The resulted NSString checked.
 */
+ (NSString *)checkNilString:(NSString *)stringToCheck;

/*!
 Method used to remove HTML tags from an NSString.
 @param htmlString The NSString to use.
 @return The resulted NSString filtered.
 */
+ (NSString *)stringByStrippingHTML:(NSString *)htmlString;

/*!
 Method used to convert a degrees angle to radians.
 @param degrees Degrees angle.
 @return The converted radians angle.
 */
+ (float)degreesToRadians:(float)degrees;

/*!
 Method used to convert a radians angle to degrees.
 @param radians Radians angle.
 @return The converted degrees angle.
 */
+ (float)radiansToDegrees:(float)radians;

/*!
 Static method used to get the current time in milliseconds.
 @return The current time in milliseconds.
 */
+ (int64_t)getMStime;

/*!
 Static method used to get the current free memory.
 @return The current free memory.
 */
+ (natural_t)getFreeMemory;

/*!
 Static method used to append two NSString.
  @param text The first NSString to append.
  @param filePath The second NSString to append.
 */
+ (void)appendText:(NSString *)text toFile:(NSString *)filePath;

/*!
 Static method used to know if the WIFI is currently available.
 @return <b>YES</b> if the WIFI is available, otherwise <b>NO</b>.
 */
+ (Boolean)isWiFiAvailable;

/*!
 Static method used to get a CC3Ray from an NSValue.
 @param value NSValue containing the CC3Ray.
 @return The corresponding CC3Ray.
 */
+ (CC3Ray)rayWithValue:(NSValue *)value;

/*!
 Static method used to convert a CC3Ray to an NSValue.
 @param ray The CC3Ray to convert.
 @return The corresponding NSValue.
 */
+ (NSValue *)rayValue:(CC3Ray)ray;

/*!
 Static method used to get a CC3Vector4 from an NSValue.
 @param value NSValue containing the CC3Vector4.
 @return The corresponding CC3Vector4.
 */
+ (CC3Vector4)vector4WithValue:(NSValue *)value;

/*!
 Static method used to convert a CC3Vector4 to an NSValue.
 @param vector The CC3Vector4 to convert.
 @return The corresponding NSValue.
 */
+ (NSValue *)vector4Value:(CC3Vector4)vector;

@end
