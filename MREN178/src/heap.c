#include <stdio.h>
#include "heap.h"

MinHeap heap;

void swap(Product** a, Product** b) {
    Product* t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(int i) {
    while (i > 0 && heap.arr[i]->quantity < heap.arr[(i - 1)/2]->quantity) {
        swap(&heap.arr[i], &heap.arr[(i - 1)/2]);
        i = (i - 1)/2;
    }
}

void heapifyDown(int i) {
    int smallest = i;
    int l = 2*i + 1, r = 2*i + 2;

    if (l < heap.size && heap.arr[l]->quantity < heap.arr[smallest]->quantity)
        smallest = l;

    if (r < heap.size && heap.arr[r]->quantity < heap.arr[smallest]->quantity)
        smallest = r;

    if (smallest != i) {
        swap(&heap.arr[i], &heap.arr[smallest]);
        heapifyDown(smallest);
    }
}

void heapInsert(Product* p) {
    heap.arr[heap.size] = p;
    heapifyUp(heap.size++);
}

Product* extractMin() {
    if (heap.size == 0) return NULL;

    Product* root = heap.arr[0];
    heap.arr[0] = heap.arr[--heap.size];
    heapifyDown(0);

    return root;
}

void restockRecommendations() {
    printf("\nRestock Priority\n");

    while (heap.size > 0) {
        Product* p = extractMin();
        printf("%s (Loc %d) Qty:%d\n",
               p->name, p->location_id, p->quantity);
    }
}
