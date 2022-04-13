#include "graph.h"
#include "bfs.h"
#include "dijkstry.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

graph_t initialise_graph(int rows, int columns)
{
	int i, j;

	graph_t g = malloc(sizeof *g);
	g->rows = rows;
	g->columns = columns;
	g->v = malloc(rows * columns * sizeof *(g->v));

	for(i = 0; i < rows * columns; i++)
	{
		for(j = 0; j < 4; j++)
		{
			g->v[i].neighbour[j] = -1;
			g->v[i].weight[j] = -1;
		}
	}
	return g;
}

void generate_graph(graph_t g, double w1, double w2)
{
	int i;
	int current_rows = 0, current_columns = 0;
	double w = 0.0;

	srand(time(NULL));

	for(i = 0; i < (g->rows * g->columns); i++)
	{
		if(current_rows != 0)	//(i - columns) - upper neighbour
                {
                        if(g->v[i].neighbour[0] == -1)
			{
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
				g->v[i].neighbour[0] = (i - g->columns);
				g->v[i].weight[0] = w;
				g->v[i-g->columns].neighbour[3] = i;
				g->v[i-g->columns].weight[3] = w;
			}
                }
		if(current_columns != 0)	//(i - 1) - left neighbour
                {
                        if(g->v[i].neighbour[1] == -1)
                        {
                                w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
				g->v[i].neighbour[1] = (i - 1);
				g->v[i].weight[1] = w;
				g->v[i-1].neighbour[2] = i;
				g->v[i-1].weight[2] = w;
                        }
                }
		if(current_columns != (g->columns - 1))	//(i + 1) - right neighbour
                {
                        if(g->v[i].neighbour[2] == -1)
                        {
                                w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->v[i].neighbour[2] = (i + 1);
				g->v[i].weight[2] = w;
				g->v[i+1].neighbour[1] = i;
				g->v[i+1].weight[1] = w;
                        }
                }
                if(current_rows != (g->rows - 1))	//(i + columns) - lower neighbour
                {
                        if(g->v[i].neighbour[3] == -1)
                        {
                                w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->v[i].neighbour[3] = (i + g->columns);
				g->v[i].weight[3] = w;
				g->v[i+g->columns].neighbour[0] = i;
				g->v[i+g->columns].weight[0] = w;
                        }
                }

                current_rows = (i+1) / (g->columns);

                current_columns++;
                current_columns = current_columns % (g->columns);
	}
}

void split_graph(graph_t g, int segments, double w1, double w2)
{
	int start_vertex, finish_vertex;
	int count_edges = 0;
	int i, j;
	path_t p;
	colour_t colour;

	do
	{
		count_edges = 0;
		start_vertex = (g->rows * g->columns) * rand() / RAND_MAX;
		for(i = 0; i < 4; i++)
		{
			if(g->v[start_vertex].neighbour[i] != -1)
                        {
                                count_edges++;
                        }
		}
		if(count_edges != 3)
                {
                        continue;
                }

		count_edges = 0;
		finish_vertex = (g->rows * g->columns) * rand() / RAND_MAX;
		for(i = 0; i < 4; i++)
		{
                        if(g->v[finish_vertex].neighbour[i] != -1)
                        {
                                count_edges++;
                        }
                }
		if(count_edges != 3)
                {
                        continue;
		}


	} while(count_edges != 3 || (start_vertex / g->columns) == (finish_vertex / g->columns) || (start_vertex % g->columns) == (finish_vertex % g->columns));

	printf("Start vertex: %d\nFinish vertex: %d\n", start_vertex, finish_vertex);

	colour = bfs(g, start_vertex);
	if(colour[finish_vertex] == white)
	{
		printf("Disconnected!\n");
		free(colour);

		return;
	}
	
	
	p = dijkstry(g, start_vertex);
	int *good_path = malloc((g->rows * g->columns) * sizeof *good_path);
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
	printf("%d.\n", good_path[i]);

	for(i = no_vertices; i >= 0; i--)
	{
		current_vertex = good_path[i];

		g->v[current_vertex].neighbour[2] = -1;
		g->v[current_vertex].weight[2] = -1;
		if(current_vertex + 1 < (g->rows * g->columns))
		{
			g->v[current_vertex+1].neighbour[1] = -1;
                	g->v[current_vertex+1].weight[1] = -1;
		}
		g->v[current_vertex].neighbour[3] = -1;
		g->v[current_vertex].weight[3] = -1;
		if(current_vertex + g->columns < (g->rows * g->columns))
		{
			g->v[current_vertex+g->columns].neighbour[0] = -1;
			g->v[current_vertex+g->columns].weight[0] = -1;
		}
	}

	double w = 0;

	for(i = 0; i < (g->rows * g->columns); i++)
	{
		count_edges = 0;
		for(j = 0; j < 4; j++)
		{
			if(g->v[i].neighbour[j] != -1)
			{
				count_edges++;
			}
		}
		if(count_edges == 0)
		{
			if((i / g->columns) != 0)   //(i - columns) - upper neighbour
	                {
                        	w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                               	g->v[i].neighbour[0] = (i - g->columns);
                               	g->v[i].weight[0] = w;
	                        g->v[i-g->columns].neighbour[3] = i;
        	                g->v[i-g->columns].weight[3] = w;
                	}
			else if((i % g->columns) != 0)        //(i - 1) - left neighbour
        	        {
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->v[i].neighbour[1] = (i - 1);
                                g->v[i].weight[1] = w;
                                g->v[i-1].neighbour[2] = i;
                                g->v[i-1].weight[2] = w;
                        }
			else if((i % g->columns) != (g->columns - 1)) //(i + 1) - right neighbour
                	{
                                w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->v[i].neighbour[2] = (i + 1);
                                g->v[i].weight[2] = w;
                                g->v[i+1].neighbour[1] = i;
                                g->v[i+1].weight[1] = w;
                        }
			else if((i / g->columns) != (g->rows - 1))       //(i + columns) - lower neighbour
                	{
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->v[i].neighbour[3] = (i + g->columns);
                                g->v[i].weight[3] = w;
                                g->v[i+g->columns].neighbour[0] = i;
                                g->v[i+g->columns].weight[0] = w;
                        }
		}
	}

	free(colour);
	free(p);
	free(good_path);

	/*int start_vertex, first_step;
	int step = 0, count3 = 0, count4 = 0;
	int i, j;
	int *path = malloc((g->rows * g->columns) * sizeof *path);

	while(step == 0)
	{
		start_vertex = (g->rows * g->columns) * rand() / RAND_MAX;
		printf("Try for start vertex: %d\n", start_vertex);
		for(i = 0; i < 4; i++)
		{
			if(g->v[start_vertex].neighbour[i] != -1)
			{
				count3++;
			}
		}
		if(count3 != 3)
		{
			count3 = 0;
			continue;
		}
		printf("Success, start vertex: %d\n", start_vertex);
		for(i = 0; i < 4; i++)
		{
			if(g->v[start_vertex].neighbour[i] == -1)
			{
				 continue;
			}
			first_step = g->v[start_vertex].neighbour[i];
			printf("Try for first step: %d\n", first_step);
			for(j = 0; j < 4; j++)
			{
				if(g->v[first_step].neighbour[j] != -1)
				{
					count4++;
				}
			}
			if(count4 == 4)
			{
				step = 1;
				printf("Success, first step: %d\n", first_step);
				break;
			}
			count4 = 0;
		}
	}
	printf("Start vertex: %d, first step: %d\n", start_vertex, first_step);
	path[0] = start_vertex;
	path[1] = first step;
	count3 = 0;
	count4 = 0;
	int current_vertex = first_step;
	int path_count = 2;

	while(count3 != 3)
	{
		path[path_count] = current_vertex;
		path_count++;
		int direction = 2 + rand() % 2;
		int next_vertex = g->v[current_vertex].neighbour[direction];
		for(i = 0; i < 4; i++)
		{
			if(g->v[next_vertex].neighbour[i] != -1)
			{
				count3++;
			}
		}
		if(count3 != 3)
		{
			count3 = 0;
			continue;
		}
	}*/
}

static int add_neighbour(graph_t g, int vertex, int neighbour, double weight)
{
	if(neighbour < 0 || neighbour >= (g->rows * g->columns) || neighbour == vertex || weight <= 0.0)
	{
		return -1;
	}

	if(neighbour == (vertex - g->columns))
	{
		g->v[vertex].neighbour[0] = neighbour;
		g->v[vertex].weight[0] = weight;
		return 0;
	}
	if(neighbour == (vertex - 1))
	{
		g->v[vertex].neighbour[1] = neighbour;
		g->v[vertex].weight[1] = weight;
		return 1;
	}
	if(neighbour == (vertex + 1))
	{
		g->v[vertex].neighbour[2] = neighbour;
		g->v[vertex].weight[2] = weight;
		return 2;
	}
	if(neighbour == (vertex + g->columns))
	{
		g->v[vertex].neighbour[3] = neighbour;
		g->v[vertex].weight[3] = weight;
		return 3;
	}

	return -1;
}

int read_graph(graph_t g, FILE * in)
{
        int neighbour;
        double weight;
	int i;
	int c = 0;

        for(i = 0; i < (g->rows * g->columns); i++)
        {
		while(c != '\n' && c != EOF)
		{
			if(fscanf(in, "%d :%lf", &neighbour, &weight) != 2)
			{
				return 1;
			}
			if(add_neighbour(g, i, neighbour, weight) == -1)
			{
				return 1;
			}
			if((c = fgetc(in)) == EOF && i != (g->rows * g->columns - 1))
			{
				return 1;
			}
		}
		c = 0;
        }

	return 0;
}

void write_graph(graph_t g, FILE* out)
{

	fprintf(out, "%d %d\n", g->rows, g->columns);
	for (int i = 0; i < (g->rows * g->columns); i++)
	{
		fprintf(out, "\t");
		for (int j = 0; j < 4; j++)
		{
			if (g->v[i].neighbour[j] != -1)
			{
				fprintf(out, "%d :%g ", g->v[i].neighbour[j], g->v[i].weight[j]);
			}
		}
		fprintf(out, "\n");
	}


}

void print_graph(graph_t g)
{
	int i, j;

	printf("Graph:\n");
	for(i = 0; i < (g->rows * g->columns); i++)
	{
		printf("[%d]:\t", i);
		for(j = 0; j < 4; j++)
		{
			if(g->v[i].neighbour[j] != -1)
			{
				printf("(%d:%g) ", g->v[i].neighbour[j], g->v[i].weight[j]);
			}
		}
		printf("\n");
	}
}

void free_graph(graph_t g)
{
	free(g->v);
	free(g);
}
