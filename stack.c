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


int pop(t_stack *p_stack) {
    int value, position;
    position = p_stack->nbElts;
    if (position > 0) {
        value = p_stack->values[position-1];
        p_stack->nbElts = p_stack->nbElts-1;
        return value;
    }
    else {
        return -1;
    }
}

t_stack createStack(int nbElts) {
    t_stack stack;
    stack.nbElts = 0;
    return stack;
}

void pushStack(int value, t_stack * p_stack) {
    int top = p_stack->nbElts;
    p_stack->nbElts += 1;
    p_stack->values[top] = value;
    return;
}

int top(t_stack * p_stack) {
    return p_stack->values[p_stack->nbElts - 1];
}