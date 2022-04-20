#include "arguments.h"
#include "graph.h"
#include "bfs.h"
#include "dijkstry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

int main(int argc, char **argv)
{
	int rows = 100, columns = 100;
	int rows_in = 0, columns_in = 0;
	double w1 = 0.0 + DBL_MIN, w2 = 10.0;
	int n = 1;
	int v1 = -1, v2 = -1;
	char *filein = NULL;
	char *fileout = "graph.output";
	int read_failure = 1;
	int in_conflict = 0;
	int connectivity = 0, path = 0;
	graph_t g = NULL;
	int i;

	//check the user-provided arguments
	if(argc > 1)
	{
		for(i = 1; i < argc; i++)
		{
			if(strcmp(argv[i], "--size") == 0)
			{
				i++;
				if(i >= argc || is_int(argv[i]) == 0)
				{
					format_error(argv[i-1]);
					i--;
					continue;
				}
				else
				{
					rows = atoi(argv[i]);
					i++;
					if(i >= argc || is_int(argv[i]) == 0)
                	                {
                                        	format_error(argv[i-2]);
						i--;
						rows = 100;
                                        	continue;
                                	}
					else
					{
						columns = atoi(argv[i]);
						if(rows * columns == 0 || rows * columns > 1000000)
						{
							range_error(argv[i-2]);
							rows = 100;
							columns = 100;
							continue;
						}
						else
						{
							in_conflict = 1;
						}
					}
				}
			}
			else if(strcmp(argv[i], "--weight") == 0)
			{
				i++;
                           	if(i >= argc || is_double(argv[i]) == 0)
                                {
                                        format_error(argv[i-1]);
					i--;
                                        continue;
                                }
                                else
                                {
                                        w1 = atof(argv[i]);
                                        i++;
                                        if(i >= argc || is_double(argv[i]) == 0)
                                        {
                                                format_error(argv[i-2]);
						i--;
                                                w1 = 0.0 + DBL_MIN;
                                                continue;
                                        }
                                        else
                                        {
                                                w2 = atof(argv[i]);
                                                if(w1 >= w2)
                                                {
                                                        range_error(argv[i-2]);
							w1 = 0.0 + DBL_MIN;
                                                        w2 = 10.0;
                                                        continue;
                                                }
                                                else if(w1 == 0 || w1 > 100 || w2 == 0 || w2 > 100)
                                                {
                        				range_error(argv[i-2]);
							w1 = 0.0 + DBL_MIN;
                        				w2 = 10.0;
							continue;
                                                }
						else
						{
							in_conflict = 1;
						}
                                        }
                                }

			}
			else if(strcmp(argv[i], "--segments") == 0)
			{
				i++;
				if(i >= argc || is_int(argv[i]) == 0)
				{
					format_error(argv[i-1]);
					i--;
					continue;
				}
				else
				{
					n = atoi(argv[i]);
					if(n == 0 || n > 10)
					{
						range_error(argv[i-1]);
						n = 1;
						continue;
					}
					else
					{
						in_conflict = 1;
					}
				}
			}
			else if(strcmp(argv[i], "--in") == 0)
                        {
				i++;
				if(i >= argc)
				{
					format_error(argv[i-1]);
					continue;
				}
				else if(strstr(argv[i], "--"))
				{
					format_error(argv[i-1]);
					i--;
					continue;
				}
				else
				{
					filein = argv[i];
				}
                        }
			else if(strcmp(argv[i], "--out") == 0)
                        {
				i++;
                                if(i >= argc)
                                {
                                        format_error(argv[i-1]);
					continue;
                                }
				else if(strstr(argv[i], "--"))
                                {
                                        format_error(argv[i-1]);
					i--;
                                        continue;
                                }
                                else
                                {
                                        fileout = argv[i];
                                }
                        }
			else if(strcmp(argv[i], "--connectivity") == 0)
                        {
				connectivity = 1;
                        }
			else if(strcmp(argv[i], "--path") == 0)
                        {
				i++;
                                if(i >= argc || is_int(argv[i]) == 0)
                                {
                                        format_error(argv[i-1]);
					i--;
                                        continue;
                                }
                                else
                                {
                                        v1 = atoi(argv[i]);
                                        i++;
                                        if(i >= argc || is_int(argv[i]) == 0)
                                        {
                                                format_error(argv[i-2]);
						i--;
                                                v1 = -1;
                                                continue;
                                        }
                                        else
                                        {
                                                v2 = atoi(argv[i]);
                                                if(v1 == v2)
                                                {
                                                        range_error(argv[i-2]);
							v1 = -1;
                                                        v2 = -1;
                                                        continue;
                                                }
                                                else
                                                {
                                                        path = 1;
                                                }
                                        }
                                }

                        }
			else if(strcmp(argv[i], "--help") == 0)
                        {
				help();
                        }
			else if(strstr(argv[i], "--") != NULL)
			{
				unknown_arg_error(argv[i]);
			}
			else
			{
				continue;
			}
		}
	}

	if(in_conflict == 1 && filein != NULL)
	{
		conflict_error("--size", "--weight", "--segments", "--in");
		rows = 100;
		columns = 100;
		w1 = 0.0 + DBL_MIN;
		w2 = 10.0;
		n = 1;
        }
	
#ifdef DEBUG
	printf("Size: rows = %d, columns = %d\n", rows, columns);
	printf("Weight: w1 = %g, w2 = %g\n", w1, w2);
	printf("Segments: n = %d\n", n);
	printf("In: filein = %s\n", filein);
	printf("Out: fileout = %s\n", fileout);
	printf("Connectivity: connectivity = %d\n", connectivity);
	printf("Path: path = %d, v1 = %d, v2 = %d\n", path, v1, v2);
	printf("Inconflict: inconflict = %d\n", in_conflict);
#endif
	
	//input file has not been provided
	if(filein == NULL)
	{
		g = initialise_graph(rows, columns);
		if(g == NULL)
		{
			memory_error();
			return 1;
		}
		generate_graph(g, w1, w2);
	}
	//input file has been provided
	else
	{
		FILE * in = fopen(filein, "r");
		//invalid input file
		if(in == NULL)
		{
			file_error(filein);
			g = initialise_graph(rows, columns);
			if(g == NULL)
	                {
                	        memory_error();
				return 1;
                	}
                	generate_graph(g, w1, w2);	
		}
		//valid input file
		else
		{
			if(fscanf(in, "%d %d\n", &rows_in, &columns_in) != 2)
			{
				//invalid input file rows and columns format
                		file_error(filein);
				g = initialise_graph(rows, columns);
                		if(g == NULL)
				{
					memory_error();
					return 1;
                		}
                		generate_graph(g, w1, w2);
			}
			else if(rows_in * columns_in <= 0 || rows_in * columns_in > 1000000)
			{
				//invalid input file rows and columns format
                    		file_error(filein);
				g = initialise_graph(rows, columns);
                    		if(g == NULL)
				{
                        		memory_error();
					return 1;
                    		}
                    		generate_graph(g, w1, w2);
			}
			//valid input file rows and columns format
			else
			{
				g = initialise_graph(rows_in, columns_in);
				if(g == NULL)
				{
                        		memory_error();
					return 1;
                    		}
                    		if(read_failure = read_graph(g, in) == 1)
				{
					//invalid input file edges format
                        		file_error(filein);
					free_graph(g);
                        		g = initialise_graph(rows, columns);
                        		if(g == NULL)
					{
                            			memory_error();
						return 1;
                        		}
                        		generate_graph(g, w1, w2);
				}
			}
		}
		fclose(in);
	}
	
#ifdef DEBUG_GRAPH
	//before splitting
	print_graph(g);
#endif

	//split graph into n-segments
	if(n > 1)
	{
		for(i = 1; i < n; i++)
		{
			split_graph(g, w1, w2);
		}
	}

#ifdef DEBUG_GRAPH
	//after splitting
	print_graph(g);
#endif

	//check connectivity
	if(connectivity == 1)
	{
		check_connectivity(g);
	}

	if(read_failure == 0)
	{
		rows = rows_in;
		columns = columns_in;
	}
	if(v1 > (rows * columns - 1) || v2 > (rows * columns - 1))
	{
		range_error("--path");
		path = 0;
	}
	//find path
	if(path == 1)
	{
		find_path(g, v1, v2);
	}

	//print graph into an output file
	FILE * out = fopen(fileout, "w");
	if(out == NULL)
	{
		file_error(fileout);
	}
	write_graph(g, out);
	fclose(out);

	//free allocated memory for the graph
	free_graph(g);

	return 0;
}