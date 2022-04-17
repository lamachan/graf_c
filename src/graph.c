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

	//make a graph without edges
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

	//fill the graph with "rectangular" edges with random weights
	for(i = 0; i < (g->rows * g->columns); i++)
	{
		//vertex not in the topmost row
		if((i / g->columns) != 0)	//(i - columns) - upper neighbour
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
		//vertex not in the leftmost column
		if((i % g->columns) != 0)	//(i - 1) - left neighbour
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
		//vertex not in the righmost column
		if((i % g->columns) != (g->columns - 1))	//(i + 1) - right neighbour
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
		//vertex not in the downmost row
                if((i / g->columns) != (g->rows - 1))	//(i + columns) - lower neighbour
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
	}
}

void split_graph(graph_t g, double w1, double w2)
{
	int start_vertex, finish_vertex;
	int count_edges = 0, connected = 0;
	int i, j;
	path_t p;
	colour_t colour;

	//pick 2 random connected vertices with 3 edges that aren't in the same row or column
	while(connected == 0)
	{
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

        	colour = bfs(g, start_vertex);
        	if(colour[finish_vertex] != white)
        	{
                	connected = 1;
	        }
		free(colour);
	}
	
	//find the shortest path between the 2 vertices
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

	//for all vertices from the path, cut all right and bottom edges
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

	//for all vertices that became entirely disconnected, restore 1 possible edge
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

	free(p->predecessor);
	free(p->distance);
	free(p);
	free(good_path);
}

static int add_neighbour(graph_t g, int vertex, int neighbour, double weight)
{
	if(neighbour < 0 || neighbour >= (g->rows * g->columns) || neighbour == vertex || weight <= 0.0)
	{
		//neighbour not allowed
		return -1;
	}

	//upper neighbour
	if(neighbour == (vertex - g->columns))
	{
		g->v[vertex].neighbour[0] = neighbour;
		g->v[vertex].weight[0] = weight;
		return 0;
	}
	//left neighbour
	if(neighbour == (vertex - 1))
	{
		g->v[vertex].neighbour[1] = neighbour;
		g->v[vertex].weight[1] = weight;
		return 1;
	}
	//right neighbour
	if(neighbour == (vertex + 1))
	{
		g->v[vertex].neighbour[2] = neighbour;
		g->v[vertex].weight[2] = weight;
		return 2;
	}
	//lower neighbour
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

	//read all edges from the input file
        for(i = 0; i < (g->rows * g->columns); i++)
        {
		while(c != '\n' && c != EOF)
		{
			if(fscanf(in, "%d :%lf", &neighbour, &weight) != 2)
			{
				//invalid input file format
				return 1;
			}
			if(add_neighbour(g, i, neighbour, weight) == -1)
			{
				//invalid input file format
				return 1;
			}
			if((c = fgetc(in)) == EOF && i != (g->rows * g->columns - 1))
			{
				//invalid input file format
				return 1;
			}
			if(c == ' ' && (c = fgetc(in)) != '\n')
			{
				ungetc(c, in);
			}
		}
		c = 0;
        }

	return 0;
}

void write_graph(graph_t g, FILE* out)
{
	int i, j;

	fprintf(out, "%d %d\n", g->rows, g->columns);
	for(i = 0; i < (g->rows * g->columns); i++)
	{
		fprintf(out, "\t");
		for(j = 0; j < 4; j++)
		{
			if(g->v[i].neighbour[j] != -1)
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
