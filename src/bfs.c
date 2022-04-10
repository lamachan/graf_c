#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>

fifo_t initialise_fifo()
{
	fifo_t q = malloc(sizeof *q);
	q->count = 0;
	q->front = NULL;
	q->back = NULL;

	return q;
}

void push_fifo(fifo_t q, int vertex)
{
	fifo_element_t *new_element = malloc(sizeof *new_element);
	new_element->vertex = vertex;
	new_element->next = NULL;

	if(!is_empty_fifo(q))
	{
		q->back->next = new_element;
		q->back = new_element;
	}
	else
	{
		q->front = q->back = new_element;
	}
	q->count++;
}

int pop_fifo(fifo_t q)
{
	int popped;
	fifo_element_t *next_node = NULL;
	
	next_node = q->front->next;
	popped = q->front->vertex;
	free(q->front);
	q->front = next_node;
	q->count--;

	return popped;
}

int is_empty_fifo(fifo_t q)
{
	return (q->count == 0);
}

void print_fifo(fifo_t q)
{
	fifo_element_t *tmp = NULL;
	tmp = q->front;

	printf("FIFO: [ ");
	while(tmp != NULL)
	{
		printf("%d ", tmp->vertex);
		tmp = tmp->next;
	}
	printf("]\n");
}

void free_fifo(fifo_t q)
{
	free(q);
}

colour_t bfs(graph_t g, int start_vertex)
{
	int i, current_vertex, neighbour, no_vertices = g->rows * g->columns;
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
#ifdef DEBUG
		print_fifo(q);
#endif
		current_vertex = pop_fifo(q);
		for(i = 0; i < 4; i++)
		{
			neighbour = g->v[current_vertex].neighbour[i];
			if(neighbour != -1 && colour[neighbour] == white)
			{
				colour[neighbour] = gray;
				push_fifo(q, neighbour);
			}
		}
		colour[current_vertex] = black;
	}

	free_fifo(q);

	return colour;
}

void check_connectivity(graph_t g)
{
	colour_t colour = bfs(g, 0);
	int i;
	
	for(i = 0; i < (g->rows * g->columns); i++)
	{
		if(colour[i] != black)
		{
			printf("The graph is disconnected.\n");
			free(colour);
			return;
		}
	}
	printf("The graph is connected.\n");

	free(colour);
}

