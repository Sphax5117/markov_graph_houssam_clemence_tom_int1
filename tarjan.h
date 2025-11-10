//
// Created by cleme on 07/11/2025.
//

#ifndef INC_2526_TI301_PJT_TARJAN_H
#define INC_2526_TI301_PJT_TARJAN_H
#include "adjacency.h"
//algo réccursif donc il doit sauvegarder les indo
typedef struct s_tarjan_vertex{
    int id;
    int number;
    int accessnb;
    int boolind;
}t_tarjan_vertex;
// on ne sait pas a l'avance le nombre de sommets et aussi le nb de classes donc il faut alloué dynamiquement
// sinon on doit fixer une taille max et risque de dépassement

typedef struct s_class{
    char name[10];
    t_tarjan_vertex * vertices;// tableau qui contient TOUS les sommets
    int size;//nb sommet
    int capacity;
}t_class;

typedef struct s_partition{
    t_class * classes;
    int size;//nombre de classe trouvé
    int capacity;//capacité mémoire alloué
}t_partition;

t_tarjan_vertex*tarjanArr(t_adjacency_list*graph);

#endif //INC_2526_TI301_PJT_TARJAN_H
