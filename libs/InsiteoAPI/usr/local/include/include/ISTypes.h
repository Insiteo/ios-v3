//
//  ISTypes.h
//  lbs
//
//  Created by dev_iphone on 08/07/2014.
//  Copyright (c) 2014 INSITEO. All rights reserved.
//

/*!
 Enum used to handle INSITEO server types.
 @constant PROD_SERVER Production server.
 @constant TEST_SERVER Test server.
 @constant DEV_SERVER Development server.
 */
typedef enum {
    PROD_SERVER = 1,
    TEST_SERVER,
    DEV_SERVER
} ISEServerType;