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
            rc = ERR_NO_EXIST;
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
        fprintf(stderr, "Unable to finish database connection - %s.\n",
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
        fprintf(stderr, "Unable to exec query: [%s] - %s.\n.", sql_query,
                sqlite3_errmsg(db_h));
        rc = ERR_OP_FAILED;
    }
    return rc;
}

int prepare_stmt_queries(sqlite3 **db_h, sqlite3_stmt **stmt_select, sqlite3_stmt **stmt_insert_values)
{
    int rc;
    rc = sqlite3_prepare_v2 ((*db_h), SQL_SELECT_ALL, -1, & (*stmt_select), NULL);
    if (rc != SQLITE_OK){
        printf("Could not compile select query - %s.\n", sqlite3_errmsg((*db_h)));
        goto error_stmt_prepare;
    }
    rc = sqlite3_prepare_v2 ((*db_h), SQL_INSERT_VALUES, -1, & (*stmt_insert_values), NULL);
    if (rc != SQLITE_OK){
        printf("Could not compile insert query - %s.\n", sqlite3_errmsg((*db_h)));
        goto error_stmt_prepare;
    }

    return ERR_OK;

error_stmt_prepare:
    return ERR_OP_FAILED;
}

void print_time()
{
    struct tm * timeinfo;
    time_t now = time(0);
    //time ( &now );
    timeinfo = localtime ( &now );
    printf("NOW =>>>> %lld\n", (long long) time(NULL));
    printf ( "Current local time and date: %s\n\n", asctime (timeinfo) );
}

int insert_values(sqlite3_stmt **stmt_insert_values)
{
    time_t now = time(0);

    sqlite3_bind_int((*stmt_insert_values), 1, 3);
    sqlite3_bind_text((*stmt_insert_values), 2, "DDD", sizeof("DDD"), NULL);
    sqlite3_bind_int64((*stmt_insert_values), 3, now);
    sqlite3_step((*stmt_insert_values));

    /* neccessary if SQL query will be reused */
    sqlite3_reset((*stmt_insert_values));

    sqlite3_bind_int((*stmt_insert_values), 1, 4);
    sqlite3_bind_text((*stmt_insert_values), 2, "SSS", sizeof("SSS"), NULL);
    sqlite3_bind_int64((*stmt_insert_values), 3, now);
    sqlite3_step((*stmt_insert_values));


    return 0;
}

void print_all(sqlite3 **db_h, sqlite3_stmt **stmt_select)
{
    int rc, rows;
    fprintf(stdout, " %s | %s | %s\n",  sqlite3_column_name((*stmt_select), 0),
                                        sqlite3_column_name((*stmt_select), 1),
                                        sqlite3_column_name((*stmt_select), 2));
    fprintf(stdout, "------------------------------------------------------\n");

    rows = 0;
    while ( (rc = sqlite3_step((*stmt_select))) != SQLITE_DONE )
    {
        switch(rc)
        {
            case SQLITE_ROW:
                {
                    fprintf(stdout, "[%d] | %s | %s\n", sqlite3_column_int((*stmt_select),0),
                                                        sqlite3_column_text((*stmt_select),1),
                                                        sqlite3_column_text((*stmt_select),2));
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
                fprintf(stderr, "Error occured: %s\n", sqlite3_errmsg((*db_h)));
                break;
            default:
                fprintf(stderr, "Undefined error occured: %s\n",  sqlite3_errmsg((*db_h)));
                break;
        }
    }
}
