//
//  ISInitInformation.h
//  CommonAPI
//
//  Created by INSITEO on 14/01/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

/*!
 @header ISInitInformation.h
 ISInitInformation
 */

#import <Foundation/Foundation.h>

/*!
 Class used to represent the initialization result information.
 */
@interface ISInitInformation : NSObject {
    
@private
    
	//Maps resources path
	NSString * m_mapsPath;
	//Content resources path
	NSString * m_contentPath;
	//LBS server
	NSString * m_lbsServer;
    //Analytics server
	NSString * m_analyticsServer;
    
    //Zip full md5
    NSString * m_zipFullMd5;
    //Zip lite md5
    NSString * m_zipLiteMd5;
}

/*!
 Maps resources path.
 */
@property (nonatomic, retain) NSString * mapsPath;

/*!
 Content resources path.
 */
@property (nonatomic, retain) NSString * contentPath;

/*!
 LBS server.
 */
@property (nonatomic, retain) NSString * lbsServer;

/*!
 Analytics server.
 */
@property (nonatomic, retain) NSString * analyticsServer;

/*!
 Zip full md5.
 */
@property (nonatomic, retain) NSString * zipFullMd5;

/*!
 Zip lite md5.
 */
@property (nonatomic, retain) NSString * zipLiteMd5;

@end
