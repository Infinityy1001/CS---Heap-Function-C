#include <stdio.h>
#include "heap.h"

int main() {
    // Initialization of the heap and stack_base
    stack_base = (const uintptr_t*)__builtin_frame_address(0);

    // Memory allocation using heap_alloc
    int *ptr1 = (int*)heap_alloc(sizeof(int));
    *ptr1 = 42;

    // Memory allocation using heap_calloc
    int *ptr2 = (int*)heap_calloc(5, sizeof(int));
    // Memory allocated by heap_calloc is initialized to zero
    for (int i = 0; i < 5; ++i) {
        printf("%d ", ptr2[i]);  // Should print "0 0 0 0 0 "
    }
    printf("\n");

    // Memory reallocation using heap_realloc
    ptr2 = (int*)heap_realloc(ptr2, 10 * sizeof(int));
    // The newly allocated memory by heap_realloc is not initialized
    for (int i = 0; i < 10; ++i) {
        printf("%d ", ptr2[i]);  // Values can be unpredictable
    }
    printf("\n");

    // Memory deallocation using heap_free
    heap_free(ptr1);
    heap_free(ptr2);

    // Collection of unused memory
    heap_collect();

    // Display information about allocated chunks
    chunk_list_dump(&alloced_chunks, "Allocated");
    chunk_list_dump(&freed_chunks, "Freed");

    return 0;
}
