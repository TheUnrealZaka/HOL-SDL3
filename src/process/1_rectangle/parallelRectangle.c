#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Screen size
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

/* SDL main objects */
static SDL_Window*   window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Surface* screenSurface = NULL;

/* 'Game' related variables */
#define MAXR 1000  // Increase this for better testing with multiple threads
SDL_Rect r[MAXR];
static bool quit = false;
static int frames = 0;
static SDL_Mutex* frameMutex = NULL;  // Mutex to protect frames counter
static SDL_Mutex* rectMutex = NULL;  // Mutex to protect rectangle array

// Thread data structure
typedef struct {
    int start;    // Starting index in the array
    int count;    // Number of rectangles to process
    int threadId; // Thread identifier for debugging
} ThreadData;

static bool initializeSDL();
static void updateRect(int start, int iters);
static void move(SDL_Rect *rect);

// Thread function for updating rectangles
static int updateRectThread(void* data) {
    ThreadData* threadData = (ThreadData*)data;
    int start = threadData->start;
    int count = threadData->count;
    int threadId = threadData->threadId;
    
    printf("Thread %d: Processing rectangles %d to %d\n", threadId, start, start + count - 1);
    
    while (!quit) {
        // Lock before modifying rectangles
        SDL_LockMutex(rectMutex);
        for (int i = 0; i < count; i++) {
            move(&r[start + i]);
        }
        SDL_UnlockMutex(rectMutex);
        
        SDL_Delay(1);
    }
    
    printf("Thread %d: Exiting\n", threadId);
    return 0;
}

// Rendering thread - separate from calculation threads
static int renderThread(void* data) {
    while (!quit) {
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        // Lock before reading rectangles
        SDL_LockMutex(rectMutex);
        for (int i = 0; i < MAXR; i++) {
            SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
            SDL_Rect rect = { r[i].x, r[i].y, r[i].w, r[i].h };
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_UnlockMutex(rectMutex);
        
        SDL_RenderPresent(renderer);
        
        // Safely increment frame counter
        SDL_LockMutex(frameMutex);
        frames++;
        SDL_UnlockMutex(frameMutex);
    }
    return 0;
}

int parallelRectangle(int argc, char** argv) {
    if (!initializeSDL()) return (-1);

    printf(" ** Starting Parallel Rectangle Program\n");
    
    // Ask user for number of threads
    int numThreads;
    printf("Enter number of computation threads to create (recommended: 2, 4, 8, 16, 32): ");
    if (scanf("%d", &numThreads) != 1) {
        printf("Invalid input. Using 2 threads.\n");
        numThreads = 2;
    }
    
    if (numThreads <= 0 || numThreads > MAXR) {
        printf("Invalid number of threads. Using 2 threads.\n");
        numThreads = 2;
    }

    // Create mutex for frame counter
    frameMutex = SDL_CreateMutex();
    if (!frameMutex) {
        printf("Failed to create mutex: %s\n", SDL_GetError());
        return -1;
    }

    // Create mutex for rectangle array protection
    rectMutex = SDL_CreateMutex();
    if (!rectMutex) {
        printf("Failed to create rectangle mutex: %s\n", SDL_GetError());
        SDL_DestroyMutex(frameMutex);
        return -1;
    }

    // Draw background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Initialize rectangles
    for (int i = 0; i < MAXR; i++) {
        r[i].x = rand() % (SCREEN_WIDTH - 10);
        r[i].y = rand() % (SCREEN_HEIGHT - 10);
        r[i].h = 10;
        r[i].w = 10;
    }
    printf(" ** Initialized %d rectangles \n", MAXR);

    // Calculate work distribution
    int rectanglesPerThread = MAXR / numThreads;
    int remainder = MAXR % numThreads;
    
    printf("Creating %d threads, %d rectangles per thread", numThreads, rectanglesPerThread);
    if (remainder > 0) {
        printf(" (+%d extra for some threads)", remainder);
    }
    printf("\n");

    // Create thread data and threads
    ThreadData* threadDataArray = (ThreadData*)malloc(numThreads * sizeof(ThreadData));
    SDL_Thread** threads = (SDL_Thread**)malloc(numThreads * sizeof(SDL_Thread*));
    
    if (!threadDataArray || !threads) {
        printf("Failed to allocate memory for threads\n");
        return -1;
    }
    
    int currentStart = 0;
    for (int i = 0; i < numThreads; i++) {
        threadDataArray[i].start = currentStart;
        threadDataArray[i].count = rectanglesPerThread;
        threadDataArray[i].threadId = i + 1;
        
        // Distribute remainder rectangles among first threads
        if (i < remainder) {
            threadDataArray[i].count++;
        }
        
        char threadName[32];
        sprintf(threadName, "ComputeThread%d", i);
        threads[i] = SDL_CreateThread(updateRectThread, threadName, &threadDataArray[i]);
        if (threads[i] == NULL) {
            printf("SDL_CreateThread failed for thread %d: %s\n", i, SDL_GetError());
            return -1;
        }
        
        currentStart += threadDataArray[i].count;
    }
    
    // Create rendering thread
    SDL_Thread* renderThreadHandle = SDL_CreateThread(renderThread, "RenderThread", NULL);
    if (renderThreadHandle == NULL) {
        printf("SDL_CreateThread failed for render thread: %s\n", SDL_GetError());
        return -1;
    }

    printf("All threads created successfully!\n");

    // Main thread handles events and FPS calculation
    SDL_Event e;
    Uint64 start, now;
    start = SDL_GetTicks();
    
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        now = SDL_GetTicks();
        if ((now - start) > 1000) {
            start = now;
            SDL_LockMutex(frameMutex);
            printf("frames/s = %d (using %d threads)\n", frames, numThreads);
            frames = 0;
            SDL_UnlockMutex(frameMutex);
        }
        
        // Small delay to prevent excessive CPU usage in main thread
        SDL_Delay(10);
    }
    
    printf(" ** Finishing - waiting for threads to complete\n");

    // Wait for all computation threads to finish
    for (int i = 0; i < numThreads; i++) {
        int threadReturnValue;
        SDL_WaitThread(threads[i], &threadReturnValue);
    }
    
    // Wait for render thread to finish
    int renderReturnValue;
    SDL_WaitThread(renderThreadHandle, &renderReturnValue);
    
    printf(" ** All threads completed\n");
    
    // Cleanup
    SDL_DestroyMutex(frameMutex);
    SDL_DestroyMutex(rectMutex);
    free(threadDataArray);
    free(threads);
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// Move a rectangle in a random direction
void move(SDL_Rect *rect) {
    int dir = rand() % 4;
    switch(dir) {
        case 0: // RIGHT
            rect->x += 10;
            if (rect->x >= SCREEN_WIDTH) rect->x = 0;
            break;
        case 1: // DOWN
            rect->y += 10;
            if (rect->y >= SCREEN_HEIGHT) rect->y = 0;
            break;
        case 2: // LEFT
            rect->x -= 10;
            if (rect->x < 0) rect->x = SCREEN_WIDTH - 10;
            break;
        case 3: // UP
            rect->y -= 10;
            if (rect->y < 0) rect->y = SCREEN_HEIGHT - 10;
            break;
    }
}

// Move rectangles 'start' to 'start+iters' in a random way
static void updateRect(int start, int iters) {
    // This function is now mainly used by the single-threaded version
    // In the parallel version, we separate computation (move) from rendering
    
    for (int i = 0; i < iters; i++) {
        move(&r[start + i]);
    }
}

// Initialize SDL
bool initializeSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (!SDL_CreateWindowAndRenderer("Parallel Rectangle", SCREEN_WIDTH, SCREEN_HEIGHT, 
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        printf("Window/Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
    return true;
}