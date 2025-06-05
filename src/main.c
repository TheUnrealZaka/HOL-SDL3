/**
 * @file main.c
 * @brief Menú principal per als exercicis del HOL (Hands On Lab)
 * @details Aquest programa proporciona un menú interactiu per executar tots els
 *          exercicis dels diferents mòduls: Files, Memory i Process.
 * @authors Zakaria Hamdaoui - Joel Martínez Arjona - Sofía Giner Vargas
 * @date 2025-06-05
 */

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Declaracions de funcions dels diferents mòduls
// Files
extern int write_string(int argc, char* argv[]);
extern int write_ints(int argc, char* argv[]);
extern int read_ints(int argc, char* argv[]);
extern int hall_of_fame(int argc, char* argv[]);

// Memory
extern int geraldBag();
extern int matriu();
extern int mm_ijk();
extern int mm_jki();
extern int mm_kij();
extern int mm_ijk2();
extern int mem();
extern int mem2();

// Process
extern int rectangle(int argc, char** argv);
extern int singleRectangle(int argc, char** argv);
extern int parallelRectangle(int argc, char** argv);
extern int shared_inc(int argc, char* argv[]);
extern int shared_inc_multi(int argc, char* argv[]);
extern int shared_inc_safe(int argc, char* argv[]);

void mostrarMenu() {
    printf("\n=== HOL - HANDS ON LAB - SDL3 ===\n");
    printf("Selecciona un modul:\n\n");
    
    printf("FILES:\n");
    printf("  1) Write String (write_string.c)\n");
    printf("  2) Write Integers (write_ints.c)\n");
    printf("  3) Read Integers (read_ints.c)\n");
    printf("  4) Hall of Fame (hall_of_fame.c)\n\n");
    
    printf("MEMORY:\n");
    printf("  5) Gerald's Bag (geraldBag.c)\n");
    printf("  6) Matrix Analysis (matriu.c)\n");
    printf("  7) Matrix Multiply IJK (mm-ijk.c)\n");
    printf("  8) Matrix Multiply JKI (mm-jki.c)\n");
    printf("  9) Matrix Multiply KIJ (mm-kij.c)\n");
    printf(" 10) Matrix Multiply IJK2 (mm-ijk2.c)\n");
    printf(" 11) Memory Test 1 (mem.c)\n");
    printf(" 12) Memory Test 2 (mem2.c)\n\n");
    
    printf("PROCESS:\n");
    printf(" 13) Rectangle Single Thread (rectangle.c)\n");
    printf(" 14) Rectangle with Thread (singleRectangle.c)\n");
    printf(" 15) Parallel Rectangles (parallelRectangle.c)\n");
    printf(" 16) Shared Increment Simple (shared_inc.c)\n");
    printf(" 17) Shared Increment Multi (shared_inc_multi.c)\n");
    printf(" 18) Shared Increment Safe (shared_inc_safe.c)\n\n");
    
    printf("  0) Sortir\n\n");
    printf("Introdueix la teva opcio: ");
}

int main(int argc, char* argv[]) {
    int opcio;
    
    // Inicialitzar SDL una sola vegada
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("Error inicialitzant SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    printf("Benvingut al HOL - Hands On Lab!\n");
    printf("Autors: Zakaria Hamdaoui, Joel Martinez Arjona, Sofia Giner Vargas\n");
    
    do {
        mostrarMenu();
        
        if (scanf("%d", &opcio) != 1) {
            // Neteja buffer si input invàlid
            while (getchar() != '\n');
            printf("Opcio invalida. Prova de nou.\n");
            continue;
        }
        
        // Neteja buffer després de llegir número
        while (getchar() != '\n');
        
        printf("\n");
        
        switch (opcio) {
            // FILES
            case 1:
                printf("🔹 Executant Write String...\n");
                write_string(argc, argv);
                break;
                
            case 2:
                printf("🔹 Executant Write Integers...\n");
                write_ints(argc, argv);
                break;
                
            case 3:
                printf("🔹 Executant Read Integers...\n");
                read_ints(argc, argv);
                break;
                
            case 4:
                printf("🔹 Executant Hall of Fame...\n");
                hall_of_fame(argc, argv);
                break;
                
            // MEMORY
            case 5:
                printf("🔹 Executant Gerald's Bag...\n");
                geraldBag();
                break;
                
            case 6: // Agregar nuevo caso para matriu
                printf("🔹 Executant Matrix Analysis...\n");
                matriu();
                break;
                
            case 7:
                printf("🔹 Executant Matrix Multiply IJK...\n");
                mm_ijk();
                break;
                
            case 8:
                printf("🔹 Executant Matrix Multiply JKI...\n");
                mm_jki();
                break;
                
            case 9:
                printf("🔹 Executant Matrix Multiply KIJ...\n");
                mm_kij();
                break;
                
            case 10:
                printf("🔹 Executant Matrix Multiply IJK2...\n");
                mm_ijk2();
                break;
                
            case 11:
                printf("🔹 Executant Memory Test 1...\n");
                mem();
                break;
                
            case 12:
                printf("🔹 Executant Memory Test 2...\n");
                mem2();
                break;
                
            // PROCESS
            case 13: // Cambiar números de casos
                printf("Executant Rectangle Single Thread...\n");
                printf("Premeu ESC o tanqueu la finestra per sortir.\n");
                rectangle(argc, argv);
                break;
                
            case 14:
                printf("Executant Rectangle with Thread...\n");
                printf("Premeu ESC o tanqueu la finestra per sortir.\n");
                singleRectangle(argc, argv);
                break;
                
            case 15:
                printf("Executant Parallel Rectangles...\n");
                printf("Premeu ESC o tanqueu la finestra per sortir.\n");
                parallelRectangle(argc, argv);
                break;
                
            case 16:
                printf("Executant Shared Increment Simple...\n");
                shared_inc(argc, argv);
                break;
                
            case 17:
                printf("Executant Shared Increment Multi...\n");
                shared_inc_multi(argc, argv);
                break;
                
            case 18:
                printf("Executant Shared Increment Safe...\n");
                shared_inc_safe(argc, argv);
                break;
                
            case 0:
                printf("Fins aviat!\n");
                break;
                
            default:
                printf("Opcio invalida. Prova amb un número del 0 al 18.\n");
                break;
        }
        
        if (opcio != 0) {
            printf("\nPrograma finalitzat. Premeu ENTER per tornar al menu...");
            getchar();
        }
        
    } while (opcio != 0);
    
    SDL_Quit();
    return 0;
}