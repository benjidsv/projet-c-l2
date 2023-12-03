#ifndef PROJET_C_L2_L_LIST_H
#define PROJET_C_L2_L_LIST_H

#include "l_cell.h"

typedef struct l_list
{
    int maxLevels;
    l_cell * heads[];
} l_list;

l_list *MakeEmptyList(int maxLevels);

void InsertCell(l_list *list, l_cell *cell);

void PrintListLevel(l_list *list, int level);

void PrintList(l_list *list);


#endif //PROJET_C_L2_L_LIST_H
