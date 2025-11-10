#include "stack.h"


int isEmptyStack(t_stack stack) {
    int res, nbElems;
    nbElems = stack.nbElts;
    if (nbElems == 0) {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}


