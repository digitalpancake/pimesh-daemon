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

typedef struct {
        node* head;
        DB_TYPE type;
} dbresult_t;

int dbselect_callback(void* payload, int argc, char** argv, char** azColName) {
    dbresult_t* dbresult = (dbresult_t*)payload;

    if (dbresult->type == USER) {
        User* u = (User*)malloc(sizeof(User));
        u->id = atoi(argv[0]);
        u->name = argv[1];
        u->username = argv[2];
        printf("Found User: %s\n", u->username);
        node* new_node = (node*)malloc(sizeof(node));
        new_node->data = u;
        new_node->next = NULL;

        if (dbresult->head == NULL) {
            dbresult->head = new_node;
        } else {
            node* current = dbresult->head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    return 0;
}

node* dbquery(sqlite3* db, char* query, DB_TYPE db_type) {
    dbresult_t* dbresult = (dbresult_t*)calloc(1, sizeof(dbresult_t));
    dbresult->head = NULL;
    dbresult->type = db_type;

    char* z_err_msg;
    int rc = sqlite3_exec(db, query, dbselect_callback, dbresult, &z_err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", z_err_msg);
        sqlite3_free(z_err_msg);
    }

    return dbresult->head;
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

    return 0;
}

node* get_users(sqlite3* db) {
    node* head = NULL;

    char* sql = "select * from Users";

    char* z_err_msg;
    int rc =
        sqlite3_exec(db, sql, get_users_callback, (void*)&head, &z_err_msg);

    if (rc != SQLITE_OK) {
        sqlite3_free(z_err_msg);
    }

    return head;
}
