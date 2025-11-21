#include "stack.h"

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack The stack structure to check.
 * @return int Returns 1 if the stack is empty, 0 otherwise.
 */
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



/**
 * @brief Pops an element from the top of the stack.
 *
 * @param p_stack A pointer to the stack.
 * @return int The value popped from the stack, or -1 if the stack is empty.
 */
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

/**
 * @brief Creates a new stack with a specified capacity.
 *
 * @param nbElts The maximum number of elements the stack can hold (not used in current implementation, fixed size implied or dynamic allocation missing for values).
 * Note: The current implementation allocates the stack structure but assumes 'values' is a fixed array in the struct definition (based on usage).
 *
 * @return t_stack* A pointer to the newly created stack.
 */
t_stack * createStack(int nbElts) {
    t_stack * stack = (t_stack *)malloc(sizeof(t_stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->nbElts = 0;
    return stack;
}

/**
 * @brief Pushes a value onto the stack.
 *
 * @param value The value to push.
 * @param p_stack A pointer to the stack.
 */
void pushStack(int value, t_stack * p_stack) {
    int top = p_stack->nbElts;
    p_stack->nbElts += 1;
    p_stack->values[top] = value;
    return;
}

/**
 * @brief Returns the value at the top of the stack without removing it.
 *
 * @param p_stack A pointer to the stack.
 * @return int The value at the top of the stack.
 */
int top(t_stack * p_stack) {
    return p_stack->values[p_stack->nbElts - 1];
}