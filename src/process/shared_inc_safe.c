#include <stdio.h>
#include <SDL3/SDL.h>
#include <stdlib.h>

#define N 1000000
#define MAX_THREADS 16

static int globalVar = 0;
SDL_Mutex* mutex = NULL;  // Mutex per protegir la variable global

typedef struct {
    int thread_id;
    int increments;
} ThreadData;

static int TestThread(void *data) {
    ThreadData* threadData = (ThreadData*)data;
    printf("Thread %d started, will increment %d times\n", 
           threadData->thread_id, threadData->increments);
    
    for (int i = 0; i < threadData->increments; i++) {
        // CRITICAL SECTION START
        SDL_LockMutex(mutex);     // Lock mutex
        globalVar++;              // Protected increment
        SDL_UnlockMutex(mutex);   // Unlock mutex
        // CRITICAL SECTION END
    }
    
    printf("Thread %d finished\n", threadData->thread_id);
    return threadData->increments;
}

int shared_inc_safe(int argc, char *argv[]) {
    int numThreads;
    
    printf("Enter number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &numThreads);
    
    if (numThreads < 1 || numThreads > MAX_THREADS) {
        printf("Invalid number of threads. Using 1.\n");
        numThreads = 1;
    }
    
    int expectedValue = numThreads * N;
    printf("\nThread-safe shared memory increment test:\n");
    printf("Number of threads: %d\n", numThreads);
    printf("Increments per thread: %d\n", N);
    printf("Expected final value: %d\n\n", expectedValue);
    
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    
    // Create mutex
    mutex = SDL_CreateMutex();
    if (mutex == NULL) {
        printf("SDL_CreateMutex failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    
    SDL_Thread* threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];
    
    // Reset global variable
    globalVar = 0;
    
    // Create threads
    for (int i = 0; i < numThreads; i++) {
        threadData[i].thread_id = i;
        threadData[i].increments = N;
        
        char threadName[32];
        sprintf(threadName, "TestThread%d", i);
        
        threads[i] = SDL_CreateThread(TestThread, threadName, &threadData[i]);
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
        printf("✓ Result is correct! Mutex protection worked!\n");
    } else {
        printf("✗ Result is still incorrect! Something went wrong!\n");
    }
    
    // Cleanup
    SDL_DestroyMutex(mutex);
    SDL_Quit();
    return 0;
}