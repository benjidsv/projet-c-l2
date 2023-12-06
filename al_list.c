#include "al_list.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

al_list *MakeEmptyList(int maxLevels) {
    al_list *newList = malloc(sizeof(al_list) + maxLevels * sizeof(al_cell));
    newList->maxLevels = maxLevels;

    for (int i = 0; i < maxLevels; ++i) {
        newList->heads[i] = NULL;
    }

    return newList;
}

// Retourne 1 pour key > other (plus loin dans l'alphabet)
int CompareKeys(const char *key, const char *other) {
    if (!strcmp(key, other)) return -1; // Si les chaînes sont égales

    int i = 0;
    while (key[i] != '\0' && other[i] != '\0') {
        if (key[i] > other[i]) return 1;
        if (key[i] < other[i]) return 0;
        i++;
    }
    // Si on est ici les clés ont les mêmes caractères mais une des clés est plus longue
    // Dans ce cas celle qui est plus longue est la plus grande (plus loin dans l'alphabet)
    return strlen(key) > strlen(other);
}

int NumberOfSameLetters(const char *key, const char *other) {
    int i = 0;
    while (key[i] != '\0' && other[i] != '\0' && key[i] == other[i]) i++;

    return i;
}

int SkipColumnWhilePrinting(al_list *list, int index, entry value, char **retval) {
    al_cell *next = list->heads[0];
    int j = 0;
    while (j < index) {
        if (next == NULL) return 0;
        next = next->next[0];
        j++;
    }

    if (next == NULL) return 0;
    *retval = next->value.c.key;
    return strcmp(next->value.c.key, value.c.key);
}

void PrintList(al_list *list) {
    for (int i = 0; i < list->maxLevels ; ++i) {
        PrintListLevel(list, i);
    }
}


void RaccordCells(al_list *list) {
    // On efface le raccordement précédent
    al_cell *next = list->heads[0];
    while (next != NULL) {
        for (int i = 1; i < list->maxLevels; ++i) {
            next->next[i] = NULL;
        }
        next = next->next[0];
    }

    for (int level = 1; level < list->maxLevels; ++level) {
        // On met la première valeur à tous les niveaux
        list->heads[level] = list->heads[0];
    }

    next = list->heads[3];
    // On raccorde les lettres différentes
    while (next != NULL) {
        if (next->next[3] == NULL) {
            al_cell *next0 = next;
            while (next0 != NULL && next0->value.c.key[0] == next->value.c.key[0]) next0 = next0->next[0];
            if (next0 == NULL) break;
            next->next[3] = next0;
        }
        next = next->next[3];
    }


    next = list->heads[2];
    // On raccorde le niveau 2
    while (next != NULL) {
        if (next->next[2] == NULL) {
            al_cell *next0 = next->next[0];
            while (next0 != NULL && NumberOfSameLetters(next->value.c.key, next0->value.c.key) != 1)
                next0 = next0->next[0];
            if (next0 == NULL) break;
            next->next[2] = next0;
        }
        next = next->next[2];
    }

    next = list->heads[1];
    // On raccorde le niveau 1
    while (next != NULL) {
        if (next->next[1] == NULL) {
            al_cell *next0 = next->next[0];
            while (next0 != NULL && NumberOfSameLetters(next->value.c.key, next0->value.c.key) != 2)
                next0 = next0->next[0];
            if (next0 == NULL) break;
            next->next[1] = next0;
        }
        next = next->next[1];
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
// on peut ignorer ce warning car il est impossible que la fonction soit appellée récursivement plus d'une fois
void InsertCell(al_list *list, al_cell *cell, int raccord) {
    int position = 0;
    // Cas ou la liste est vide
    if (list->heads[0] == NULL) {
        list->heads[0] = cell;
        RaccordCells(list);
        return;
    }

    // Cas ou il n'y a qu'un élément
    if (list->heads[0]->next[0] == NULL) {
        if (CompareKeys(cell->value.c.key, list->heads[0]->value.c.key)) {
            list->heads[0]->next[0] = cell;
            if (raccord) RaccordCells(list);
            return;
        }

        // Si on doit faire l'inverse on peut simplement vider la liste et y remettre les éléments dans l'odre inverse
        al_cell *cell2 = list->heads[0];
        for (int i = 0; i < list->maxLevels; ++i) {
            list->heads[i] = NULL;
        }
        InsertCell(list, cell, raccord); // On insère notre cellule en premier
        InsertCell(list, cell2, raccord);
        return;
    }

    // On détermine ou insérer la cellule dans la liste (par ordre croissant)
    al_cell *insertionPoint = list->heads[0];
    // On doit l'insérer en tête
    if (CompareKeys(insertionPoint->value.c.key, cell->value.c.key)) {
        cell->next[0] = list->heads[0];
        list->heads[0] = cell;
        if (raccord) RaccordCells(list);
        return;
    }

    while (insertionPoint->next[0] != NULL) {
        if (CompareKeys(insertionPoint->next[0]->value.c.key, cell->value.c.key)) break;
        insertionPoint = insertionPoint->next[0];
    }

    if (insertionPoint->next[0] != NULL) cell->next[0] = insertionPoint->next[0];
    insertionPoint->next[0] = cell;

    if (raccord) RaccordCells(list);
}
#pragma clang diagnostic pop

void PrintListLevel(al_list *list, int level) {
    printf("[ H%d @-] --", level);

    al_cell *next = list->heads[level];
    int j = 0;
    while (next != NULL) {
        char *retval = "";
        if (SkipColumnWhilePrinting(list, j, next->value, &retval)) {
            for (int i = 0; i < 13 + strlen(retval); ++i) putchar('-');
            j++;
            continue;
        }

        printf("> [ %s | @-] --", next->value.c.key);
        next = next->next[level];
        j++;
    }

    printf("> NULL\n");
}

al_cell *SearchValueLevel0(al_list *list, char *value) {
    al_cell *next = list->heads[0];
    while (next != NULL) {
        if (!strcmp(next->value.c.key, value)) break;
        next = next->next[0];
    }

    return next;
}

al_cell *SearchValue(al_list *list, char* value) {
    int level = list->maxLevels - 1;
    al_cell *next = list->heads[level];
    al_cell *lastInferior = next;

    for (; level >= 0; --level) {
        if (CompareKeys(lastInferior->value.c.key, value)) {
            while (next != NULL) {
                if (!strcmp(next->value.c.key, value)) return next;
                if (strcasestr(next->value.c.key, value)) return next;
                if (CompareKeys(next->value.c.key, value)) break;

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


