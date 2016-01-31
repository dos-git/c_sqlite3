#ifndef RESOURCES_SQLITE_H_INCLUDED
#define RESOURCES_SQLITE_H_INCLUDED


#include "stdio.h"
#include <unistd.h>     /* for access() */
#include <errno.h>      /* to compare codes when access is used */

#include "sqlite3.h"

#define ERR_OK           0      /* no error */
#define ERR_OP_FAILED   -1      /* operation failed */
#define ERR_OTHER       -11     /* other error not specified */

#define DB_PATH "data/test_sqlite.db"
#define SQL_CREATE "CREATE TABLE MY_TAB(" \
                    "id INT NOT NUL PRIMARY KEY," \
                    "name TEXT" \
                    ");"

int open_db(sqlite3 *dbh_ptr);      /* opens DB by handler (a pointer)*/
int close_db(sqlite3 *dbh_ptr);     /* close DB */

int check_db_file(void);                /* verifies DB file existance */
int create_db_structure(void);          /* call function to create DB structure */
int check_db_structure(void);           /* verifies DB structure */

#endif
