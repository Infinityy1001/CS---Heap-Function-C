#include <stdio.h>
#include <string.h>
#include "heap_lib.h"

int main() {
    printf("Initial memory map:\n");
    print_memory_map();

    // Dynamic memory allocation using custom malloc function
    int *array = (int*)my_malloc(40 * sizeof(int));
    printf("Memory map after malloc for array:\n");
    print_memory_map();

    // Allocating memory using custom calloc function
    int *array_calloc = (int*)my_calloc(25, sizeof(int));
    printf("Memory map after calloc for array_calloc:\n");
    print_memory_map();

    // Reallocating memory using custom realloc function
    array = (int*)my_realloc(array, 20 * sizeof(int));
    printf("Memory map after realloc for array:\n");
    print_memory_map();

    // Freeing memory using custom free function
    my_free(array);
    printf("Memory map after free for array:\n");
    print_memory_map();

    // Freeing memory allocated by calloc
    my_free(array_calloc);
    printf("Memory map after free for array_calloc:\n");
    print_memory_map();

    return 0;
}