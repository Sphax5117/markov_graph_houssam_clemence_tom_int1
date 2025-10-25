#include <stdio.h>
#include "list.h"
#include "cell.h"
#include "adjacency.h"

int main() {
    char filename[256];
    #ifdef _WIN32
        snprintf(filename, sizeof(filename), "..\\data\\exemple1.txgtt");
    #else
        snprintf(filename, sizeof(filename), "data/exemple1.txt");
    #endif
    t_adjacency_list * adj;
    adj = readGraph(filename);
    displayAdjacencyList(adj);
    return 0;
}
