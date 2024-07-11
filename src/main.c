#include "main.h"

int main() {
    while(1) {
        int err = run_daemon();
        if (err != 0) {
            return err;
        }
    }
    return 0;
}

int run_daemon() {
    return 0;
}

