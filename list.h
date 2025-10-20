#ifndef __LIST_H__
#define __LIST_H__
#include "cell.h"

typedef struct s_list {
    t_cell *head;
} t_list;

void list_init(t_list *l);
void addCell(t_list *list, int destination, float probability);
void displayList(const t_list *list);
#endif

