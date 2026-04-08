#include "hashmap.h"

typedef struct {
    Product* arr[200000];
    int size;
} MinHeap;

extern MinHeap heap;

void heapInsert(Product* p);
Product* extractMin();
void restockRecommendations();
