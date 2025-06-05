#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

#define N 1000000  // Reduït per fer més evident el problema
#define MAX_THREADS 16

static int globalVar = 0;

static int TestThread(void *data) {
    int thread_id = *(int*)data;
    printf("Thread %d started, will increment %d times\n", thread_id, N);
    
    for (int i = 0; i < N; i++) {
        globalVar++; // Critical region - PROBLEM AQUÍ!
    }
    
    printf("Thread %d finished\n", thread_id);
    return N;
}

int shared_inc_multi(int argc, char *argv[]) {
    int numThreads;
    
    printf("Enter number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &numThreads);
    
    if (numThreads < 1 || numThreads > MAX_THREADS) {
        printf("Invalid number of threads. Using 1.\n");
        numThreads = 1;
    }
    
    int expectedValue = numThreads * N;
    printf("\nShared memory increment test:\n");
    printf("Number of threads: %d\n", numThreads);
    printf("Increments per thread: %d\n", N);
    printf("Expected final value: %d\n\n", expectedValue);
    
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    
    SDL_Thread* threads[MAX_THREADS];
    int threadIds[MAX_THREADS];
    
    // Reset global variable
    globalVar = 0;
    
    // Create threads
    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i;
        char threadName[32];
        sprintf(threadName, "TestThread%d", i);
        
        threads[i] = SDL_CreateThread(TestThread, threadName, &threadIds[i]);
        if (threads[i] == NULL) {
            printf("SDL_CreateThread failed for thread %d: %s\n", i, SDL_GetError());
            return -1;
        }
    }
    
    // Wait for all threads
    printf("Waiting for all threads to finish...\n");
    for (int i = 0; i < numThreads; i++) {
        int threadReturnValue;
        SDL_WaitThread(threads[i], &threadReturnValue);
        printf("Thread %d returned: %d\n", i, threadReturnValue);
    }
    
    printf("\nResults:\n");
    printf("Expected value: %d\n", expectedValue);
    printf("Actual value:   %d\n", globalVar);
    printf("Difference:     %d\n", expectedValue - globalVar);
    
    if (globalVar == expectedValue) {
        printf("Result is correct!\n");
    } else {
        printf("Result is incorrect! Race condition detected!\n");
        printf("Lost increments: %d (%.2f%%)\n", 
               expectedValue - globalVar, 
               100.0 * (expectedValue - globalVar) / expectedValue);
    }
    
    SDL_Quit();
    return 0;
}