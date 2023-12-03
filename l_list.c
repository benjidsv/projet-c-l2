#include "l_list.h"
#include <stdio.h>

l_list *MakeEmptyList(int maxLevels) {
    l_list *newList = malloc(sizeof(l_list) + maxLevels * sizeof(l_cell));
    newList->maxLevels = maxLevels;

    for (int i = 0; i < maxLevels; ++i) {
        newList->heads[i] = NULL;
    }

    return newList;
}

l_cell *GetCellFromIndex(l_list *list, int i) {
    l_cell *next = list->heads[0];
    while (i > 0) {
        next = next->next[0];
        i--;
    }

    return next;
}

int SkipColumnWhilePrinting(l_list *list, int index, int value) {
    l_cell *next = list->heads[0];
    int j = 0;
    while (j < index) {
        if (next == NULL) return 0;
        next = next->next[0];
        j++;
    }

    if (next == NULL) return 0;
    return next->value != value;
}

void PrintList(l_list *list) {
    for (int i = 0; i < list->maxLevels ; ++i) {
        PrintListLevel(list, i);
    }
}

void InsertCell(l_list *list, l_cell *cell) {
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
        l_cell *cell2 = list->heads[0];
        for (int i = 0; i < list->maxLevels; ++i) {
            list->heads[i] = NULL;
        }
        InsertCell(list, cell); // On insère notre cellule en premier
        InsertCell(list, cell2);
        return;
    }

    // On détermine ou insérer la cellule dans la liste (par ordre croissant)
    l_cell *insertionPoint = list->heads[0];
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
        l_cell *next = list->heads[i];
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

void PrintListLevel(l_list *list, int level) {
    printf("[ H%d @-] --", level);

    l_cell *next = list->heads[level];
    int j = 0;
    while (next != NULL) {
        if (SkipColumnWhilePrinting(list, j, next->value)) {
            printf("---------------");
            j++;
            continue;
        }
        else printf("> [ %d | @-] --", next->value);
        next = next->next[level];
        j++;
    }

    printf("> NULL\n");
}


