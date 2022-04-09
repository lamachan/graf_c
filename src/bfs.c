#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>

/*typedef struct fifo_element
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

typedef enum colour {white, gray, black} * colour_t;*/

fifo_t initialise_fifo()
{

}

void push_fifo(fifo_t q, int vertex)
{

}

int pop_fifo(fifo_t q)
{

}

int is_empty_fifo(fifo_t q)
{
	return (q->count == 0);
}

void print_fifo(fifo_t q)
{

}

void free_fifo(fifo_t q)
{

}

colour_t bfs(graph_t g, int start_vertex)
{
	int i, current_vertex, no_vertices = g->rows * g->columns;
	colour_t colour = malloc(no_vertices * sizeof *colour);

	for(i = 0; i < no_vertices; i++)
	{
		colour[i] = white;
	}
	colour[start_vertex] = gray;
	
	fifo_t q = initialise_fifo();
	push_fifo(q, start_vertex);

	while(!is_empty_fifo(q))
	{
		current_vertex = pop_fifo(q);
		for(i = 0; i < no_vertices; i++)
		{
			if(g->matrix[current_vertex][i] != 0 && colour[i] == white)
			{
				colour[i] = gray;
				push_fifo(q, i);
			}
		}
		colour[current_vertex] = black;
	}

}

int check_connectivity(graph_t g)
{

}

