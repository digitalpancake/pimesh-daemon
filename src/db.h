#include <stdlib.h>

#include "list.h"
#include "sqlite3.h"

typedef enum {
    USER,
} DB_TYPE;

sqlite3* connect_db();
node* get_users(sqlite3* db);
node* dbquery(sqlite3* db, char* query, DB_TYPE type);
