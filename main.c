#include "l_list.h"

int main() {
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

    return 0;
}
