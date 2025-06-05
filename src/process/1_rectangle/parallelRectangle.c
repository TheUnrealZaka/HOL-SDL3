#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Screen size
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAX_THREADS 32

/* SDL main objects */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Surface *screenSurface = NULL;

/* 'Game' related variables */
#define MAXR 1000 // Usa un valor que et doni pocs FPS en single thread
SDL_Rect r[MAXR];
static bool quit = false;
static int frames = 0;

// Structure to pass data to each thread
typedef struct
{
    int start;     // Starting position in array
    int count;     // Number of rectangles to process
    int thread_id; // Thread identifier
} ThreadData;

// Function declarations
static bool initializeSDL();
static void move(SDL_Rect *rect);  // Add this declaration

static bool initializeSDL();
// Move a rectangle in a random direction
static void move(SDL_Rect *rect)
{
    int dir = rand() % 4;
    switch (dir)
    {
    case 0: // RIGHT
        rect->x += 10;
        if (rect->x >= SCREEN_WIDTH)
            rect->x = 0;
        break;
    case 1: // DOWN
        rect->y += 10;
        if (rect->y >= SCREEN_HEIGHT)
            rect->y = 0;
        break;
    case 2: // LEFT
        rect->x -= 10;
        if (rect->x < 0)
            rect->x = SCREEN_WIDTH - 10;
        break;
    case 3: // UP
        rect->y -= 10;
        if (rect->y < 0)
            rect->y = SCREEN_HEIGHT - 10;
        break;
    }
}

// Thread function - each thread processes a portion of rectangles
static int updateRectThread(void *data)
{
    ThreadData *threadData = (ThreadData *)data;

    printf("Thread %d started: processing %d rectangles from position %d\n",
           threadData->thread_id, threadData->count, threadData->start);

    while (!quit)
    {
        // Each thread handles its portion: MOVE + RENDER
        for (int i = 0; i < threadData->count; i++)
        {
            int rectIndex = threadData->start + i;
            
            // Move rectangle
            move(&r[rectIndex]);
            
            // Each thread renders its own rectangles
            SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
            SDL_FRect frect = {(float)r[rectIndex].x, (float)r[rectIndex].y, 
                              (float)r[rectIndex].w, (float)r[rectIndex].h};
            SDL_RenderFillRect(renderer, &frect);
        }
        
        // Small delay to prevent 100% CPU usage
        SDL_Delay(1);
    }

    printf("Thread %d finished\n", threadData->thread_id);
    return 0;
}

int parallelRectangle(int argc, char **argv)
{
    if (!initializeSDL())
        return (-1);

    // Ask for number of threads
    int numThreads;
    printf("Enter number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &numThreads);

    if (numThreads < 1 || numThreads > MAX_THREADS)
    {
        printf("Invalid number of threads. Using 1.\n");
        numThreads = 1;
    }

    printf(" ** Starting with %d threads\n", numThreads);

    // Draw background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Initialize rectangles
    for (int i = 0; i < MAXR; i++)
    {
        r[i].x = rand() % (SCREEN_WIDTH - 10);
        r[i].y = rand() % (SCREEN_HEIGHT - 10);
        r[i].h = 10;
        r[i].w = 10;
    }
    printf(" ** Initialized %d rectangles \n", MAXR);

    // Create threads and thread data
    SDL_Thread *threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];

    // Calculate work distribution - FIXED VERSION
    int rectsPerThread = MAXR / numThreads;
    int remainingRects = MAXR % numThreads;

    for (int i = 0; i < numThreads; i++)
    {
        threadData[i].thread_id = i;
        threadData[i].count = rectsPerThread;

        // Give extra rectangles to first threads
        if (i < remainingRects)
        {
            threadData[i].count++;
        }

        // Calculate start position correctly
        threadData[i].start = 0;
        for (int j = 0; j < i; j++)
        {
            threadData[i].start += threadData[j].count;
        }

        printf("Creating thread %d: start=%d, count=%d\n",
               i, threadData[i].start, threadData[i].count);

        // Create thread
        char threadName[32];
        sprintf(threadName, "UpdateThread%d", i);
        threads[i] = SDL_CreateThread(updateRectThread, threadName, &threadData[i]);

        if (threads[i] == NULL)
        {
            printf("SDL_CreateThread failed for thread %d: %s\n", i, SDL_GetError());
            return -1;
        }
    }

    // Main thread handles only FPS calculation and events
    SDL_Event e;
    Uint64 start, now;
    start = SDL_GetTicks();

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                quit = true;
        }

        // Clear screen once per frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        // Present the frame (all threads have drawn their parts)
        SDL_RenderPresent(renderer);
        frames++;

        now = SDL_GetTicks();
        if ((now - start) > 1000)
        {
            start = now;
            printf("frames/s = %d (using %d threads)\n", frames, numThreads);
            frames = 0;
        }
    }

    printf(" ** Finishing and waiting for threads...\n");

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; i++)
    {
        int threadReturnValue;
        SDL_WaitThread(threads[i], &threadReturnValue);
        printf("Thread %d finished with return value %d\n", i, threadReturnValue);
    }

    printf(" ** All work done \n");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// Initialize SDL
static bool initializeSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Parallel Rectangle", SCREEN_WIDTH, SCREEN_HEIGHT,
                                     SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        printf("Window/Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
    return true;
}