#include "main.h"
#include "db.h"
#include "user.h"
#include "sqlite3.h"
#include "web_server/server.c"

// TODO: Check if daemon is already installed
// Get upto-date version from github
// Connect to SQLite

int main() {
    run_server();
    return 0;
}
