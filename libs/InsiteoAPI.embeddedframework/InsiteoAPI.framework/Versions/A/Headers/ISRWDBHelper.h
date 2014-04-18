//
//  ISRWDBHelper.h
//  CommonAPI
//
//  Created by Baptiste LE GUELVOUIT on 22/03/12.
//  Copyright (c) 2012 INSITEO. All rights reserved.
//

/*!
 @header ISRODBHelper.h
 ISRODBHelper
 */

#import <Foundation/Foundation.h>

#import "ISRODBHelper.h"

/*!
 Static class used to handle ReadWrite SQLITE requests.
 */
@interface ISRWDBHelper : ISRODBHelper {
    
}

/*!
 Method used to initilase the DataHelper.
 @param databasePath Application path where the database is located.
 */
- (void)initializeWithDatabasePath:(NSString *)databasePath;

/*!
 Method used to execute an SQL INSERT query.
 @param request The NSString sqlite query.
 @return the id of the inserted row, or Constants.NULL_ID if failed.
 */
- (int)executeInsert:(NSString *)request;

/*!
 Method used to execute an SQL query.
 @param request The NSString sqlite query.
 @return <b>YES</b> if the query succeeded, else <b>NO</b>.
 */
- (Boolean)executeRequest:(NSString *)request;

@end
