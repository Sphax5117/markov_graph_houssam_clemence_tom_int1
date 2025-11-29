#ifndef __HASSE_H__
#define __HASSE_H__
#include "tarjan.h"

typedef struct {
    int from;
    int to;
} t_link;
//structure that will store one int for the start class and one integer for the end class.

typedef struct {
    t_link *links;   // tableau
    int log_size;    // nombre d'éléments utilisés
    int size;        // capacité allouée
} t_link_array;
//Create a structure to store multiple 'links'.

void initLink(t_link_array *la);

void addLink(t_link_array *la, int from, int to);
//dans le pdf du prof: If the link (Ci,Cj) does not exist
//Add the link (Ci,Cj)

void createvertextoclass(t_partition *p, int *vertextoclass, int nb_vertices);
//Creer un tableau qui indique la class pour chaque vertex
void Linkslist(t_partition *p, t_adjacency_list *graph, int *vertextoclass, t_link_array *links);
//pseudocode du pro:For each vertex i in the graph
//   Ci = class to which i belongs
//   For all vertices j in adjacency list of vertex i
//      Cj = class to which j belongs
//      If Ci is different from Cj
//         If link (Ci,Cj) does not exist
//            Add link (Ci,Cj)
void graphCharacteristics(t_partition *p, t_link_array *links);

#endif