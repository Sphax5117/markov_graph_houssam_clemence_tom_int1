#ifndef CELL_H
#define CELL_H
typedef struct s_cell {
    int destination;
    float probability;
    struct s_cell *next;
} t_cell;

t_cell *createCell(int destination, float probability);
#endif