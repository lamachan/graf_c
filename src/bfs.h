#ifndef _BFS_H_
#define _BFS_H_

#include "graph.h"

typedef struct fifo_element
{
	int vertex;
	struct fifo_element *next;
} fifo_element_t;

typedef struct fifo
{
	int count;
	fifo_element_t *front;
	fifo_element_t *back;
} * fifo_t;

typedef enum colour {white, gray, black} * colour_t;

fifo_t initialise_fifo();

void push_fifo(fifo_t q, int vertex);

int pop_fifo(fifo_t q);

int is_empty_fifo(fifo_t q);

void print_fifo(fifo_t q);

void free_fifo(fifo_t q);

colour_t bfs(graph_t g, int start_vertex);

int check_connectivity(graph_t g);

#endif
