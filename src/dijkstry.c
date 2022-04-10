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
	int i;

	pq_t q = malloc(sizeof *q);
	q->heap = malloc(size * sizeof *(q->heap));
	q->distance = malloc(size * sizeof *(q->distance));
	q->position = malloc(size * sizeof *(q->position));
	for(i = 0; i < size; i++)
	{
		q->distance[i] = INFINITY;
		q->position[i] = -1;
	}
	q->count = 0;
	
	return q;
}

static void heap_up(pq_t q, int child)
{
	int parent, tmp;

	while(child > 0)
	{
		parent = (child - 1) / 2;
		
		if(q->distance[q->heap[parent]] <= q->distance[q->heap[child]])
		{
			return;
		}

		tmp = q->heap[parent];
		q->heap[parent] = q->heap[child];
		q->heap[child] = tmp;
		
		q->position[q->heap[parent]] = parent;
		q->position[q->heap[child]] = child;

		child = parent;
	}
}

static void heap_down(pq_t q)
{
	int parent = 0, tmp;
	int child = 2 * parent + 1;

	while( child < q->count)
	{
		if((child + 1) < q->count && q->distance[q->heap[child+1]] < q->distance[q->heap[child]])
		{
			child++;
		}
		if(q->distance[q->heap[parent]] <= q->distance[q->heap[child]])
		{
			return;
		}

		tmp = q->heap[parent];
		q->heap[parent] = q->heap[child];
		q->heap[child] = tmp;

		q->position[q->heap[parent]] = parent;
		q->position[q->heap[child]] = child;

		parent = child;
		child = 2 * parent + 1;
	}
}

void push_pq(pq_t q, int vertex, double distance)
{
	q->distance[vertex] = distance;
	if(q->position[vertex] == -1)
	{
		q->heap[q->count++] = vertex;
		q->position[vertex] = q->count - 1;
	}

	heap_up(q, q->position[vertex]);
}

int pop_pq(pq_t q)
{
	int popped = q->heap[0];
	q->heap[0] = q->heap[--q->count];
	q->position[popped] = -1;
	q->position[q->heap[0]] = 0;
#ifdef DEBUG
	printf("Heap before fixing: ");
	print_pq(q);
#endif
	heap_down(q);
#ifdef DEBUG
	printf("Heap after fixing: ");
        print_pq(q);
#endif
	return popped;
}

int is_empty_pq(pq_t q)
{
	return (q->count == 0);
}

void print_pq(pq_t q)
{
	int i;

	printf("[");
	for(i = 0; i < q->count; i++)
	{
		printf(" (%d:%g)", q->heap[i], q->distance[q->heap[i]]);
	}
	printf(" ]\n");
}

void free_pq(pq_t q)
{
	free(q->position);
	free(q->distance);
	free(q->heap);
	free(q);
}

path_t dijkstry(graph_t g, int start_vertex)
{
	int i, current_vertex, neighbour;
	double new_distance;
	int no_vertices = g->rows * g->columns;

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
		for(i = 0; i < 4; i++)
		{
			neighbour = g->v[current_vertex].neighbour[i];
			if(neighbour != -1)
			{
				new_distance = p->distance[current_vertex] + g->v[current_vertex].weight[i];
				if(p->distance[neighbour] > new_distance)
				{
					p->distance[neighbour] = new_distance;
					p->predecessor[neighbour] = current_vertex;
					push_pq(q, neighbour, p->distance[neighbour]);
				}
			}
		}
	}

	free_pq(q);
	
	return p;
}

void find_path(graph_t g, int start_vertex, int finish_vertex)
{
	path_t p = dijkstry(g, start_vertex);
	if(p->predecessor[finish_vertex] == INFINITY)
	{
		printf("The verices %d and %d are disconnected. There is no path between them.\n", start_vertex, finish_vertex);
		
		free(p->predecessor);
		free(p->distance);
		free(p);
		return;
	}
	
	int i;
	int *good_path = malloc((g->rows * g->columns) * sizeof *(good_path));
	int no_vertices = 0;
	int current_vertex = finish_vertex;

	while(current_vertex != start_vertex)
	{
		good_path[no_vertices++] = current_vertex;
		current_vertex = p->predecessor[current_vertex];
	}
	good_path[no_vertices] = current_vertex;

	printf("Path between %d and %d: ", start_vertex, finish_vertex);
	for(i = no_vertices; i > 0; i--)
	{
		printf("%d-", good_path[i]);
	}
	printf("%d.\nThe total distance: %g.\n", good_path[i], p->distance[finish_vertex]);

	free(p->predecessor);
	free(p->distance);
	free(p);
	free(good_path);
}

