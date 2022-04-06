#include "graph.h"
#include <stdlib.h>

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
        g->matrix = malloc(rows * sizeof *(g->matrix));
        for(i = 0; i < rows; i++)
        {
                g->matrix[i] = malloc(columns * sizeof *(g->matrix[i]));
                for(j = 0; j < columns; j++)
                {
                        g->matrix[i][j] = 0;
                }
        }

	g->rows = rows;
	g->columns = columns;

	return g;
}

void generate_graph(graph_t g, double w1, double w2)
{

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

void free_graph(graph_t g)
{
	
}
