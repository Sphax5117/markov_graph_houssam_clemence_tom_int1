#include <stdio.h>
#include "list.h"
#include "cell.h"
#include "adjacency.h"

int main() {
    char * filename;
    printf("Filename : ");
    scanf("%s", &filename);
    readGraph(filename);
    return 0;
}
