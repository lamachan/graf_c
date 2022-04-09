#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<stdio.h>
//#include "bfs.h"

typedef struct graph
{
	double **matrix;
	int rows;
	int columns;
} * graph_t;

graph_t initialise_graph(int rows, int columns);

void generate_graph(graph_t g, double w1, double w2);

void split_graph(graph_t g, int segments);

int read_graph(graph_t g, FILE * in);

void write_graph(graph_t g, FILE * out);

void print_graph(graph_t g);

void free_graph(graph_t g);

#endif
