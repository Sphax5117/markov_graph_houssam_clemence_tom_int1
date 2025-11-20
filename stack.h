#define NBMAX 1000
#include <stdlib.h>

struct s_stack {
	int values[NBMAX];        
	int nbElts;    
};

typedef struct s_stack t_stack;

int isEmptyStack(t_stack stack);
int pop(t_stack *p_stack);
t_stack * createStack(int nbElts);
void pushStack(int value, t_stack * p_stack);
int top(t_stack * p_stack);