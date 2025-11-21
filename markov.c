#include "markov.h"

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