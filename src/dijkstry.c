#include "dijkstry.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*typedef struct pq
{
        int *heap;
        int count;
        double *distance;
        int *position;
} * pq_t;

typedef struct path
{
        int *predecessor;
        double *distance;
} * path_t;*/

pq_t initialise_pq(int size)
{

}

static void heap_up(pq_t q, int child)
{

}

static void heap_down(pq_t q)
{

}

void push_pq(pq_t q, int vertex, double distance)
{

}

int pop_pq(pq_t q)
{

}

int is_empty_pq(pq_t q)
{

}

void print_pq(pq_t q)
{

}

void free_pq(pq_t q)
{

}

path_t dijkstry(graph_t g, int start_vertex)
{
	int i, current_vertex;
	double new_distance;
	int no_vertices = g->rows * g->columns;

	if(start_vertex < 0 || start_vertex > (no_vertices - 1))
	{
		return NULL;
	}
	
	path_t p = malloc(sizeof *p);
	p->predecessor = malloc(no_vertices * sizeof *(p->predecessor));
	p->distance = malloc(no_vertices * sizeof *(p->distance));
	
	for(i = 0; i < (no_vertices); i++)
	{
		p->predecessor[i] = -1;
		p->distance[i] = INFINITY;
	}

	pq_t q = initialise_pq(no_vertices);

	p->distance[start_vertex] = 0.0;
	push_pq(q, start_vertex, p->distance[start_vertex]);

	while(is_empty_pq(q) != 1)
	{
		current_vertex = pop_pq(q);
		for(i = 0; i < no_vertices; i++)
		{
			if(g->matrix[current_vertex][i] != 0.0)
			{
new_distance = p->distance[current_vertex] + g->matrix[current_vertex][i];
				if(p->distance[i] > new_distance)
				{
					p->distance[i] = new_distance;
					p->predecessor[i] = current_vertex;
					push_pq(q, i, p->distance[i]);
				}
			}
		}
	}
	
	return p;
}

int find_path(graph_t g, int start_vertex, int finish_vertex)
{

}

