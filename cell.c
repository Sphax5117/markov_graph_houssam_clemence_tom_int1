#include <stdlib.h>
#include "cell.h"


t_cell *createCell(int destination, float probability) {
    /**
 * @brief Allocates and initializes a new cell structure for a linked list.
 *
 * This function creates a new `t_cell` node, sets its destination and
 * probability values, and initializes its `next` pointer to NULL.
 * It dynamically allocates memory for the new cell.
 *
 * @param destination The target node index for this cell in the graph
 * @param probability The probability value associated with the connection
 * or transition represented by this cell.
 * @return t_cell* A pointer to the newly created and initialized cell,
 * or NULL if memory allocation fails.
 */
    t_cell *new_cell = malloc(sizeof *new_cell);
    if (!new_cell) return NULL;
    new_cell->destination = destination;
    new_cell->probability = probability;
    new_cell->next = NULL;
    return new_cell;
}