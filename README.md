# CS Project : Recreate the Heap Function in C

This documentation outlines the implementation details and usage of our custom memory allocation functions: mymalloc(), myfree(), myrealloc(), and mycalloc(). These functions are designed to allocate memory on the heap of a program using the brk(2) and sbrk(2) system calls.
### Prerequisites
GCC (GNU Compiler Collection) installed on your system.
### Compilation
To compile the program, follow these steps:
1. Open a terminal window.
2. Navigate to the directory containing the source code files main.c and heap.c.
3. Compile the source files to object files:

   gcc -c main.c -o main.o
   
   gcc -c heap.c -o heap.o
5. Link the object files to create the executable:

   gcc main.o heap.o -o my_program
### Execution
To run the program, use the following command:
./my_program
### Cleanup
rm main.o heap.o my_program

### Special steps to use shared library (currently only for linux users)
1. Navigate to Struct2
2. Run the command to compile and install the shared library "lib_my_malloc.so" into /usr/local/lib, super user password is required
   use following command:

   make

   make install

for testing:

3. There is a test program in the folder also(test_program.c), complie it in ordinary way, but special parament required:

gcc -o test_program test_program.c -l_my_malloc

4. run the program to see the result if it is like this:
   Initial memory map:
Memory Blocks:
Memory map after malloc for array:
Memory Blocks:
Block at 0x55763c3b0000, size: 160, free: 0
Memory map after calloc for array_calloc:
Memory Blocks:
Block at 0x55763c3b0000, size: 160, free: 0
Block at 0x55763c3b00b8, size: 112, free: 0
Memory map after realloc for array:
Memory Blocks:
Block at 0x55763c3b0000, size: 80, free: 0
Block at 0x55763c3b0068, size: 56, free: 1
Block at 0x55763c3b00b8, size: 112, free: 0
Memory map after free for array:
Memory Blocks:
Block at 0x55763c3b0000, size: 160, free: 1
Block at 0x55763c3b00b8, size: 112, free: 0
Memory map after free for array_calloc:
Memory Blocks:
Block at 0x55763c3b0000, size: 160, free: 1
Block at 0x55763c3b00b8, size: 112, free: 1

5. to clean up:
Navigate to /usr/local/lib, and delete lib_my_malloc.so ( super user permission needed), delete all other files in the downloaded folder.

### Theory explanation 
In computer memory management, the Random Access Memory (RAM) is divided into two essential components: the stack and the heap. The stack is a dedicated portion of memory primarily responsible for handling function calls and managing local variables. Whenever a function is invoked, a new stack frame is created, encompassing space for local variables, function parameters, and return addresses. The stack operates on a Last In, First Out (LIFO) basis, meaning that the most recently added item is the first to be removed. While the stack is efficient for managing function-related data, exclusively relying on it can lead to memory inefficiency.

To address this limitation, C provides the heap, a more versatile region of memory designed for dynamic memory allocation. The heap allows for on-the-fly memory requests during program execution, offering flexibility in managing memory resources. Unlike the stack, the heap requires explicit allocation and deallocation of memory by the programmer and does not adhere to a strict LIFO order. Generally, the heap has a larger size compared to the stack, and programs can dynamically request memory as needed. However, accessing data on the heap typically involves more intricate memory management processes, resulting in slower performance compared to the stack. 

In C, to manage the memory with dynamic allocation, there are these main functions from the <unistd.h> library:
1. malloc: Stands for "memory allocation", it is used to dynamically allocate memory on the heap during the execution. It returns a pointer of type void which can be cast into a pointer of any form. Syntax: int *numPtr = (int *)malloc(sizeof(int));
2. calloc: Stands for "contiguous allocation", it is used to dynamically allocate a specified number of blocks of memory, each with a specified number of bytes, and is initialized it to zero. Syntax: void* calloc(size_t num_elements, size_t element_size);
3. realloc: Stands for "reallocate", it is used to resize a previously allocated block of memory. It takes a pointer to a block of memory previously allocated with malloc, calloc, or realloc, and changes the size of that block. If the size is increased, the content of the previously allocated memory is preserved up to the minimum of the old and new sizes. If the size is decreased, the excess memory at the end of the block is released. Syntax: void* realloc(void* ptr, size_t new_size);
4. free: It is used to deallocate memory that was previously allocated using functions like malloc, calloc, or realloc. It helps in releasing the memory back to the system so that it can be used for other purposes. Syntax: free(variable);

To understand how these functions work, we made them using the sbrk(2) and brk(2) system calls as it is shown in the schematics:

![image](https://github.com/ElessarWillomoont/Memory_Management_S2P1/assets/157610130/610a67ff-e550-4fa6-9263-6cebe4f46fda)

The process that we follow to make our malloc function was to use the brk(2) system call sets the end of the data segment to the specified value, effectively changing the program's break. It increments the program's data space by the specified number of bytes, allowing us to allocate the data in an specific PID.
