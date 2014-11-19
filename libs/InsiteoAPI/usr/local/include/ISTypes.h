//
//  ISTypes.h
//  lbs
//
//  Created by dev_iphone on 08/07/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 @header ISTypes.h
 ISTypes
 */

/*!
 Enum used to handle INSITEO server types.
 @constant ISEServerTypeProd Production server.
 @constant ISEServerTypeTest Test server.
 @constant ISEServerTypeDev Development server.
 */
typedef enum {
    ISEServerTypeProd = 1,
    ISEServerTypeTest,
    ISEServerTypeDev
} ISEServerType;

/*!
 Enum used to handle different map rendering mod.
 @constant ISERenderMode2D 2D rendering.
 @constant ISERenderMode3D 3D rendering.
 */
typedef enum {
    ISERenderMode2D,
    ISERenderMode3D,
} ISERenderMode;