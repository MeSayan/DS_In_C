#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)
#define PARENT(x) (x >> 1)


#define HEAP_SIZE 10000
#define HEAP_UNDERFLOW_ERROR -666
#define HEAP_INVALID_KEY_ERROR -777


typedef struct heap {
    int A[HEAP_SIZE];
    int heap_size;
} heap;



void max_heapify(heap * h, int i) {
    int largest = i;
    if (LEFT(i) <= h->heap_size && h->A[LEFT(i)] > h->A[largest])
        largest = LEFT(i);
    if (RIGHT(i) <= h->heap_size && h->A[RIGHT(i)] > h->A[largest])
        largest = RIGHT(i);
    if (largest != i) {
        int t = h->A[i];
        h->A[i] = h->A[largest];
        h->A[largest] = t;
        max_heapify(h, largest);
    }
}

void heapify(heap * h) {
    int heap_size = h->heap_size;
    for (int i = heap_size / 2; i > 0; --i)
        max_heapify(h, i);
}

int maximum(heap * h) {
    return h->A[1];
}

int extract_max(heap * h) {
    if(h->heap_size < 1)
        return HEAP_UNDERFLOW_ERROR;
    int max = h->A[1];
    h->A[1] = h->A[h->heap_size];
    h->heap_size -= 1;
    max_heapify(h, 1);
    return max;
}

int increase_key(heap * h, int i, int key) {
    if (key < h->A[i])
        return HEAP_INVALID_KEY_ERROR;
    h->A[i] = key;
    while (i > 1 && h->A[PARENT(i)] < h->A[i]) {
        int t = h->A[i];
        h->A[i] = h->A[PARENT(i)];
        h->A[PARENT(i)] = t;
        i = PARENT(i);
    }
    return 0;
}

void insert(heap * h, int key) {
    h->A[h->heap_size+1] =  INT_MIN;
    h->heap_size += 1;
    increase_key(h, h->heap_size, key);
}


void print_heap(heap * h) {
    printf("Heap: [ ");
    for (int i= 1; i <= h->heap_size; ++i) 
        printf("%d ", h->A[i]);
    printf("]\n");
}


int main(int argc, char * argv) {
    heap h;
    h.heap_size = 0;
    int initial_data[] = {1,2,4,6,9,3,7,8,5};
    for(int i = 0; i < 9; ++i) {
        h.A[i+1] = initial_data[i];
        h.heap_size += 1;
    }

    heapify(&h);
    print_heap(&h);
    printf("Maximum in heap %d\n", maximum(&h));
    printf("Increase key at poisition %d\n", 9);
    increase_key(&h, 9, 11);
    printf("Maximum in heap after increase key %d\n", maximum(&h));
    print_heap(&h);
    printf("Removing max from heap\n");
    extract_max(&h);
    print_heap(&h);
    printf("Inserting 12, 15, 13\n");
    insert(&h, 12);
    insert(&h, 15);
    insert(&h, 13);
    print_heap(&h);

    return 0;

}    
