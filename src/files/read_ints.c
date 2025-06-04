/**
 * @file read_ints.c
 * @brief Llegeix enters d'un fitxer utilitzant SDL IO.
 * @details Aquest programa obre un fitxer anomenat "MYINTS.TXT" i llegeix enters
 *        un per un, mostrant-los per pantalla. Utilitza les funcions SDL_IO per gestionar
 *        l'entrada/sortida de fitxers.
 * * @authors Zakaria Hamdaoui - Joel Martínez Arjona - Sofía Giner Vargas
 * @date 2025-06-04
 */

#include <SDL3/SDL.h>
#include <stdio.h>

int read_ints(int argc, char* argv[]) {
    
    SDL_IOStream* file = SDL_IOFromFile("MYINTS.TXT", "rb");
    if (file == NULL) {
        printf("Error obrint el fitxer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    int number;
    int count = 0;
    
    printf("Numeros llegits del fitxer:\n");
    while (SDL_ReadIO(file, &number, sizeof(int)) == sizeof(int)) {
        printf("Numero %d: %d\n", count + 1, number);
        count++;
    }
    
    SDL_CloseIO(file);
    SDL_Quit();
    return 0;
}