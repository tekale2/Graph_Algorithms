#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "grap_data_struct.h"
int normal_dijkstra(Graph *g, unsigned int start, unsigned int dest);
int heap_dijkstra(Graph *g, unsigned int start, unsigned int dest);
#endif // DIJKSTRA_H_INCLUDED
