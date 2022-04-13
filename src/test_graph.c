#include "graph.h"
#include "dijkstry.h"
#include "bfs.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	//random graph generation test
	int rows, columns;
	double w1, w2;
	/*FILE * in = fopen(argv[1], "r");
	if(in == NULL)
	{
		printf("Blad otwierania!\n");
	}
	if(fscanf(in, "%d %d\n", &rows, &columns) != 2)
        {
                printf("Zły format rows, columns!\n");
		return 1;
        }*/
	rows = 100;
	columns = 100;
	w1 = 0.0;
	w2 = 10.0;

	graph_t g = initialise_graph(rows, columns);
	
	/*int x = read_graph(g, in);
	printf("%d\n", x);*/

	generate_graph(g, w1, w2);

	print_graph(g);

	//write_graph(g, argv[1]);
	//dijsktry test
	//find_path(g, 0, 6);

	//check_connectivity(g);

	split_graph(g, 2, w1, w2);
	
	check_connectivity(g);

	print_graph(g);

	free_graph(g);

	return 0;
}
