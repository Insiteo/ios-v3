//
//  ISGenericRenderer.h
//  MapAPI
//
//  Created by INSITEO on 29/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISGenericRenderer.h
 ISGenericRenderer
 */

#import <Foundation/Foundation.h>

#import "ISPRenderer.h"
#import "ISPRTOListener.h"

/*!
 Class used to represent the generic map renderer we will use.
 */
@interface ISGenericRenderer : NSObject <ISPRenderer> {
    
@protected
    
    //Relative class
	NSString * m_rtoClass;
    //Renderer priority
	int m_priority;
    //Current map id
	ISMap * m_currentMap;
    
    //Boolean used to know if the Renderer is displayed
	Boolean m_displayEnabled;
    //Boolean used to know if the Renderer handle touch events
	Boolean m_touchEnabled;
    
	//RTO HashMap
	NSMutableDictionary * m_rtos;
    //The RTO NSArray mutex.
    NSLock * m_rtosLock;
	
	//RenderTouchObject listeners array
	id<ISPRTOListener> m_rtoListener;
	
	//Boolean used to know if we moved
	Boolean m_hasMoved;
    
#pragma mark - 3D
    
    //Current rendering mode
    ISERenderMode m_renderMode;
    //3D layer
    CC3Node * m_generic3dLayer;
}

/*!
 RTO HashMap.
 */
@property (nonatomic, retain) NSMutableDictionary * rtos;

/*!
 The RTO NSArray mutex.
 */
@property (nonatomic, retain) NSLock * rtosLock;

/*!
 Boolean used to know if we moved.
 */
@property (nonatomic, readwrite) Boolean hasMoved;

/*!
 Map view layer.
 */
@property (assign) ISLayer * layer;

/*!
 Main constructor.
 @param rtoClass Related RTO class.
 @param priority Renderer priority.
 */
- (id)initWithRTOClass:(Class)rtoClass andPriority:(int)priority;

/*!
 Method used to get the zone rendering position for a given RTO.
 @param zone Zone to draw in.
 @param rto RTO to draw.
 @param ratio Current rendering ratio.
 @param offset Current rendering offset.
 */
- (CGPoint)getZoneDrawPositionWithZone:(ISZone *)zone andRTO:(id<ISPRTO>)rto andRatio:(float)ratio andOffset:(CGPoint)offset;

/*!
 Method called to remove a RTO with its identifier.
 @param rtoId RTO identifier to remove.
 */
- (void)removeRTOWithId:(int)rtoId;

@end
