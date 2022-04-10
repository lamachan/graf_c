#include "graph.h"
#include "dijkstry.h"
#include "bfs.h"
#include <stdio.h>

int main()
{
	//random graph generation test
	graph_t g = initialise_graph(1000, 1000);

	generate_graph(g, 1, 10);
#ifdef DEBUG
	print_graph(g);
#endif
	//dijsktry test
	find_path(g, 0, 567822);

	check_connectivity(g);

	free_graph(g);

	return 0;
}
