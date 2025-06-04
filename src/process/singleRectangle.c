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
#define MAXR 100  // Usa el valor que t'hagi donat ~10 FPS
SDL_Rect r[MAXR];
static bool quit = false;
static int frames = 0;

bool initializeSDL();
void updateRect(int start, int iters);
void move(SDL_Rect *rect);

// TODO: Thread function
int updateRectThread(void* data) {
    while (!quit) {
        updateRect(0, MAXR);
    }
    return 0;
}

int singleRectangle(int argc, char** argv) {
    if (!initializeSDL()) return (-1);

    printf(" ** Starting \n");

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

    // TODO: Create thread HERE
    SDL_Thread *thread = SDL_CreateThread(updateRectThread, "UpdateThread", NULL);
    if (thread == NULL) {
        printf("SDL_CreateThread failed: %s\n", SDL_GetError());
        return -1;
    }

    // Main thread only calculates FPS
    SDL_Event e;
    Uint64 start, now;
    start = SDL_GetTicks();
    
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        // TODO: Remove this line when threads are created
        // updateRect(0, MAXR);  // COMENTAT!

        now = SDL_GetTicks();
        if ((now - start) > 1000) {
            start = now;
            printf("frames/s = %d\n", frames);
            frames = 0;
        }
    }
    
    printf(" ** Finishing \n");

    // TODO: Change this to REAL code to Wait threads
    int threadReturnValue;
    SDL_WaitThread(thread, &threadReturnValue);
    
    printf(" ** All work done \n");
    
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
void updateRect(int start, int iters) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < iters; i++) {
        move(&r[start + i]);
        
        // Draw rectangle with random color
        SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
        SDL_FRect frect = { r[start + i].x, r[start + i].y, r[start + i].w, r[start + i].h };
        SDL_RenderFillRect(renderer, &frect);
    }
    
    SDL_RenderPresent(renderer);
    frames++;
}

// Initialize SDL
bool initializeSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    if (!SDL_CreateWindowAndRenderer("Single Thread Rectangle", SCREEN_WIDTH, SCREEN_HEIGHT, 
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        printf("Window/Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
    return true;
}