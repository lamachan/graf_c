#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<stdio.h>

typedef struct graph
{
	double **matrix;
	int rows;
	int columns;
} * graph_t;

graph_t initialise_graph(int rows, int columns);

void generate_graph(graph_t g, double w1, double w2);

int read_graph(graph_t g, FILE * in);

void write_graph(graph_t g, FILE * out);

void free_graph(graph_t g);

#endif
