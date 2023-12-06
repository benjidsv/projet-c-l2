#include "al_list.h"
#include <math.h>
#include <stdlib.h>

al_list *MakeEmptyList(int maxLevels) {
    al_list *newList = malloc(sizeof(al_list) + maxLevels * sizeof(al_cell));
    newList->maxLevels = maxLevels;

    for (int i = 0; i < maxLevels; ++i) {
        newList->heads[i] = NULL;
    }

    return newList;
}

al_list *MakeBigList(int n) {
    int cellCount = (int)pow(2, n) - 1;
    int middle = (int)(cellCount/2);
    int level = 1;
    al_list *newList = MakeEmptyList(n);

    for (int i = 1; i <= cellCount; ++i) {
        al_cell *cell;
        if (i % 2 == 0) {
            level += i > middle + 1? -1 : 1;
            cell = MakeCell(i, level);
        }
        else {
            cell = MakeCell(i, 1); // Si le chiffre est impair le niveau est 1
        }
        InsertCell(newList, cell);
    }

    return newList;
}

int SkipColumnWhilePrinting(al_list *list, int index, int value) {
    al_cell *next = list->heads[0];
    int j = 0;
    while (j < index) {
        if (next == NULL) return 0;
        next = next->next[0];
        j++;
    }

    if (next == NULL) return 0;
    return next->value != value;
}

void PrintList(al_list *list) {
    for (int i = 0; i < list->maxLevels ; ++i) {
        PrintListLevel(list, i);
    }
}

void InsertCell(al_list *list, al_cell *cell) {
    // On limite le niveau de la cellule pour ne pas dépasser celui de la liste
    if (cell->level > list->maxLevels) cell->level = list->maxLevels;

    // Cas ou la liste est vide
    if (list->heads[0] == NULL) {
        for (int i = 0; i < cell->level; ++i) {
            list->heads[i] = cell;
        }
        return;
    }

    // Cas ou il n'y a qu'un élément
    if (list->heads[0]->next[0] == NULL) {
        if (cell->value > list->heads[0]->value) {
            // On lie à la cellule précédente
            for (int i = 0; i < cell->level && i < list->heads[0]->level; ++i) {
                list->heads[i]->next[i] = cell;
            }
            // On lie le reste aux têtes
            for (int i = list->heads[0]->level; i < cell->level; ++i) {
                list->heads[i] = cell;
            }
            return;
        }

        // Si on doit faire l'inverse on peut simplement vider la liste et y remettre les éléments dans l'odre inverse
        al_cell *cell2 = list->heads[0];
        for (int i = 0; i < list->maxLevels; ++i) {
            list->heads[i] = NULL;
        }
        InsertCell(list, cell); // On insère notre cellule en premier
        InsertCell(list, cell2);
        return;
    }

    // On détermine ou insérer la cellule dans la liste (par ordre croissant)
    al_cell *insertionPoint = list->heads[0];
    // On doit l'insérer en tête
    if (insertionPoint->value > cell->value) {
        for (int i = 0; i < cell->level; ++i) {
            list->heads[i] = cell;
            if (i < insertionPoint->level) cell->next[i] = insertionPoint;
        }

        return;
    }

    while (insertionPoint->next[0] != NULL) {
        if (insertionPoint->next[0]->value > cell->value) break;
        insertionPoint = insertionPoint->next[0];
    }

    // On lie aux cellules précédentes et suivantes s'il y en a
    for (int i = 0; i < cell->level && i < insertionPoint->level; ++i) {
        cell->next[i] = insertionPoint->next[i];
        insertionPoint->next[i] = cell;
    }
    // On lie le reste aux têtes / aux cellules passerelles
    for (int i = insertionPoint->level; i < cell->level; ++i) {
        // On parcoure chaque niveau concerné et on trouve le dernier élément (c'est là qu'on doit lier)
        al_cell *next = list->heads[i];
        if (next == NULL) {
            // Le niveau est vide
            list->heads[i] = cell;
            continue;
        }
        if (next->value > cell->value) {
            list->heads[i] = cell;
            cell->next[i] = next;
            continue;
        }
        while (next->next[i] != NULL) {
            next = next->next[i];
        }

        next->next[i] = cell;
    }
}

void PrintListLevel(al_list *list, int level) {
    printf("[ H%d @-] --", level);

    al_cell *next = list->heads[level];
    int j = 0;
    while (next != NULL) {
        if (SkipColumnWhilePrinting(list, j, next->value)) {
            printf("---------------");
            j++;
            continue;
        }

        printf("> [ %.2d | @-] --", next->value);
        next = next->next[level];
        j++;
    }

    printf("> NULL\n");
}

al_cell *SearchValueLevel0(al_list *list, int value) {
    al_cell *next = list->heads[0];
    while (next != NULL) {
        if (next->value == value) break;
        next = next->next[0];
    }

    return next;
}

al_cell *SearchValue(al_list *list, int value) {
    int level = list->maxLevels - 1;
    al_cell *next = list->heads[level];
    al_cell *lastInferior = next;

    for (; level >= 0; --level) {
        if (lastInferior->value <= value) {
            while (next != NULL) {
                if (next->value == value) return next;
                if (next->value > value) break;

                lastInferior = next;
                next = next->next[level];
            }

            next = lastInferior;
        }
        else {
            next = list->heads[level - 1];
            lastInferior = next;
        }
    }

    return NULL;
}


