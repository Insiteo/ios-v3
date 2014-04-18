//
//  ISLayer.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 17/02/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISLayer.h
 ISLayer
 */

#import "cocos2d.h"

/*!
 Class used to represent an INSITEO rendering layer.
 */
@interface ISLayer : CCLayer {
    
}

/*!
 Static method used to konw if the Cocos2d engine is initialized.
 @return <b>YES</b> if  it's initialized, otherwise <b>NO</b>.
 */
+ (Boolean)isCocos2dInitialized;

/*!
 Static method used to get a unique render identifier for ISPRTO.
 @return InitProvider unique instance.
 */
+ (int)generateCocos2dUniqueId;

@end
