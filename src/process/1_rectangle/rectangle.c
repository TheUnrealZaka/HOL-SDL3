#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Screen size
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

/* SDL main objects */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Surface *screenSurface = NULL;

/* 'Game' related variables */
#define MAXR 1     // Maximum number of rectangles - CANVIA AQUEST VALOR!
SDL_Rect r[MAXR];  // Array of rectangles
static bool quit = false; // Finish game indicator
static int frames = 0;    // Number of Drawn frames (since last update)

static bool initializeSDL();
static void updateRect(int start, int iters);
static void move(SDL_Rect *rect);

int rectangle(int argc, char **argv)
{
    if (!initializeSDL())
        return (-1);

    printf(" ** Starting \n");

    // Draw background (white)
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

    // Start game loop
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

        updateRect(0, MAXR);

        now = SDL_GetTicks();
        if ((now - start) > 1000)
        { // a SECOND has passed!
            start = now;
            printf("frames/s = %d\n", frames);
            frames = 0;
        }
    }

    printf(" ** Finishing \n");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

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

// Move rectangles 'start' to 'start+iters' in a random way
static void updateRect(int start, int iters)
{
    // Clear screen (white background)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < iters; i++)
    {
        move(&r[start + i]); // Calculate new position

        // Draw rectangle in new position with random color
        SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
        SDL_FRect frect = {r[start + i].x, r[start + i].y, r[start + i].w, r[start + i].h};
        SDL_RenderFillRect(renderer, &frect);
    }

    SDL_RenderPresent(renderer);
    frames++;
}

// Initialize SDL
static bool initializeSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Rectangle Movement", SCREEN_WIDTH, SCREEN_HEIGHT,
                                     SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        printf("Window/Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
    return true;
}