#include <stdio.h>
#include "hashmap.h"
#include "heap.h"

#define LOW_STOCK_THRESHOLD 10

void processRestock(int pid, int loc, int qty) {
    Product* p = findProduct(pid, loc);
    if (!p) return;

    p->quantity += qty;
    if (p->quantity > p->max_capacity) {
        printf("Overstock: %s\n", p->name);
        p->quantity = p->max_capacity;
    }
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
}