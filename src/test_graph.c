#include "graph.h"
#include "dijkstry.h"
#include "bfs.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	//random graph generation test
	int rows, columns;
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
	rows = 3;
	columns = 4;
	graph_t g = initialise_graph(rows, columns);
	
	/*int x = read_graph(g, in);
	printf("%d\n", x);*/

	generate_graph(g, 1, 10);
#ifdef DEBUG
	print_graph(g);
#endif
	write_graph(g, argv[1]);
	//dijsktry test
	//find_path(g, 0, 567822);

	//check_connectivity(g);

	free_graph(g);

	return 0;
}
