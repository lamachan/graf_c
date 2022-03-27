#ifndef _DIJKSTRY_H_
#define _DIJKSTRY_H_

struct pq
{
	int *heap;
	int count;
	double *distance;
	int *position;
} * pq_t;

struct path
{
	int *predecessor;
	double *distance;
} * path_t;

pq_t initialise_pq(int size);

static void heap_up(pq_t q, int child);

static void heap_down(pq_t q);

void push_pq(pq_t q, int vertex, double distance);

int pop_pq(pq_t q);

int is_empty_pq(pq_t q);

void print_pq(pq_t q);

void free_pq(pq_t q);

path_t dijkstry(graph_t g, int start_vertex);

int find_path(graph_t g, int start_vertex, int finish_vertex);

#endif
