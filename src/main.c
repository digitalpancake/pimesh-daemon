#include "main.h"
#include "db.h"
#include "user.h"
#include "sqlite3.h"
#include "web_server/server.h"
#include <stdio.h>

// TODO: Check if daemon is already installed
// Get upto-date version from github
// Connect to SQLite

int main() {
    sqlite3* db = connect_db();
    node* head = dbquery(db, "select * from Users", USER);

    if(head == NULL) {
        printf("NULL\n");
    }

    sqlite3_close(db);
    return 0;
}
