#include <stdio.h>

#include "db.h"
#include "sqlite3.h"

#define DB_NAME "mesh_db.db"

sqlite3* connect_db() {
    sqlite3* db;
    int rc = sqlite3_open(DB_NAME, &db);

    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    return db;
}

int get_users_callback (void *data, int argc, char **argv, char **azColName) {
   for(int i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;}

int get_users(sqlite3* db) {
    const char* data = "Callback function";

    char* sql = "select * from Users";

    char* z_err_msg;
    int rc = sqlite3_exec(db, sql, get_users_callback, (void*)data, &z_err_msg);

    if(rc!=SQLITE_OK) {
        sqlite3_free(z_err_msg);
    }

    return 0;
}
