#include "mermaid.h"


/**
 * @brief Generates a Mermaid flowchart representation of the graph.
 *
 * Creates a file named "mermaid.txt" containing the graph structure in Mermaid syntax.
 *
 * @param adj A pointer to the adjacency list of the graph.
 */
void mermaidGenerator(t_adjacency_list * adj) {
    FILE *file = fopen("mermaid.txt", "w"); //opening the file
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
    fclose(file); //we don't forget to close the file at the end
    return;
}


void mermaidHasse(t_partition *p, t_link_array *links)
{
    FILE *file = fopen("mermaid_hasse.txt", "w");
    if (file == NULL) {
        perror("Could not open mermaid_hasse.txt for writing");
        return;
    }

    fprintf(file, "---\nconfig:\n   layout: elk\n   theme: neo\n   look: neo\n---\n\nflowchart LR");


    for (int c = 0; c < p->size; c++) {
        fprintf(file, "\nC%d([\"C%d: ", c + 1, c + 1);

        // display vertex
        for (int k = 0; k < p->classes[c].size; k++) {
            int v = p->classes[c].vertices[k].id;
            fprintf(file, "%d", v);
            if (k < p->classes[c].size - 1) {
                fprintf(file, ",");
            }
        }

        fprintf(file, "\"]);");
    }

    fprintf(file, "\n\n");

    for (int i = 0; i < links->log_size; i++) {
        int from = links->links[i].from;
        int to   = links->links[i].to;

        fprintf(file, "C%d --> C%d\n", from + 1, to + 1);
    }

    fclose(file);
}

