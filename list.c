#include <stdio.h>
#include <stdlib.h>
#include "list.h"
t_list * createEmptyList() {
    t_list * list = malloc(sizeof(t_list));
    list->head = NULL;
    return list;
}

void addCell(t_list *list, int destination, float probability) {
    if (!list) return;
    t_cell *newCell = createCell(destination, probability);
    if (!newCell) { fprintf(stderr,"addCell: malloc failed\n"); return; }
    newCell->next = list->head;  
    list->head = newCell;
}

void displayList(const t_list *list) {
    const t_cell *curr = list->head;
    printf(" [head] ->");
    while (curr) {
        printf(" (%d, %.2f) @->", curr->destination, curr->probability);
        curr = curr->next; 
    }
    printf(" NULL\n");
}