#ifndef __LIST_H__
#define __LIST_H__
#include "cell.h"

typedef struct s_list{
    t_cell *head;
} t_list;


t_list * createEmptyList();
void addCell(t_list * list, int destination,float probability);
void displayList(t_list * list);

#endif

