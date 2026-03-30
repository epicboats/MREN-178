#include <stdio.h>
#include "hashmap.h"
#include "heap.h"
#include "fileio.h"
#include "cli.h"


int main() {
    for (int i = 0; i < TABLE_SIZE; i++)
        hashTable[i] = NULL;

    heap.size = 0;

    loadProducts("C:\\Users\\junon\\OneDrive\\Documents\\MREN178\\data\\products.txt");
    loadTransactions("C:\\Users\\junon\\OneDrive\\Documents\\MREN178\\data\\transactions.txt");

    commandLineInterface();

    return 0;
}