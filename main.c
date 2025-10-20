#include <stdio.h>
#include "list.h"
#include "cell.h"
#include "adjacency.h"

int main() {
    char filename[100]="data/exemple1.txt";

    t_adjacency_list * adj;
    adj = readGraph(filename);
    displayAdjacencyList(adj);
    return 0;
}
