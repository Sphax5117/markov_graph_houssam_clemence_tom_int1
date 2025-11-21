#include "markov.h"

/**
 * @brief Checks if the given graph is a Markov graph.
 *
 * A graph is considered a Markov graph if the sum of probabilities of outgoing edges
 * for each vertex is approximately 1 (between 0.99 and 1.00).
 *
 * @param adj A pointer to the adjacency list representing the graph.
 * @return int Returns 1 if the graph is a Markov graph, 0 otherwise.
 */
int isMarkovGraph(t_adjacency_list * adj) {
    int result = 0;
    printf("\n");
    for (int i = 0; i < adj->size; i++) {
        const t_cell *curr = adj->array[i].head;
        float totalproba = 0;
        while (curr) {
            totalproba+= curr->probability;
            curr = curr->next; 
        }
        if (totalproba <= 1 && totalproba >= 0.99) {
            printf("The sum of probabilities for vertex %d is %.2f\n", i + 1, totalproba);
            result += 1;
        } else {
            printf("The sum of probabilities for vertex %d is %.2f, which is not between 0.99 and 1 \n", i + 1, totalproba);
            return 0;
        }
    }
    return (result == adj->size);
}