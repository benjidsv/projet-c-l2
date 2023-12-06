#include "al_cell.h"
#include <stdlib.h>

al_cell *MakeCell(int val, int lvl) {
    al_cell *newCell = malloc(sizeof(al_cell) + sizeof(al_cell*) * lvl);
    newCell->value = val;
    newCell->level = lvl;
    for (int i = 0; i < lvl; ++i) {
        newCell->next[i] = NULL;
    }

    return newCell;
}