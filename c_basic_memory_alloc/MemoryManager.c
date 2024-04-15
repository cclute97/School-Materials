#include <stdio.h>
#include <stdlib.h>

/**
 * Compares two numbers and returns a positive integer, 0 or 
 * a negative integer if the first number is greater than, equal to
 * or less than the second number.
 * Assumes the numbers are of the type int.
 * Used when invoking the quicksort function.  
 */
int compare (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}


/**
 * Takes in an array of integers and the number of elements in the array 
 * as arguments.
 * Then it will sort and return the median of the sorted array. 
 * To keep things simple, it always returns
 * the element at index arr_size/2 even though the 
 * array size is even.
 */
int return_median(int *arr, int size)
{
   qsort(arr, size, sizeof(int), compare);
   return arr[size/2];
}


/**
 * Takes in a random number and maps it to the
 * range [100000 - 120000)
 */
int get_iteration_count(int rand)
{
    return (rand % 20000) + 100000;     
}

/**
 * Takes in a random number and maps it to the 
 * range [1000 - 1500)
 */
int get_arr_size(int rand)
{
    return (rand % 500) + 1000;
}

void print_num_iterations(int num_iterations) {
    printf("[MemoryManager] Number of Iterations: %d\n", num_iterations);
}

void print_malloc_error() {
    printf("Memory for the array could not be allocated in the heap.\n");
}

/**
 * This is the method that you need to implement.
 * Implement the following steps in the given order.
 *
 *  1. Generate the number of iterations
 *      - Generate a random number. Map it to the range [100000 - 120000) using the 
 *      utility function 'get_iteration_count'.
 * 
 * 2. For each iteration:
 *      2.a Generate an array size - Generate a random number and map it to the range [1000 - 1500) using
 *          the utility function 'get_arr_size'.
 * 
 *      2.b Allocate memory for the array in the heap.
 *
 *      2.c Populate the array with random numbers.
 *
 *      2.d Get the median of the array using the function 'return_median'.
 *
 *      2.e Check if the median is divisible by 13.
 *
 *      2.f Return the number of medians that were divisible by 13.
 *
 */
int get_running_count()
{
    // TODO: Implement this method.
    int num_median_elements_divisible_13 = 0;
    int num_iterations = get_iteration_count(rand());
    int array_size;
    int *array_in_heap;

    print_num_iterations(num_iterations);

    for (int i = 0; i < num_iterations; i++) {
        array_size = get_arr_size(rand());
        array_in_heap = malloc(array_size * sizeof(int));

        if (array_in_heap == NULL) {
            print_malloc_error();
            return -1;
        }

        for (int j = 0; j < array_size; j++ ) {
            array_in_heap[j] = rand();
        }

        if (return_median(array_in_heap, array_size) % 13 == 0) {
            num_median_elements_divisible_13++;
        }

        free(array_in_heap);
    }

    return num_median_elements_divisible_13;
}
