#include "main.h"
#include "db.h"
#include "sqlite3.h"
#include "user.h"
#include "web_server/server.h"

// TODO: Check if daemon is already installed
// Get upto-date version from github
// Connect to SQLite

// Rename smh
void db_testing() {
    sqlite3* db = connect_db();
    node* head = get_users(db);
    sqlite3_close(db);
}

int main() {
    db_testing();
    run_server();
    return 0;
}
