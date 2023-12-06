#include "l_list.h"
#include "timer/timer.h"
#include <stdlib.h>
#include <math.h>


void Partie1() {
    l_list *list = MakeEmptyList(5);

    // Insertion en tête
    l_cell *cell = MakeCell(15, 3);
    InsertCell(list, cell);

    // Insertion en tête
    cell = MakeCell(10, 4);
    InsertCell(list, cell);

    // Insertion en queue
    cell = MakeCell(25, 5);
    InsertCell(list, cell);

    // Insertion en milieu de liste
    cell = MakeCell(20, 1);
    InsertCell(list, cell);

    // Affichage
    // PrintListLevel(list, 0);
    PrintList(list);
}

void Partie2(int nMax) {
    for (int n = 3; n < nMax; ++n) {
        srand(time(0));
        int valueToSearch = rand() % ((int)pow(2, n) - 1) + 1;
        l_list *list = MakeBigList(n);

        startTimer();
        for (int j = 0; j <= 1000; ++j) {
            SearchValueLevel0(list, valueToSearch);
        }
        stopTimer();
        char *oneSingle = getTimeAsString();

        startTimer();
        for (int j = 0; j <= 10000; ++j) {
            SearchValueLevel0(list, valueToSearch);
        }
        stopTimer();
        char *tenSingle = getTimeAsString();

        startTimer();
        for (int j = 0; j <= 100000; ++j) {
            SearchValueLevel0(list, valueToSearch);
        }
        stopTimer();
        char *hundredSingle = getTimeAsString();

        startTimer();
        for (int j = 0; j <= 1000; ++j) {
            SearchValue(list, valueToSearch);
        }
        stopTimer();
        char *oneMulti = getTimeAsString();

        startTimer();
        for (int j = 0; j <= 10000; ++j) {
            SearchValue(list, valueToSearch);
        }
        stopTimer();
        char *tenMulti = getTimeAsString();

        startTimer();
        for (int j = 0; j <= 100000; ++j) {
            SearchValue(list, valueToSearch);
        }
        stopTimer();
        char *hundredMulti = getTimeAsString();

        printf("n=%d | level 0: %s %s %s | multilevel %s %s %s\n", n, oneSingle, tenSingle, hundredSingle, oneMulti, tenMulti, hundredMulti);
    }
}

int main() {

    Partie1();

    return 0;
}
