#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

int productExists[MAX_PRODUCTS] = {0};
int locationExists[MAX_LOCATIONS] = {0};

Product* hashTable[TABLE_SIZE];

int hash(int pid, int loc) {
    return (pid * 31 + loc) % TABLE_SIZE;
}

Product* createProduct(int pid, char* name, int loc, int qty, int max) {
    Product* p = malloc(sizeof(Product));
    p->product_id = pid;
    p->location_id = loc;
    strcpy(p->name, name);
    p->quantity = qty;
    p->max_capacity = max;
    p->next = NULL;
    return p;
}

void insertProduct(int pid, char* name, int loc, int qty, int max) {
    int idx = hash(pid, loc);
    Product* p = createProduct(pid, name, loc, qty, max);

    p->next = hashTable[idx];
    hashTable[idx] = p;
}

Product* findProduct(int pid, int loc) {
    int idx = hash(pid, loc);
    Product* temp = hashTable[idx];

    while (temp) {
        if (temp->product_id == pid && temp->location_id == loc)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void printInventory() {
    printf("\n--- Inventory ---\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        Product* temp = hashTable[i];
        while (temp) {
            printf("PID:%d Loc:%d Name:%s Qty:%d\n",
                   temp->product_id,
                   temp->location_id,
                   temp->name,
                   temp->quantity);
            temp = temp->next;
        }
    }
}

void createProductType(int pid, char* name, int max_capacity) {
    if (productExists[pid]) {
        printf("Product already exists\n");
        return;
    }

    productExists[pid] = 1;
    printf("Created product type: %s (ID %d)\n", name, pid);
}

void createLocation(int loc) {
    if (locationExists[loc]) {
        printf("Location already exists\n");
        return;
    }

    locationExists[loc] = 1;
    printf("Created location: %d\n", loc);
}

void stockProduct(int pid, int loc, int qty, int max_capacity, char* name) {
    if (!productExists[pid]) {
        printf("Product type does not exist\n");
        return;
    }

    if (!locationExists[loc]) {
        printf("Location does not exist\n");
        return;
    }

    Product* p = findProduct(pid, loc);

    if (!p) {
        insertProduct(pid, name, loc, qty, max_capacity);
    } else {
        p->quantity += qty;
    }

    printf("Stocked product %d at location %d\n", pid, loc);
}