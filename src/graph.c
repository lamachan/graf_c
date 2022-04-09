#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*typedef struct graph
{
        double **matrix;
        int rows;
        int columns;
} * graph_t;*/

graph_t initialise_graph(int rows, int columns)
{
        int i, j;

        graph_t g = malloc(sizeof *g);
        g->matrix = malloc(rows * columns * sizeof *(g->matrix));
        for(i = 0; i < rows * columns; i++)
        {
                g->matrix[i] = malloc(rows * columns * sizeof *(g->matrix[i]));
                for(j = 0; j < rows * columns; j++)
                {
                        g->matrix[i][j] = 0.0;
                }
        }

	g->rows = rows;
	g->columns = columns;

	return g;
}

void generate_graph(graph_t g, double w1, double w2)
{
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

		current_rows = i / (g->columns);

		current_columns++;
		current_columns = current_columns % (g->columns);
	}
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

	printf("Adjacency matrix:\n");
	for(i = 0; i < (g->rows * g->columns); i++)
	{
		printf("[%d]:\t", i);
		for(j = 0; j < (g->rows * g->columns); j++)
		{
			printf("(%d:%g) ", j, g->matrix[i][j]);
		}
		printf("\n");
	}
}

void free_graph(graph_t g)
{
	int i;

	for(i = 0; i < (g->rows * g->columns); i++)
	{
		free(g->matrix[i]);
	}
	free(g->matrix);
	free(g);
}
