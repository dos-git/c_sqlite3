#include <stdlib.h>
#include <stdio.h>

#include <sqlite3.h>

#include <unistd.h>

#define DIR_DATA data
#define DB_NAME test_sqlite.db
#define PATH_SEP "/"
//#define DB_PATH PATH_SEP + DIR_DATA + PATH_SEP + DB_NAME

int callback(void *, int, char **, char **);

int main(int argc, char **argv)
{
    char *err_msg = NULL;
    char cwd[1024];
    char full_path[] = "/home/dos/Programming/c_pro/c_sqlite3/data/test_sqlite.db";
    char *sql = "CREATE TABLE Cars(Id INT, Name TEXT PRIMARY KEY, Price INT);";
    char *sql_insert =  "INSERT INTO Cars VALUES(1, 'Audi', 52642);"
                        "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);"
                        "INSERT INTO Cars VALUES(3, 'Mazda', 9000);"
                        "INSERT INTO Cars VALUES(4, 'Volvo', 29000);"
                        "INSERT INTO Cars VALUES(5, 'VW', 99900);" ;

    char *sql_insert_2 =  "INSERT INTO Cars VALUES(1, 'Audi', 52642);";
    char *sql_select = "SELECT * FROM Cars";

    sqlite3 *db;
    int rc = sqlite3_open(full_path, &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
   if (rc != SQLITE_OK ) {
       fprintf(stderr, "SQL error: %s\n", err_msg);
       sqlite3_free(err_msg);
       sqlite3_close(db);
       return 1;
   }

   rc = sqlite3_exec(db, sql_insert, 0, 0, &err_msg);
   if (rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
   }
/*
   rc = sqlite3_exec(db, sql_insert_2, 0, 0, &err_msg);
   if (rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
   }
*/
   rc = sqlite3_exec(db, sql_select, callback, 0, &err_msg);
   if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
    }

   sqlite3_close(db);
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;
    int i = 0;
    for (i; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}
