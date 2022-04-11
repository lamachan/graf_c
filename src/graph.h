#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<stdio.h>
//#include "bfs.h"

typedef struct vertex
{
	int neighbour[4];	//for v[n]: {(n-columns), (n-1), (n+1), (n+columns)}, (-1) if there is no edge
	double weight[4];	//weight index corresponding with neighbour index, (-1) if there is no edge
} vertex_t;

typedef struct graph
{
	int rows;
	int columns;
	vertex_t *v;
} * graph_t;

graph_t initialise_graph(int rows, int columns);

void generate_graph(graph_t g, double w1, double w2);

void split_graph(graph_t g, int segments);

int read_graph(graph_t g, char *filein);

void write_graph(graph_t g, char *fileoutout);

void print_graph(graph_t g);

void free_graph(graph_t g);

#endif
