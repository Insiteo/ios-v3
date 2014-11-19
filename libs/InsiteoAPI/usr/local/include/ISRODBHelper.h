//
//  ISRODBHelper.h
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
#import <sqlite3.h>

/*!
 @"insiteo.db"
 */
extern NSString * const DATABASENAME;

/*!
 Static class used to handle ReadOnly SQLITE requests.
 */
@interface ISRODBHelper : NSObject {
    
@protected
    
    //SQLITE database
    sqlite3 * m_database;
    
    //Database name
    NSString * m_databaseName;
    //Database lock
    NSLock * m_dbLock;    
    //Database path
    NSString * m_databasePath;
}

/*!
 The database path.
 */
@property (nonatomic, retain) NSString * databasePath;

/*!
 The database lock.
 */
@property (nonatomic, retain) NSLock * dbLock;

/*!
 Method used to initialize the DataHelper.
 @param databaseName The database name to use.
 @param databasePath Application path where the database is located.
 */
- (void)initializeWithDatabaseName:(NSString *)databaseName andDatabasePath:(NSString *)databasePath;

/*!
 Method used to check if database exists.
 */
- (Boolean)checkDatabase;

/*!
 Method used to open the sqlite database.
 @return <b>YES</b> if it succeeded, else <b>NO</b>.
 */
- (Boolean)openDatabase;

/*!
 Method used to close the sqlite database.
 */
- (void)closeDatabase;

/*!
 Method used to get a NSString from an sqlite statement and a field position.
 @param statement The related sqlite statement.
 @param position The related field position.
 @return The resulted NSString (could be nil).
 */
- (NSString *)getStringWithStatement:(sqlite3_stmt *)statement andPosition:(int)position;

/*!
 Method used to execute an SQL SELECT query.
 @param request The NSString sqlite query.
 @param lock Boolean used to know if we need to lock the database during the query.
 @return The resulted sqlite statement (rows).
 */
- (sqlite3_stmt *)executeSelect:(NSString *)request andLock:(Boolean)lock;

/*!
 Method used to execute an SQL SELECT query.
 @param request The NSString sqlite query.
 @return The resulted sqlite statement (rows).
 */
- (sqlite3_stmt *)executeSelect:(NSString *)request;

/*!
 Method used to update the current database path.
 */
- (void)updateDatabasePath;

@end
