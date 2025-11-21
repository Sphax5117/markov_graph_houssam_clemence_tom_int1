#include <stdio.h>
#include <stdlib.h>
#include "hasse.h"


/**
 * @brief Initializes the link array structure.
 *
 * @param la A pointer to the link array to initialize.
 */
void initLink(t_link_array *la)
{
    la->log_size = 0;
    la->size = 1000; 
    la->links = malloc(la->size * sizeof(t_link));//size of the table(allocation for the 1000 t_link)

    if (!la->links) {
        perror("malloc link_array");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Adds a link between two classes to the link array.
 *
 * @param la A pointer to the link array.
 * @param from The source class ID.
 * @param to The destination class ID.
 */
void addLink(t_link_array *la, int from, int to)
{
    //we check if the link exists
    for (int i = 0; i < la->log_size; i++) {
        if (la->links[i].from == from && la->links[i].to == to)
            return; //already present
    }

    // if not enough capacity
    if (la->log_size == la->size) {
        la->size *= 2;
        la->links = realloc(la->links, la->size * sizeof(t_link));
        if (!la->links) {
            perror("realloc link_array");
            exit(EXIT_FAILURE);
        }
    }

    la->links[la->log_size].from = from;
    la->links[la->log_size].to = to;
    la->log_size++;
}
//The fonction above follows the PDF :
//If the link Ci,Cj does not exist
//Add the link Ci,Cj to the structure that stores the links
// Elle :
//vérifie si le lien existe déjà
//agrandit le tableau si besoin
//ajoute le lien à la fin

/**
 * @brief Creates an array mapping each vertex to its corresponding class.
 *
 * @param p A pointer to the partition structure.
 * @param vertextoclass An array to store the class ID for each vertex.
 * @param nb_vertices The number of vertices in the graph.
 */
void createvertextoclass(t_partition *p, int *vertextoclass, int nb_vertices)
{
    for (int i = 0; i <= nb_vertices; i++)
        vertextoclass[i] = -1;

    for (int c = 0; c < p->size; c++) {
        for (int k = 0; k < p->classes[c].size; k++) {
            int v = p->classes[c].vertices[k].id;
            vertextoclass[v] = c;
        }
    }
}
// Same for above
//Create an array that indicates, for each vertex of the graph, the class to which it belongs.
/**
 * @brief Generates the list of links between classes based on the graph and partition.
 *
 * @param p A pointer to the partition structure.
 * @param graph A pointer to the adjacency list of the graph.
 * @param vertextoclass An array mapping vertices to their classes.
 * @param links A pointer to the link array to populate.
 */
void Linkslist(t_partition *p, t_adjacency_list *graph,int *vertextoclass, t_link_array *links)
{
    initLink(links);

    for (int i = 1; i <= graph->size; i++) {
        int Ci = vertextoclass[i];

        t_cell *cur = graph->array[i - 1].head;

        while (cur != NULL) {

            int j = cur->destination;
            int Cj = vertextoclass[j];

            if (Ci != Cj)
                addLink(links, Ci, Cj);

            cur = cur->next;
        }
    }
}
//pseudocode du pro:For each vertex i in the graph
//   Ci = class to which i belongs
//   For all vertices j in adjacency list of vertex i
//      Cj = class to which j belongs
//      If Ci is different from Cj
//         If link (Ci,Cj) does not exist
//            Add link (Ci,Cj)


/**
 * @brief Analyzes and prints the characteristics of the graph (transient, persistent, absorbing, irreducible).
 *
 * @param p A pointer to the partition structure.
 * @param links A pointer to the link array representing connections between classes.
 */
void graphCharacteristics(t_partition *p, t_link_array *links)
{
    printf("\nPART 3 - BEGINNING OF THE TESTS\n");

    int found_absorbing = 0;

    for (int c = 0; c < p->size; c++) {

        int has_outgoing = 0;

        for (int i = 0; i < links->log_size; i++) {
            if (links->links[i].from == c)
                has_outgoing = 1;
        }

        if (has_outgoing)
            printf("Class C%d: transient\n", c + 1);
        else
            printf("Class C%d: persistent\n", c + 1);

        if (!has_outgoing && p->classes[c].size == 1) {
            int s = p->classes[c].vertices[0].id;
            printf("  -> absorbing state: %d\n", s);
            found_absorbing = 1;
        }
    }

    if (!found_absorbing)
        printf("\nNo absorbing states.\n");

    if (p->size == 1)
        printf("\nThe Markov graph is irreducible.\n");
    else
        printf("\nThe Markov graph is NOT irreducible.\n");
}