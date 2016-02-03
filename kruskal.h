#ifndef KRUSKAL_H_INCLUDED
#define KRUSKAL_H_INCLUDED
#include "grap_data_struct.h"
//will be used in the intialization
int Make_Heap(vector<Knode> *arr);
//KRUSKAL's MST
int Kruskal(Graph *g);
//DFS for printing out path from s to t
int DFS(Graph *g, unsigned int start, unsigned int dest);
//init graph
void init_data();
#endif // KRUSKAL_H_INCLUDED
