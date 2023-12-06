#include "agenda.h"
#include "al_list.h"
#include <stdlib.h>
#include <math.h>
#include <printf.h>

int main() {
    al_list *list = MakeEmptyList(4);
    contact *c = MakeContact("Arbousset", "Benjamin");
    entry *e = MakeEntry(*c);
    al_cell *cell = MakeCell(*e);
    InsertCell(list, cell);

    c = MakeContact("John", "Carpenter");
    e = MakeEntry(*c);
    cell = MakeCell(*e);
    InsertCell(list, cell);

    c = MakeContact("Allawakbar", "Carpenter");
    e = MakeEntry(*c);
    cell = MakeCell(*e);
    InsertCell(list, cell);

    PrintList(list);

    return 0;
}
