#include "graph.h"
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
	int i, j;
	int current_rows = 0, current_columns = 0;
	double w = 0.0;

	srand(time(NULL));

	for(i = 0; i < (g->rows * g->columns); i++)
	{
		if(current_rows != 0)	//i-columns
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
		if(current_columns != 0)
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
		if(current_columns != (g->columns - 1))
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
                if(current_rows != (g->rows - 1))
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



/*
	int i, j;
	int size = g->rows * g->columns;
	int current_rows = 0, current_columns = 0;
	double w = 0.0;
	
	srand(time(NULL));

	for(i = 0; i < size; i++)
	{
		if(current_columns != (g->columns - 1))
		{
			if(g->matrix[i][i+1] == 0.0)
			{
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
				g->matrix[i][i+1] = w;
				g->matrix[i+1][i] = w;
			}
		}

		if(current_columns != 0)
		{
			if(g->matrix[i][i-1] == 0.0)
			{
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->matrix[i][i-1] = w;
                                g->matrix[i-1][i] = w;
	
			}
		}

		if(current_rows != 0)
		{
			if(g->matrix[i][i-(g->columns)] == 0.0)
			{
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->matrix[i][i-(g->columns)] = w;
                                g->matrix[i-(g->columns)][i] = w;
			}
		}

		if(current_rows != (g->rows - 1))
		{
			if(g->matrix[i][i+(g->columns)] == 0.0)
			{
				w = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
                                g->matrix[i][i+(g->columns)] = w;
 				g->matrix[i+(g->columns)][i] = w;

			}
		}

		current_rows = (i+1) / (g->columns);

		current_columns++;
		current_columns = current_columns % (g->columns);
	}*/
}

void split_graph(graph_t g, int segments)
{

}

int read_graph(graph_t g, FILE * in)
{

}

void write_graph(graph_t g, FILE * out)
{

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
