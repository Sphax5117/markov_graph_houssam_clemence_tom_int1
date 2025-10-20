#include <stdio.h>
#include "list.h"
void list_init(t_list *l) { l->head = NULL; }

void addCell(t_list *list, int destination, float probability) {
    if (!list) return;
    t_cell *newCell = createCell(destination, probability);
    if (!newCell) { fprintf(stderr,"addCell: malloc failed\n"); return; }
    newCell->next = list->head;   // insertion en tête
    list->head = newCell;
}

void displayList(const t_list *list) {
    const t_cell *curr = list->head;
    printf(" [head] ->");
    while (curr) {
        printf(" (%d, %.2f) @->", curr->destination, curr->probability);
        curr = curr->next;  // <<< important
    }
    printf(" NULL\n");
}