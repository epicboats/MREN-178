#include <stdio.h>
#include <string.h>
#include "hashmap.h"
#include "transactions.h"

void loadProducts(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error opening products file\n");
        return;
    }

    int pid, loc, qty, max;
    char name[50];

    while (fscanf(f, "%d %s %d %d %d", &pid, name, &loc, &qty, &max) != EOF) {
        insertProduct(pid, name, loc, qty, max);
    }

    fclose(f);
}

void loadTransactions(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Error opening transactions file\n");
        return;
    }

    char type[20];
    int pid, loc1, loc2, qty;

    while (fscanf(f, "%s", type) != EOF) {

        if (strcmp(type, "RESTOCK") == 0) {
            fscanf(f, "%d %d %d", &pid, &loc1, &qty);
            processRestock(pid, loc1, qty);
        }
        else if (strcmp(type, "SHIP") == 0) {
            fscanf(f, "%d %d %d", &pid, &loc1, &qty);
            processShip(pid, loc1, qty);
        }
        else if (strcmp(type, "TRANSFER") == 0) {
            fscanf(f, "%d %d %d %d", &pid, &loc1, &loc2, &qty);
            processTransfer(pid, loc1, loc2, qty);
        }
    }

    fclose(f);
}

void saveProducts(const char* filename) {
    FILE* f = fopen(filename, "w");

    if (!f) {
        printf("Error saving products file\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Product* temp = hashTable[i];

        while (temp) {
            fprintf(f, "%d %s %d %d %d\n",
                    temp->product_id,
                    temp->name,
                    temp->location_id,
                    temp->quantity,
                    temp->max_capacity);

            temp = temp->next;
        }
    }

    fclose(f);
    printf("Data saved to file.\n");
}
