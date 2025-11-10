#include "mermaid.h"


//Part 3
void mermaidGenerator(t_adjacency_list * adj) {
    FILE *file = fopen("mermaid.txt", "w");
    if (file == NULL) {
        perror("Could not open file for writing");
        return;
    }
    fprintf(file, "---\nconfig:\n   layout: elk\n   theme: neo\n   look: neo\n---\n\nflowchart LR");
    for (int i = 0; i < adj->size;i++) {
        fprintf(file, "\n%s((%d))", getID(i+1), i+1);
    }
    fprintf(file,"\n\n");
    for (int j = 0; j < adj->size;j++) {
        const t_cell *curr = adj->array[j].head;;
        while (curr) {

            fprintf(file, "%s -->|%.2f|%s\n",getID(j+1), curr->probability, getID(curr->destination));
            curr = curr->next; 
        }
    }
    fclose(file);
    return;
}

