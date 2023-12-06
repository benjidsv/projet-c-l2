#include "al_cell.h"
#include <stdlib.h>

al_cell *MakeCell(entry val) {
    al_cell *new = malloc(sizeof(al_cell) + sizeof(al_cell*) * 4);
    new->value = val;
    //new->level = 4;
    for (int i = 0; i < 4; ++i) {
        new->next[i] = NULL;
    }

    return new;
}