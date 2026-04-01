#include <stdio.h>
#include <string.h>
#include "hashmap.h"
#include "transactions.h"
#include "heap.h"

void commandLineInterface() {
    char command[50];

    printf("\nInventory CLI\n");

    while (1) {
        printf("\n> ");
        scanf("%s", command);

        if (strcmp(command, "VIEW") == 0) {
            int pid, loc;
            char at[10];

            scanf("%d %s %d", &pid, at, &loc);

            Product* p = findProduct(pid, loc);
            if (p)
                printf("Product: %s  Qty: %d  Location: %d\n",
                       p->name, p->quantity, p->location_id);
            else
                printf("Product not found\n");
        }

        else if (strcmp(command, "ADD") == 0) {
            int qty, pid, loc;
            char to[10], at[10];

            scanf("%d %s %d %s %d", &qty, to, &pid, at, &loc);
            processRestock(pid, loc, qty);
        }

        else if (strcmp(command, "REMOVE") == 0) {
            int qty, pid, loc;
            char from[10], at[10];

            scanf("%d %s %d %s %d", &qty, from, &pid, at, &loc);
            processShip(pid, loc, qty);
        }

        else if (strcmp(command, "MOVE") == 0) {
            int qty, pid, fromLoc, toLoc;
            char of[10], from[10], to[10];

            scanf("%d %s %d %s %d %s %d",
                  &qty, of, &pid, from, &fromLoc, to, &toLoc);

            processTransfer(pid, fromLoc, toLoc, qty);
        }

        else if (strcmp(command, "SHOW") == 0) {
            char sub[20];
            scanf("%s", sub);

            if (strcmp(sub, "ALL") == 0)
                printInventory();
            else if (strcmp(sub, "LOW") == 0)
                restockRecommendations();
        }

        else if (strcmp(command, "CREATE") == 0) {
            char type[20];
            scanf("%s", type);

            if (strcmp(type, "PRODUCT") == 0) {
                int pid, max;
                char name[50];

                scanf("%d %s %d", &pid, name, &max);
                createProductType(pid, name, max);
            }

            else if (strcmp(type, "LOCATION") == 0) {
                int loc;
                scanf("%d", &loc);

                createLocation(loc);
            }
            else {
                printf("Invalid CREATE type\n");
            }
        }

    else if (strcmp(command, "STOCK") == 0) {
        int pid, loc, qty;
        char at[10], with[10];
        char name[50] = "NewItem";

        scanf("%d %s %d %s %d", &pid, at, &loc, with, &qty);

        stockProduct(pid, loc, qty, 100, name);
    }

        else if (strcmp(command, "EXIT") == 0) {
            saveProducts("C:\\Users\\junon\\OneDrive\\Documents\\MREN178\\data\\products.txt");
            printf("Exiting and saving data...\n");
            break;
        }

        else {
            printf("Invalid command\n");
        }
    }
}
