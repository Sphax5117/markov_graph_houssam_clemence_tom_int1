
#include "list.h"

t_list * createEmptyList() {
    t_list * list;
    list->head = NULL;
    return list;
}


void addCell(t_list * list, int value) {
    t_cell * newCell = createCell(value);
    t_cell * curr = list->head;
    if (curr == NULL) {
        list->head = newCell;
    } else {
        while(curr) {
            
        }
    }
