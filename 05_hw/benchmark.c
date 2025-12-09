#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

void benchmark_push(int num_operations) {
    Stack stack;
    initStack(&stack);
    
    clock_t start_time = clock();

    for (int i = 0; i < num_operations; ++i) {
        push(&stack, i); 
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Push: Num of operations: %d, took %.6f seconds\n", num_operations, elapsed_time);
    
    destroyStack(&stack);
}

void benchmark_pop(int num_operations) {
    Stack stack;
    initStack(&stack);  
    
    for (int i = 0; i < num_operations; ++i) {
        push(&stack, i); 
    }

    clock_t start_time = clock();

    for (int i = 0; i < num_operations; ++i) {
        pop(&stack); 
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Pop:  Num of operations: %d, took %.6f seconds\n", num_operations, elapsed_time);
    
    destroyStack(&stack);  
}


int main() {
    
    int test_sizes[] = {1000, 10000, 100000, 1000000};
    int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    
    for (int i = 0; i < num_tests; ++i) {
        int size = test_sizes[i];
        printf("Testing with %d operations:\n", size);
        
        benchmark_push(size);
        benchmark_pop(size);
        
        printf("\n");
    }

    return 0;
}