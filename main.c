#include <stdlib.h>
#include <stdio.h>

#include <sqlite3.h>
#include <unistd.h>

#include "resources_sqlite.h"

#define DB_PATH "data/test_sqlite.db"
#define SQL_CREATE "CREATE TABLE MY_TAB(" \
                    "id INT NOT NUL PRIMARY KEY," \
                    "name TEXT" \
                    ");"


int create_db_structure();



int main(int argc, char **argv)
{
    sqlite3 *dbh;

    return 0;
}
