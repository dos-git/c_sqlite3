#include "resources_sqlite.h"


int main(int argc, char **argv)
{
    int rc;
    int rows = 0;
    sqlite3 *dbh;
    sqlite3_stmt *stmt_create = NULL, *stmt_insert = NULL, *stmt_select = NULL,
                 *stmt_insert_values = NULL;
    char *err_msg = NULL;

    rc = check_db_file();
    open_db(&dbh);

    /* create DB when file does not exist */
    if (rc != ERR_OK){
        rc = sqlite3_exec(dbh, SQL_CREATE, NULL, NULL, &err_msg);
         if( rc != SQLITE_OK ){
            fprintf(stderr, "SQL_CREATE error: %s.\n", err_msg);
            sqlite3_free(err_msg);
            return -1;
         }
    }

    prepare_stmt_queries(&dbh, &stmt_select, &stmt_insert_values);

    insert_values(&stmt_insert_values, 1, "DOMINO");
    insert_values(&stmt_insert_values, 2, "BBBB");
    insert_values(&stmt_insert_values, 3, "ABX");

    print_all(&dbh, &stmt_select);

    sqlite3_finalize(stmt_select);
    sqlite3_finalize(stmt_create);
    sqlite3_finalize(stmt_insert_values);
    close_db(dbh);

    return 0;
}
