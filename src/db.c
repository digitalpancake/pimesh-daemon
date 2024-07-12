#include <stdio.h>
#include <stdlib.h>

#include "db.h"
#include "sqlite3.h"
#include "user.h"

#define DB_NAME "mesh_db.db"

sqlite3* connect_db() {
    sqlite3* db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }

    return db;
}

int get_users_callback(void* ptr_head, int argc, char** argv,
                       char** azColName) {
    node** head = (node**)ptr_head;
    User* u = (User*)malloc(sizeof(User));

    u->id = atoi(argv[0]);
    u->name = argv[1];
    u->username = argv[2];

    if (*head == NULL) {
        *head = (node*)malloc(sizeof(node));
        (*head)->data = u;
        (*head)->next = NULL;
    } else {
        node* ll_pointer = *head;
        while (ll_pointer->next != NULL) {
            ll_pointer = ll_pointer->next;
        }
        node* next_node = (node*)malloc(sizeof(node));
        next_node->data = u;
        next_node->next = NULL;
        ll_pointer->next = next_node;
    }

    // printf("Assigned ll_pointer to data %s\n", u->username);

    return 0;
}

node* get_users(sqlite3* db) {
    node* head = NULL;

    char* sql = "select * from Users";

    char* z_err_msg;
    int rc = sqlite3_exec(db, sql, get_users_callback, (void*)&head, &z_err_msg);

    if (rc != SQLITE_OK) {
        sqlite3_free(z_err_msg);
    }

    return head;
}
