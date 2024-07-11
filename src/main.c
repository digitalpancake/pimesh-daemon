#include "main.h"
#include "sqlite3.h"
#include "db.h"

// TODO: Check if daemon is already installed
// Get upto-date version from github
// Connect to SQLite

int main() {
    sqlite3* db = connect_db();
    sqlite3_close(db);
    return 0;
}

