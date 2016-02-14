#ifndef RESOURCES_SQLITE_H_INCLUDED
#define RESOURCES_SQLITE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     /* for access() */
#include <errno.h>      /* to compare codes when access is used */

#include "sqlite3.h"
#include <time.h>

#define ERR_OK          0      /* no error */
#define ERR_OP_FAILED   1      /* operation failed */
#define ERR_NO_EXIST    2      /* resource does not exist */
#define ERR_OTHER       9      /* other error not specified */

#define DB_PATH "data/test_sqlite.db"
#define SQL_CREATE "CREATE TABLE MY_TAB(" \
                    "id INTEGER NOT NULL PRIMARY KEY, " \
                    "name TEXT DEFAULT NULL, " \
                    "date_start DATETIME DEFAULT CURRENT_TIMESTAMP " \
                    ");"
#define SQL_INSERT_HC "INSERT INTO MY_TAB VALUES(1, \"Domino\");" \
                      "INSERT INTO MY_TAB VALUES(2, \"Stefano\");"
#define SQL_INSERT_VALUES "INSERT INTO MY_TAB(id, name) VALUES(?,?);" \

#define SQL_SELECT_ALL "SELECT id, name, strftime('%Y-%m-%d %H:%M:%S', date_start) as start_time FROM MY_TAB;"

/* CURRENT_TIMESTAMP */

int open_db(sqlite3 **db_h);      /* opens DB by handler (a pointer)*/
int close_db(sqlite3 *db_h);     /* close DB */

int check_db_file(void);                /* verifies DB file existance */
int create_db_structure(void);          /* call function to create DB structure */
int check_db_structure(void);           /* verifies DB structure */

int prepare_stmt_queries(sqlite3 **db_h, sqlite3_stmt **stmt_select, sqlite3_stmt **stmt_insert_values);

int insert_values(sqlite3_stmt **stmt_insert_values);
int execute_query(sqlite3 *db_h, char *sql_query);

void print_all(sqlite3 **db_h, sqlite3_stmt **stmt_select);

#endif
