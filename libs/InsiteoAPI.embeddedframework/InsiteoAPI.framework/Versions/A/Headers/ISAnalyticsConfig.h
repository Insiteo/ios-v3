//
//  ISAnalyticsConfig.h
//  CommonAPI
//
//  Created by dev_iphone on 12/02/13.
//
//

/*!
 @header ISAnalyticsConfig.h
 ISAnalyticsConfig
 */

#import <Foundation/Foundation.h>

/*!
 Class which represents the analytics configuration.
 */
@interface ISAnalyticsConfig : NSObject {
    
@private
    
    //Remote service URL (from ISInitProvider)
    NSString * m_serviceUrl;
    //HTTP request frequency (in seconds)
    float m_frequency;
    //Number of events sent in one request
    int m_nbEventsByRequest;
    //Location event frequency
    float m_locationFrequency;
}

/*!
 Remote service URL (from ISInitProvider).
 */
@property (nonatomic, retain) NSString * serviceUrl;

/*!
 HTTP request frequency (in seconds).
 */
@property (nonatomic, readwrite) float frequency;

/*!
 Number of events sent in one request.
 */
@property (nonatomic, readwrite) int nbEventsByRequest;

/*!
 Location event frequency.
 */
@property (nonatomic, readwrite) float locationFrequency;

/*!
 Main constructor.
 @param serviceUrl Remote service URL.
 @param frequency HTTP request frequency.
 @param nbEventsByRequest Number of events sent in one request.
 @param locationFrequency Location event frequency.
 */
- (id)initWithServiceUrl:(NSString *)serviceUrl andFrequency:(float)frequency andNbEventsByRequest:(int)nbEventsByRequest andLocationFrequency:(float)locationFrequency;

@end
