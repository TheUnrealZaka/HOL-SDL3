#include <stdio.h>
#include <SDL3/SDL.h>

#define N 10000000
static int globalVar = 0;

static int TestThread(void *data) {
    printf("Thread started, will increment %d times\n", N);
    
    for (int i = 0; i < N; i++) {
        globalVar++; // Critical region
    }
    
    printf("Thread finished\n");
    return N; // Return number of increments performed
}

int shared_inc(int argc, char *argv[]) {
    SDL_Thread *thread;
    int threadReturnValue;

    printf("Simple SDL_CreateThread test:\n");
    printf("Expected final value: %d\n\n", N);
    
    // Initialize SDL (required for thread functions)
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    
    thread = SDL_CreateThread(TestThread, "TestThread", NULL);
    if (thread == NULL) {
        printf("SDL_CreateThread failed: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_WaitThread(thread, &threadReturnValue);
    printf("Thread returned value: %d\n", threadReturnValue);
    printf("Final globalVar value: %d\n", globalVar);
    
    if (globalVar == N) {
        printf("Result is correct!\n");
    } else {
        printf("Result is incorrect! Expected %d, got %d\n", N, globalVar);
    }
    
    SDL_Quit();
    return 0;
}