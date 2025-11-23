#ifndef __MERMAID_H__
#define __MERMAID_H__
#include "adjacency.h"
#include "utils.h"
#include "tarjan.h"
#include "hasse.h"
void mermaidGenerator(t_adjacency_list * adj);
void mermaidHasse(t_partition *p, t_link_array *links);

#endif