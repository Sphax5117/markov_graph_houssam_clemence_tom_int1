#include <stdlib.h>
#include "cell.h"

t_cell *createCell(int destination, float probability)
{
    t_cell *new_cell = (t_cell *)malloc(sizeof(t_cell));
    if (!new_cell)
        return NULL;

    new_cell->destination = destination;
    new_cell->probability = probability;
    new_cell->next = NULL;

    return new_cell;
}