#include "resources_sqlite.h"

int check_db_file()
{
    int rc;
    /* access returns: 0 => files exist, -1 => no file */
    if (access(DB_PATH, F_OK) == ERR_OK){
        rc = ERR_OK;
    }
    else{
        if (errno == ENOENT){
            printf("Path [%s] does not exist.\n", DB_PATH);
            rc = ERR_OP_FAILED;
        } else rc = ERR_OTHER;
    }
    return rc;
}

int open_db(sqlite3 **db_h)
{
    int rc;
    rc = sqlite3_open(DB_PATH, &(*db_h));
    if (rc != SQLITE_OK){
        fprintf(stderr, "Cannot access DB: [%s]", sqlite3_errmsg((*db_h)));
        rc = ERR_OP_FAILED;
    }
    return rc;
}

int close_db(sqlite3 *db_h)
{
    int rc;
    rc = sqlite3_close(db_h);
    if (rc != SQLITE_OK){
        fprintf(stderr, "Unable to finish database connection.",
                sqlite3_errmsg(db_h));
        rc = ERR_OP_FAILED;
    }
    return rc;
}

int execute_query(sqlite3 *db_h, char *sql_query)
{
    int rc;
    char *err_msg;

    rc = sqlite3_exec(db_h, sql_query, NULL, NULL, &err_msg);
    if (rc != SQLITE_OK){
        fprintf(stderr, "Unable to exec query: [%s] => [%s]\n.", sql_query,
                sqlite3_errmsg(db_h));
        rc = ERR_OP_FAILED;
    }
    return rc;
}
