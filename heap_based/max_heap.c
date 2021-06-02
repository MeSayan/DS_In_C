#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LEFT(i) i << 1
#define RIGHT(i) ((i << 1) | 1)
#define PARENT(i) i >> 1
#define LEN(A) sizeof(A)/sizeof(A[0])

// O(height of heap) = O(log heap_size)
void max_heapify(int A[], int i, int heap_size) {
    // A[1..heap_size] is the heap
    int largest = i;
    if (LEFT(i) <= heap_size && A[LEFT(i)] > A[largest])
        largest = LEFT(i);

    if (RIGHT(i) <= heap_size && A[RIGHT(i)] > A[largest])
        largest = RIGHT(i);
    
    if (largest != i) {
        int t = A[largest];
        A[largest] = A[i];
        A[i] = t;
        max_heapify(A, largest, heap_size);
    }
}

// Tight bound ? O(heap_size)
void heapify(int A[], int heap_size) {
    // A[1..heap_size] is heap
    // heap_size / 2 + 1 element onwards are leaf nodes
    for (int i= heap_size / 2; i > 0; --i)
        max_heapify(A, i, heap_size);
}


void heap_sort(int A[], int heap_size) {
    // remove top from heap successively, move in correct position in A 
    while (heap_size > 1) {
        int t = A[1];
        A[1] = A[heap_size];
        A[heap_size] = t;
        heap_size -= 1;
        max_heapify(A, 1, heap_size);
    }
}


int main(int argc, char * argv) {
    int A[] = {0,1,4,2,6,3,5};
    heapify(A, 6);
    for (int i = 0; i < 7; ++i)
        printf("%d ", A[i]);
    printf("\n");

    heap_sort(A, 6);
    for (int i = 0; i < 7; ++i)
        printf("%d ", A[i]);
    printf("\n");

    return 0;
}