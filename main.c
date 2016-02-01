#include "resources_sqlite.h"
#include <unistd.h>

//dasdasd

int main(int argc, char **argv)
{
    int rc;
    int rows = 0;
    sqlite3 *dbh;
    sqlite3_stmt *stmt_create = NULL, *stmt_insert = NULL, *stmt_select = NULL,
                 *stmt_insert_values = NULL;

    rc = check_db_file();
    open_db(&dbh);

    sqlite3_prepare_v2 (dbh, SQL_SELECT_ALL, -1, & stmt_select, NULL);
    sqlite3_prepare_v2 (dbh, SQL_CREATE, -1, & stmt_create, NULL);
    sqlite3_prepare_v2 (dbh, SQL_INSERT_HC, -1, & stmt_insert, NULL);
    sqlite3_prepare_v2 (dbh, SQL_INSERT_VALUES, -1, & stmt_insert_values, NULL);

    if (rc != ERR_OK){
        rc = sqlite3_step(stmt_create);
        if (rc != SQLITE_DONE) printf("Could not create DB strucutre.");
    }
    rc = sqlite3_step(stmt_insert);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Could not insert data into DB.");
    }
    insert_values(&stmt_insert_values);
    fprintf(stdout, "There is [%d]\n",  sqlite3_column_count(stmt_select));
    fprintf(stdout, " %s | %s\n", sqlite3_column_name(stmt_select, 0), sqlite3_column_name(stmt_select, 1));
    fprintf(stdout, "----------------------------------------\n");

    while ( (rc = sqlite3_step(stmt_select)) != SQLITE_DONE )
    {
        switch(rc)
        {
            case SQLITE_ROW:
                {
                    fprintf(stdout, "[%d] | %s\n", sqlite3_column_int(stmt_select,0), sqlite3_column_text(stmt_select,1));
                    rows++;
                    break;
                }
            case SQLITE_BUSY:
                {
                    fprintf(stderr, "Cannot access data, wait 1 seconds...\n");
                    sleep(1);
                    break;
                }
            case SQLITE_ERROR:
                fprintf(stderr, "Error occured: %s\n", sqlite3_errmsg(dbh));
                break;
            default:
                fprintf(stderr, "Undefined error occured: %s\n",  sqlite3_errmsg(dbh));
                break;
        }
    }


    sqlite3_finalize(stmt_select);
    sqlite3_finalize(stmt_create);
    sqlite3_finalize(stmt_insert);
    sqlite3_finalize(stmt_insert_values);
    close_db(dbh);

    return 0;
}
