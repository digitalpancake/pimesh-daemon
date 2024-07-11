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

int get_users() {
    return 0;
}
