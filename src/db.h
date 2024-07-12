#include <stdlib.h>

#include "sqlite3.h"
#include "list.h"

sqlite3* connect_db();
node* get_users(sqlite3* db);
