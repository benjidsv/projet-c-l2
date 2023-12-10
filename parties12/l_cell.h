#ifndef PROJET_C_L2_L_CELL_H
#define PROJET_C_L2_L_CELL_H

typedef struct l_cell
{
    int value;
    int level;
    struct l_cell *next[];
} l_cell;

l_cell *MakeCell(int val, int lvl);

#endif //PROJET_C_L2_L_CELL_H
