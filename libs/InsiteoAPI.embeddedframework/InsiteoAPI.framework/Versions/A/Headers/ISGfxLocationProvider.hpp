//
//  ISGfxLocationProvider.h
//  LocationAPI
//
//  Created by Baptiste LE GUELVOUIT on 06/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISGfxLocationProvider.hpp
 ISLocationProvider
 */

#import "ISLocationProvider.hpp"
#import "ISLocationRenderer.h"

/*!
 Class used to provide, get and RENDER user locations.
 @warning When using this class, you will need to tag your implementor as C++ class (*.mm extension).
 */
@interface ISGfxLocationProvider : ISLocationProvider {
    
@private
    
    //Location renderer
    ISLocationRenderer * m_locationRenderer;
}

/*!
 Location Renderer.
 */
@property (nonatomic, retain) ISLocationRenderer * renderer;

@end
