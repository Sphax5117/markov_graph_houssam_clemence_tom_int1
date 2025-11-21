#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * @brief Creates an empty linked list.
 *
 * @return t_list* A pointer to the newly created empty list.
 */
t_list * createEmptyList() {
    t_list * list = malloc(sizeof(t_list));
    list->head = NULL;
    return list;
}

/**
 * @brief Adds a new cell to the beginning of the linked list.
 *
 * @param list A pointer to the linked list.
 * @param destination The destination vertex ID.
 * @param probability The probability of the transition.
 */
void addCell(t_list *list, int destination, float probability) {
    if (!list) return;
    t_cell *newCell = createCell(destination, probability);
    if (!newCell) { fprintf(stderr,"addCell: malloc failed\n"); return; }
    newCell->next = list->head;  
    list->head = newCell;
}

/**
 * @brief Displays the contents of the linked list.
 *
 * @param list A pointer to the linked list to display.
 */
void displayList(const t_list *list) {
    const t_cell *curr = list->head;
    printf(" [head] ->");
    while (curr) {
        printf(" (%d, %.2f) @->", curr->destination, curr->probability);
        curr = curr->next; 
    }
    printf(" NULL\n");
}