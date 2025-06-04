/**
 * @file write_string.c
 * @brief Escriu una cadena de caràcters en un fitxer utilitzant SDL IO.
 * @details Aquest programa demana a l'usuari que introdueixi una cadena de caràcters
 *       i la guarda en un fitxer anomenat "MYSTRING.TXT". Utilitza les funcions SDL_IO
 *      per gestionar l'entrada/sortida de fitxers.
 * * @authors Zakaria Hamdaoui - Joel Martínez Arjona - Sofía Giner Vargas
 * @date 2025-06-04
 */

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int write_string(int argc, char* argv[]) {
    char string[256];
    printf("Introdueix una cadena de caracters: ");
    fgets(string, sizeof(string), stdin);
    
    // Eliminar el salt de línia si existeix
    int len = strlen(string);
    if (len > 0 && string[len-1] == '\n') {
        string[len-1] = '\0';
    }
    
    SDL_IOStream* file = SDL_IOFromFile("MYSTRING.TXT", "w");
    if (file == NULL) {
        printf("Error obrint el fitxer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_WriteIO(file, string, strlen(string));
    SDL_CloseIO(file);
    
    printf("Cadena guardada a MYSTRING.TXT\n");
    
    SDL_Quit();
    return 0;
}