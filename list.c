
#include "list.h"

t_list * createEmptyList() {
    t_list * list;
    list->head = NULL;
    return list;
}


void addCell(t_list * list, int destination, float probability) {
    t_cell *newCell = createCell(destination, probability);
    newCell->next = list->head;
    list->head = newCell;
    return;
}

void displayList(t_list * list) {
    t_cell * curr;
    curr = list->head;
    printf("[head @] ->")
    while(curr) {
        printf("(%d, %d) @->", curr->destination, curr->probability);
        curr++;
    }
    return;
}