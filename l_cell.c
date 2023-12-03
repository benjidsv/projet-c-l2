#include "l_cell.h"

l_cell *MakeCell(int val, int lvl) {
    l_cell *newCell = malloc(sizeof(l_cell) + sizeof(l_cell*) * lvl);
    newCell->value = val;
    newCell->level = lvl;
    for (int i = 0; i < lvl; ++i) {
        newCell->next[i] = NULL;
    }

    return newCell;
}