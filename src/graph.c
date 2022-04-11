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
}

void split_graph(graph_t g, int segments)
{

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
        //sprawdzenie, czy plik można otworzyć w main.c przed wywołaniem funkcji read_graph

        int rows, columns, neighbour;
        double weight;
	int i;
	int c = 0;

        if(fscanf(in, "%d %d\n", &rows, &columns) != 2)
        {
                return 1;       //interpretacja i komunikat w main.c
        }
        g->rows = rows;
        g->columns = columns;

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


/*int read_graph(graph_t g, char *filein)
{
	int row, column;
	int x1, x2, x3, x4, x5, x6, x7, x8, x9;
	int w1, w2, w3, w4, w5, w6, w7, w8, w9;
	int i1 = 0, j1 = 0;

	FILE* ptr = fopen(filein, "r");
	if (NULL == ptr) {
		fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
		exit(1);
	}

	int function1 = fscanf(ptr, "%d %d\n", &row, &column);
	if (function1 != 2) {
		fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
		exit(1);
	}
	g->rows = row;
	g->columns = column;

	for (i1 = 0; i1 < row; i1++)
	{
		for (j1 = 0; j1 < column; j1++)
		{
			if ((i1 == 0 && j1 == 0) || (i1 == 0 && j1 == column) || (i1 == row && j1 == 0) || (i1 == row && j1 == column)) {
				int function2 = fscanf(ptr, "\t%d :%f %d :%f\n", &x1, &w1, &x2, &w2);
				if (function2 != 4) {
					fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
					exit(1);
				}
				g->v[i1 * column + j1].neighbour[0] = x1;
				g->v[i1 * column + j1].weight[0] = w1;
				g->v[i1 * column + j1].neighbour[1] = x2;
				g->v[i1 * column + j1].weight[1] = w2;

			}
			if ((i1 == 0 && (j1 > 0 && j1 < column)) || (i1 == row && (j1 > 0 && j1 < column)) || (i1 > 0 && i1 < column) && j1 == 0 || (i1 > 0 && i1 < column) && j1 == column) {
				int function3 = fscanf(ptr, "\t%d :%f %d :%f %d :%f\n", &x3, &w3, &x4, &w4, &x5, &w5);
				if (function3 != 6) {
					fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
					exit(1);
				}
				g->v[i1 * column + j1].neighbour[0] = x3;
				g->v[i1 * column + j1].weight[0] = w3;
				g->v[i1 * column + j1].neighbour[1] = x4;
				g->v[i1 * column + j1].weight[1] = w4;
				g->v[i1 * column + j1].neighbour[2] = x5;
				g->v[i1 * column + j1].weight[2] = w5;
			}
			else {
				int function4 = fscanf(ptr, "\t%d :%f %d :%f %d :%f %d :%f\n", &x6, &w6, &x7, &w7, &x8, &w8, &x9, &w9);
				if (function4 != 8) {
					fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
					exit(1);
				}
				g->v[i1 * column + j1].neighbour[0] = x6;
				g->v[i1 * column + j1].weight[0] = w6;
				g->v[i1 * column + j1].neighbour[1] = x7;
				g->v[i1 * column + j1].weight[1] = w7;
				g->v[i1 * column + j1].neighbour[2] = x8;
				g->v[i1 * column + j1].weight[2] = w8;
				g->v[i1 * column + j1].neighbour[3] = x9;
				g->v[i1 * column + j1].weight[3] = w9;
			}
		}
	}
}*/

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
