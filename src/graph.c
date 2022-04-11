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
	//wczytanie rows i columns w main.c
        int neighbour;
        double weight;
	int i;
	int c = 0;

        /*if(fscanf(in, "%d %d\n", &rows, &columns) != 2)
        {
                return 1;	//przeniesione do main.c, aby zainicjalizowac graph
        }*/

        for(i = 0; i < (g->rows * g->columns); i++)
        {
		while(c != '\n' && c != EOF)
		{
			if(fscanf(in, "%d :%lf", &neighbour, &weight) != 2)
			{
				return 1;	//interpretacja i komunikat w main.c
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

void write_graph(graph_t g, char* out)
{
	FILE* ptr = fopen(out, "w");
	if (NULL == ptr) {
		fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
		exit(1);
	}

	fprintf(ptr, "%d %d\n", g->rows, g->columns);
	for (int i = 0; i < (g->rows * g->columns); i++)
	{
		fprintf(ptr, "\t");
		for (int j = 0; j < 4; j++)
		{
			if (g->v[i].neighbour[j] != -1)
			{
				fprintf(ptr, "%d :%g ", g->v[i].neighbour[j], g->v[i].weight[j]);
			}
		}
		fprintf(ptr, "\n");
	}

	fclose(ptr);

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
