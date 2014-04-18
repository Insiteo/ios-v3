//
//  ISAnalyticsLocationEvent.h
//  CommonAPI
//
//  Created by dev_iphone on 27/03/13.
//
//

/*!
 @header ISAnalyticsLocationEvent.h
 ISAnalyticsLocationEvent
 */

#import "ISAnalyticsAbstractEvent.h"

#import "ISPosition.h"

/*!
 Class used to represent an analytics location event.
 */
@interface ISAnalyticsLocationEvent : ISAnalyticsAbstractEvent {
    
@private
    
    //ISPosition field
    ISPosition * m_position;
    //Location accuracy
    float m_accuracy;
    //Location azimuth
    float m_azimuth;
    //Location flags
    int m_flags;
}

/*!
 ISPosition field.
 */
@property (nonatomic, retain) ISPosition * position;

/*!
 Location accuracy.
 */
@property (nonatomic, readwrite) float accuracy;

/*!
 Location azimuth.
 */
@property (nonatomic, readwrite) float azimuth;

/*!
 Location flags.
 */
@property (nonatomic, readwrite) int flags;

/*!
 Main constructor.
 @param x Location x coordinates (in meters).
 @param y Location y coordinates (in meters).
 @param mapId Location map identifier.
 @param accuracy Location accuracy.
 @param azimuth Location azimuth.
 @param flags Location flags.
 */
- (id)initWithX:(double)x andY:(double)y andMapId:(int)mapId andAccuracy:(float)accuracy andAzimuth:(float)azimuth andFlags:(int)flags;

/*!
 Constructor.
 @param position Location position.
 @param accuracy Location accuracy.
 @param azimuth Location azimuth.
 @param flags Location flags.
 */
- (id)initWithPosition:(ISPosition *)position andAccuracy:(float)accuracy andAzimuth:(float)azimuth andFlags:(int)flags;

@end
