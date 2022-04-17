#include "graph.h"
#include "bfs.h"
#include "dijkstry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

//avaliable arguments short description
void help();
//check if the argument is a natural number (positive int)
int is_int(char* argument);
//check if the argument is a positive double
int is_double(char* argument);

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
					fprintf(stderr, "Error! The flag 'size' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
					i--;
					continue;
				}
				else
				{
					rows = atoi(argv[i]);
					i++;
					if(i >= argc || is_int(argv[i]) == 0)
                	                {
                        	                fprintf(stderr, "Error! The flag 'size' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                        	i--;
						rows = 100;
                                        	continue;
                                	}
					else
					{
						columns = atoi(argv[i]);
						if(rows * columns == 0 || rows * columns > 1000000)
						{
							fprintf(stderr, "Error! The values of arguments for flag 'size' are out of the allowed range.\nFor further info please refer to the manual.\n");
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
                                        fprintf(stderr, "Error! The flag 'weight' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                        i--;
                                        continue;
                                }
                                else
                                {
                                        w1 = atof(argv[i]);
                                        i++;
                                        if(i >= argc || is_double(argv[i]) == 0)
                                        {
                                                fprintf(stderr, "Error! The flag 'weight' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                                i--;
                                                w1 = 0.0 + DBL_MIN;
                                                continue;
                                        }
                                        else
                                        {
                                                w2 = atof(argv[i]);
                                                if(w1 >= w2)
                                                {
							fprintf(stderr, "Error! The flag 'weight' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                                        w1 = 0.0 + DBL_MIN;
                                                        w2 = 10.0;
                                                        continue;
                                                }
                                                else if(w1 == 0 || w1 > 100 || w2 == 0 || w2 > 100)
                                                {
                                                        fprintf(stderr, "Error! The values of arguments for flag 'weight' are out of the allowed range.\nFor further info please refer to the manual.\n");
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
					fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
					i--;
					continue;
				}
				else
				{
					n = atoi(argv[i]);
					if(n == 0 || n > 10)
					{
						fprintf(stderr, "Error! The values of arguments for flag 'segments' are out of the allowed range.\nFor further info please refer to the manual.\n");
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
					fprintf(stderr, "Error! The flag 'in' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
					continue;
				}
				else if(strstr(argv[i], "--"))
				{
					fprintf(stderr, "Error! The flag 'in' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
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
                                        fprintf(stderr, "Error! The flag 'out' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                        continue;
                                }
				else if(strstr(argv[i], "--"))
                                {
                                        fprintf(stderr, "Error! The flag 'in' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
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
                                        fprintf(stderr, "Error! The flag 'path' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                        i--;
                                        continue;
                                }
                                else
                                {
                                        v1 = atoi(argv[i]);
                                        i++;
                                        if(i >= argc || is_int(argv[i]) == 0)
                                        {
                                                fprintf(stderr, "Error! The flag 'path' does not accept the given format of arguments.\nFor further info please refer to the manual.\n");
                                                i--;
                                                v1 = -1;
                                                continue;
                                        }
                                        else
                                        {
                                                v2 = atoi(argv[i]);
                                                if(v1 == v2)
                                                {
                                                        fprintf(stderr, "Error! The values of arguments for flag 'path' are out of the allowed range.\nFor further info please refer to the manual.\n");
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
				fprintf(stderr, "Error! The flag '%s' does not exist.\nFor further info please refer to the manual.\n", argv[i]);
			}
			else
			{
				continue;
			}
		}
	}

	if(in_conflict == 1 && filein != NULL)
	{
        	fprintf(stderr, "Error! The flags 'size', 'weight' and 'segments' are mutually exclusive with the flag 'in'.\nFor further info please refer to the manual.\n");
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
			fprintf(stderr, "Critical error! Memory allocation fail.\n");
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
			fprintf(stderr, "Error! Incorrect file format.\nFor further info please refer to the manual.\n");
			g = initialise_graph(rows, columns);
			if(g == NULL)
	                {
        	                fprintf(stderr, "Critical error! Memory allocation fail.\n");
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
				fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual.\n");
                		g = initialise_graph(rows, columns);
                		if(g == NULL)
				{
                    			fprintf(stderr, "Critical error! Memory allocation fail.\n");
					return 1;
                		}
                		generate_graph(g, w1, w2);
			}
			else if(rows_in * columns_in <= 0 || rows_in * columns_in > 1000000)
			{
				//invalid input file rows and columns format
				fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual.\n");
                    		g = initialise_graph(rows, columns);
                    		if(g == NULL)
				{
                        		fprintf(stderr, "Critical error! Memory allocation fail.\n");
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
                        		fprintf(stderr, "Critical error! Memory allocation fail.\n");
                        		return 1;
                    		}
                    		if(read_failure = read_graph(g, in) == 1)
				{
					//invalid input file edges format
                        		fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual.\n");
                        		free_graph(g);
                        		g = initialise_graph(rows, columns);
                        		if(g == NULL)
					{
                            			fprintf(stderr, "Critical error! Memory allocation fail.\n");
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
		fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual.\n");
	}
	write_graph(g, out);
	fclose(out);

	//free allocated memory for the graph
	free_graph(g);

	return 0;
}

void help()
{
    printf("HELP\nGraf - program generujacy i analizujacy grafy\n");
    printf("--size rows columns - rozmiar generowanego grafu\n\tmax rozmiar row x column < 10 ^ 6\n\tdomyslnie: row = 100 column = 100\n");
    printf("--weight w1 w2 - zakres losowanych wag dla krawedzi\n\tw1, w2 > 0.0; w1,w2 <= 100.0\n\tdomyslnie: w1 ~ 0.0 w2 = 10.0\n");
    printf("--segments n - liczba segmentow, na ktore podzielony jest graf\n\tn <= 10\n\tdomyslnie: n = 1\n");
    printf("--in filename - plik wejsciowy\n");
    printf("--out filename - plik wyjsciowy, do ktorego zostanie zapisany graf\n\tdomyslnie: filename = graph.output\n");
    printf("--connectivity - sprawdzenie spojnosci grafu\n");
    printf("--path v1 v2 - znalezienie najkrotszej sciezki od wierzcholka v1 do v2\n");
    printf("--help - wyswietlenie tej instrukcji\n");
}

int is_int(char* argument)
{
    int i;

    for (i = 0; i < strlen(argument); i++)
    {
        if (!isdigit(argument[i]))
        {
            return 0;
        }
    }

    return 1;
}

int is_double(char* argument)
{
    int i, dot_count = 0;

    for (i = 0; i < strlen(argument); i++)
    {
        if (!isdigit(argument[i]))
        {
            if (argument[i] == '.' && dot_count == 0)
            {
                dot_count++;
            }
            else
            {
                return 0;
            }
        }
    }

    return 1;
}

