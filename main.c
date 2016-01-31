#include "resources_sqlite.h"

int main(int argc, char **argv)
{
    int rc;
    sqlite3 *dbh;
    rc = check_db_file();
    open_db(&dbh);
    if (rc != ERR_OK) execute_query(dbh,SQL_CREATE);
    close_db(dbh);

    return 0;
}
