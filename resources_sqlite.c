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
