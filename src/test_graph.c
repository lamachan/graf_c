#include "graph.h"
#include "dijkstry.h"
#include <stdio.h>

int main()
{
	//random graph generation test
	graph_t g = initialise_graph(300, 100);

	generate_graph(g, 1, 10);

	//print_graph(g);

	//dijsktry test
	find_path(g, 0, 567);

	return 0;
}
