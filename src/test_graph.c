#include "graph.h"
#include <stdio.h>

int main()
{
	graph_t g = initialise_graph(3, 4);

	generate_graph(g, 1, 10);

	print_graph(g);

	return 0;
}
