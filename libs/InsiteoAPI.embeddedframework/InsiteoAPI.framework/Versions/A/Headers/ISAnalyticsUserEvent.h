//
//  ISAnalyticsUserEvent.h
//  CommonAPI
//
//  Created by dev_iphone on 12/02/13.
//
//

/*!
 @header ISAnalyticsUserEvent.h
 ISAnalyticsUserEvent
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>

#import "ISAnalyticsAbstractEvent.h"

/*!
 Class used to represent an analytics user event.
 */
@interface ISAnalyticsUserEvent : ISAnalyticsAbstractEvent {
    
@private
    
    //Application version ("%version_%name")
    NSString * m_version;
    //INSITEO api version
    NSString * m_apiVersion;
    //INSITEO site identifier
    int m_siteId;
    //INSITEO application version
    int m_applicationVersion;
    //INSITEO language
    NSString * m_language;
    //TODO : all packages versions (add function in ISInitProvider)
    
    //Device platform
    NSString * m_platform;
    //Device os version
    NSString * m_osVersion;
    //Device resolution
    NSString * m_resolution;
    //Device carrier
    NSString * m_carrier;
    //Device network
    NSString * m_network;
    //Device device name
    NSString * m_deviceName;
    //Device model name
    NSString * m_modelName;
}

/*!
 Application version ("%version_%name").
 */
@property (nonatomic, retain) NSString * version;

/*!
 INSITEO api version.
 */
@property (nonatomic, retain) NSString * apiVersion;

/*!
 INSITEO site identifier.
 */
@property (nonatomic, readwrite) int siteId;

/*!
 INSITEO application version.
 */
@property (nonatomic, readwrite) int applicationVersion;

/*!
 INSITEO language.
 */
@property (nonatomic, retain) NSString * language;

/*!
 Device platform.
 */
@property (nonatomic, retain) NSString * platform;

/*!
 Device os version.
 */
@property (nonatomic, retain) NSString * osVersion;

/*!
 Device resolution.
 */
@property (nonatomic, retain) NSString * resolution;

/*!
 Device carrier.
 */
@property (nonatomic, retain) NSString * carrier;

/*!
 Device network.
 */
@property (nonatomic, retain) NSString * network;

/*!
 Device name.
 */
@property (nonatomic, retain) NSString * deviceName;

/*!
 Device model name.
 */
@property (nonatomic, retain) NSString * modelName;

@end
