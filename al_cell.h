#ifndef PROJET_C_L2_AL_CELL_H
#define PROJET_C_L2_AL_CELL_H

#include "agenda.h"

typedef struct al_cell
{
    int level;
    entry value;
    struct al_cell *next[];
} al_cell;

al_cell *MakeCell(entry val);

#endif //PROJET_C_L2_AL_CELL_H
