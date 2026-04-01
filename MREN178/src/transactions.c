#include <stdio.h>
#include "hashmap.h"
#include "heap.h"

#define LOW_STOCK_THRESHOLD 10

#define MAX_LOGS 200000

char transactionLog[MAX_LOGS][100];
int logCount = 0;

void processRestock(int pid, int loc, int qty) {
    Product* p = findProduct(pid, loc);
    if (!p) return;

    p->quantity += qty;
    if (p->quantity > p->max_capacity) {
        printf("Overstock: %s\n", p->name);
        p->quantity = p->max_capacity;
    }
    char logEntry[100];
    sprintf(logEntry, "RESTOCK %d %d %d", pid, loc, qty);
    logTransaction(logEntry);
}

void processShip(int pid, int loc, int qty) {
    Product* p = findProduct(pid, loc);
    if (!p) return;

    if (p->quantity >= qty)
        p->quantity -= qty;
    else {
        printf("Shortage: %s\n", p->name);
        p->quantity = 0;
    }

    if (p->quantity < LOW_STOCK_THRESHOLD)
        heapInsert(p);
    
    char logEntry[100];
    sprintf(logEntry, "SHIP %d %d %d", pid, loc, qty);
    logTransaction(logEntry);
}

void processTransfer(int pid, int from, int to, int qty) {
    Product* src = findProduct(pid, from);
    Product* dest = findProduct(pid, to);

    if (!src || !dest) return;

    if (src->quantity >= qty) {
        src->quantity -= qty;
        dest->quantity += qty;
    } else {
        printf("Transfer shortage\n");
    }
    char logEntry[100];
    sprintf(logEntry, "TRANSFER %d %d %d %d", pid, from, to, qty);
    logTransaction(logEntry);
}

void logTransaction(const char* entry) {
    if (logCount < MAX_LOGS) {
        strcpy(transactionLog[logCount++], entry);
    }
}

void saveTransactionLog(const char* filename) {
    FILE* f = fopen(filename, "a");

    if (!f) {
        printf("Error saving transactions file\n");
        return;
    }

    for (int i = 0; i < logCount; i++) {
        fprintf(f, "%s\n", transactionLog[i]);
    }

    fclose(f);
    printf("Transactions appended to file.\n");

    logCount = 0;
}
