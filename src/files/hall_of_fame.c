/**
 * @file hall_of_fame.c
 * @brief Gestió del Hall of Fame per un joc utilitzant SDL IO.
 * @details Aquest programa permet llegir i escriure un fitxer de Hall of Fame,
 *         on es guarden els jugadors i les seves puntuacions. Els jugadors
 *        es poden afegir, i les puntuacions es guarden en ordre descendent.
 * * @authors Zakaria Hamdaoui - Joel Martínez Arjona - Sofía Giner Vargas
 * @date 2025-06-04
 */

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int score;
} Player;

int compareScores(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerB->score - playerA->score; // Ordre descendent
}

int hall_of_fame(int argc, char* argv[]) {
    
    Player players[100]; // Màxim 100 jugadors
    int playerCount = 0;
    
    // Llegir fitxer existent si existeix
    SDL_IOStream* file = SDL_IOFromFile("FAME.TXT", "rb");
    if (file != NULL) {
        while (SDL_ReadIO(file, &players[playerCount], sizeof(Player)) == sizeof(Player)) {
            playerCount++;
        }
        SDL_CloseIO(file);
    }
    
    // Demanar nou jugador
    Player newPlayer;
    printf("Nom del jugador: ");
    fgets(newPlayer.name, sizeof(newPlayer.name), stdin);
    
    // Eliminar salt de línia
    int len = strlen(newPlayer.name);
    if (len > 0 && newPlayer.name[len-1] == '\n') {
        newPlayer.name[len-1] = '\0';
    }
    
    printf("Puntuacio: ");
    scanf_s("%d", &newPlayer.score);
    
    // Afegir nou jugador
    players[playerCount] = newPlayer;
    playerCount++;
    
    // Ordenar per puntuació
    qsort(players, playerCount, sizeof(Player), compareScores);
    
    // Guardar al fitxer
    file = SDL_IOFromFile("FAME.TXT", "wb");
    if (file == NULL) {
        printf("Error guardant el fitxer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    for (int i = 0; i < playerCount; i++) {
        SDL_WriteIO(file, &players[i], sizeof(Player));
    }
    SDL_CloseIO(file);
    
    // Mostrar Hall of Fame
    printf("\n=== HALL OF FAME ===\n");
    printf("%-20s %s\n", "Name", "Score");
    printf("%-20s %s\n", "----", "-----");
    for (int i = 0; i < playerCount; i++) {
        printf("%-20s %d\n", players[i].name, players[i].score);
    }
    
    SDL_Quit();
    return 0;
}