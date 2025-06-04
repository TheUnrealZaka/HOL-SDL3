#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>

// Afegir la variable quit que faltava
static bool quit = false;

// Exemple de com mesurar temps en diferents parts del teu joc
void profile_game_loop() {
    Uint64 frame_start, input_time, update_time, render_time, frame_end;
    
    while (!quit) {
        frame_start = SDL_GetTicks();
        
        // 1. Input processing
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }
        input_time = SDL_GetTicks();
        
        // 2. Game logic update
        // update_game_logic();
        update_time = SDL_GetTicks();
        
        // 3. Rendering
        // render_game();
        render_time = SDL_GetTicks();
        
        frame_end = SDL_GetTicks();
        
        // Print profiling info every second
        static Uint64 last_profile = 0;
        if (frame_end - last_profile > 1000) {
            printf("Frame timing:\n");
            printf("  Input:  %llu ms\n", input_time - frame_start);
            printf("  Update: %llu ms\n", update_time - input_time);
            printf("  Render: %llu ms\n", render_time - update_time);
            printf("  Total:  %llu ms\n", frame_end - frame_start);
            printf("  FPS:    %.1f\n\n", 1000.0 / (frame_end - frame_start));
            last_profile = frame_end;
        }
    }
}