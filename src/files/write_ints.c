/**
 * @file write_ints.c
 * @brief Escriu enters en un fitxer utilitzant SDL IO.
 * @details Aquest programa demana a l'usuari que introdueixi 10 enters i els escriu
 *       en un fitxer anomenat "MYINTS.TXT" en format binari. Utilitza les funcions SDL_IO
 *       per gestionar l'entrada/sortida de fitxers.
 * * @authors Zakaria Hamdaoui - Joel Martínez Arjona - Sofía Giner Vargas
 * @date 2025-06-04
 */

#include <SDL3/SDL.h>
#include <stdio.h>

int write_ints(int argc, char* argv[]) {
    
    SDL_IOStream* file = SDL_IOFromFile("MYINTS.TXT", "wb");
    if (file == NULL) {
        printf("Error obrint el fitxer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    int numbers[10];
    printf("Introdueix 10 numeros:\n");
    for (int i = 0; i < 10; i++) {
        printf("Numero %d: ", i + 1);
        scanf_s("%d", &numbers[i]);
    }
    
    // Escriure els números en binari
    for (int i = 0; i < 10; i++) {
        SDL_WriteIO(file, &numbers[i], sizeof(int));
    }
    
    SDL_CloseIO(file);
    printf("Numeros guardats a MYINTS.TXT\n");
    
    SDL_Quit();
    return 0;
}