/**
 * Heads on Lab - Gestió de Memòria Dinàmica
 * Exercici: Emular la bossa de Geralt de Rivia
 * Autors: Zakaria Hamdaoui, Sofía Giner Vargas i Joel Martínez Arjona
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
//#include <io.h>
#else
#include <unistd.h>
#endif

unsigned ID = 0;

/* Linked list of elements */
struct element {
    unsigned id;
    char name[50];
    int weight;
    struct element* next;  // apuntador al següent element
};

struct bag {
    int nelems;
    struct element* first;  // apuntador al primer element
};

void waitReturn()
{
    printf("[Press RETURN key]\n");
    char buff;
#ifdef _WIN32
    (void)getchar();  // Usar getchar() en Windows
#else
    read(0, &buff, 1);
#endif
}

int menu(struct bag* geraldBag) {
    printf(" Current Bag has a total of %d elements\n", geraldBag->nelems);
    printf(" What do you want to do?\n");
    printf("    1) Add a new element\n");
    printf("    2) List elements\n");
    printf(" Enter command or Ctrl-C to exit: \n");
    char buff[50];
#ifdef _WIN32
    fgets(buff, 50, stdin);  // Usar fgets() en Windows
#else
    read(0, buff, 50);
#endif
    buff[1] = '\0';
    return atoi(buff);
}

void add_element(struct bag* geraldBag) {
    /* Crear memòria per al nou element */
    struct element* p = (struct element*)malloc(sizeof(struct element));
    if (p == NULL) {
        fprintf(stderr, "Error: no es pot reservar memòria.\n");
        return;
    }

    /* Inicialitzar els camps */
    p->id = ID++;
    snprintf(p->name, 50, "obj%d", p->id);
    p->weight = p->id % 50;
    p->next = NULL;

    /* Afegir al principi de la llista (o al final si prefereixes) */
    p->next = geraldBag->first;
    geraldBag->first = p;

    geraldBag->nelems++;
}

void list_elements(struct bag* geraldBag) {
    struct element* object = geraldBag->first;
    int i = 0;
    while (object != NULL) {
        printf("[%d] object [%s] weighs %d Kg\n", i, object->name, object->weight);
        object = object->next;
        i++;
    }
}

int geraldBag() {
    printf(" This is a simple code to emulate the bag of a known comic character\n");

    struct bag geraldBag;
    geraldBag.nelems = 0;
    geraldBag.first = NULL;  // inicialitzar la llista

    while (1) {
        int op = menu(&geraldBag);
        switch (op) {
        case 1:
            add_element(&geraldBag);
            break;
        case 2:
            list_elements(&geraldBag);
            break;
        default:
            break;
        }
    }

    waitReturn();
    return 0;
}