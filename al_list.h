#ifndef PROJET_C_L2_AL_LIST_H
#define PROJET_C_L2_AL_LIST_H

#include "al_cell.h"
#include <stdio.h>

typedef struct al_list
{
    int maxLevels;
    al_cell * heads[];
} al_list;

al_list *MakeEmptyList(int maxLevels);

al_list *MakeBigList(int n);

void InsertCell(al_list *list, al_cell *cell);

void PrintListLevel(al_list *list, int level);

void PrintList(al_list *list);

al_cell *SearchValueLevel0(al_list *list, int value);

al_cell *SearchValue(al_list *list, int value);


#endif //PROJET_C_L2_AL_LIST_H
