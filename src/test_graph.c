#include "graph.h"
#include "dijkstry.h"
#include "bfs.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	//random graph generation test
	graph_t g = initialise_graph(3, 4);

	FILE * in = fopen(argv[1], "r");
	if(in == NULL)
	{
		printf("Blad otwierania!\n");
	}
	int x = read_graph(g, in);
	printf("%d\n", x);

	//generate_graph(g, 1, 10);
#ifdef DEBUG
	print_graph(g);
#endif
	//dijsktry test
	//find_path(g, 0, 567822);

	//check_connectivity(g);

	free_graph(g);

	return 0;
}
