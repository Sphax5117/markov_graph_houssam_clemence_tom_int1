#define NBMAX 1000

struct s_stack {
	int values[NBMAX];        
	int nbElts;    
};

typedef struct s_stack t_stack;

int isEmptyStack(t_stack stack);
int pop(t_stack *p_stack);