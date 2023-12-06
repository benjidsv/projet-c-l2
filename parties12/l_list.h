#ifndef PROJET_C_L2_L_LIST_H
#define PROJET_C_L2_L_LIST_H

#include "l_cell.h"
#include <stdio.h>

typedef struct l_list
{
    int maxLevels;
    l_cell * heads[];
} l_list;

l_list *MakeEmptyList(int maxLevels);

l_list *MakeBigList(int n);

void InsertCell(l_list *list, l_cell *cell);

void PrintListLevel(l_list *list, int level);

void PrintList(l_list *list);

l_cell *SearchValueLevel0(l_list *list, int value);

l_cell *SearchValue(l_list *list, int value);


#endif //PROJET_C_L2_L_LIST_H
