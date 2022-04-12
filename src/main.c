#include "graph.h"
#include "bfs.h"
#include "dijkstry.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

void help() {
    printf("HELP\nGraf - program generujacy i analizujacy grafy\n");
    printf("--size rows columns - rozmiar generowanego grafu\n\tmax rozmiar row x column < 10 ^ 6\n\tdomyslnie: row = 100 column = 100\n");
    printf("--weight w1 w2 - zakres losowanych wag dla krawedzi\n\tw1, w2 > 0.0; w1,w2 <= 100.0\n\tdomyslnie: w1 ~ 0.0 w2 = 10.0\n");
    printf("--segments n - liczba segmentow, na ktore podzielony jest graf\n\tn <= 10\n\tdomyslnie: n = 1\n");
    printf("--in filename - plik wejsciowy\n");
    printf("--out filename - plik wyjsciowy, do ktorego zostanie zapisany graf\n\tdomyslnie: filename = graph.output\n");
    printf("--connectivity - sprawdzenie spojnosci grafu\n");
    printf("--path v1 v2 - znalezienie najkrotszej sciezki od wierzcholka v1 do v2\n");
    printf("--help - wysietlenie tej instrukcji\n");
}

int is_int(char *argument)
{
	int i;
	
	for(i = 0; i < strlen(argument); i++)
	{
		if(!isdigit(argument[i]))
		{
			return 0;
		}
	}
	
	return 1;
}

int is_double(char *argument)
{
	int i, dot_count = 0;

	for(i = 0; i < strlen(argument); i++)
	{
		if(!isdigit(argument[i]))
		{
			if(argument[i] = '.' && dot_count == 0)
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

int main(int argc, char** argv)
{
    int rows = 100;
    int columns = 100;
    int n = 1;
    double w1 = 0.0 + DBL_MIN;
    double w2 = 10.0;
    int i, j;
    int v1 = 0, v2 = 0;
    char* filein = NULL;
    char* fileout = NULL;
    char fd[] = "graph.output";
    int in_conflict = 0, connectivity = 0;
    graph_t g = NULL;

    if (argc > 1)
    {
        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "--size") == 0) {
                i++;
                if (i >= argc || is_int(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'size' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                rows = atoi(argv[i]);
                i++;
                if (i >= argc || atoi(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'size' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                columns = atoi(argv[i]);
                if (rows * columns <= 0 || rows * columns > 1000000) {
                    fprintf(stderr, "Error! The values of arguments for flag 'size' are outof the allowed range.For further info please refer to the manual.");
                    exit(1);
                }
                in_conflict = 1;
            }
            else if (strcmp(argv[i], "--weigth") == 0) {
                i++;
                if (i >= argc || atof(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'weight' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                w1 = atof(argv[i]);
                i++;
                if (i >= argc || atof(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'weight' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                w2 = atof(argv[i]);
                if (w1 >= w2) {
                    fprintf(stderr, "Error! The flag 'weight' does not accept the given format of arguments. For further info please refer to the manual");
                    exit(1);
                }
                if (w1 <= 0 || w1 > 100 || w2 <= 0 || w2 > 100) {
                    fprintf(stderr, "Error! The values of arguments for flag 'weight' are outof the allowed range.For further info please refer to the manual");
                    exit(1);
                }
                in_conflict = 1;

            }
            else if (strcmp(argv[i], "--segments") == 0) {
                i++;
                if (i >= argc || atoi(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                n = atoi(argv[i]);
                if (n < 1 || n > 10) {
                    fprintf(stderr, "Error! The values of arguments for flag 'segments' are outof the allowed range.For further info please refer to the manual");
                    exit(1);
                }
                in_conflict = 1;
            }
            else if (strcmp(argv[i], "--in") == 0) {
                i++;
                if (i >= argc) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                filein = argv[i];
                if (in_conflict == 1) {
                    fprintf(stderr, "Error! The flags 'size', 'weight' and 'segments' are mutually exclusive with the flag 'in'.For further info please refer to the manual");
                    exit(1);
                }
            }
            else if (strcmp(argv[i], "--out") == 0) {
                i++;
                if (i >= argc) {
                    fprintf(stderr, "Error! The flag 'out' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                fileout = argv[i];
            }
            else if (strcmp(argv[i], "--connecivity") == 0) {
                connectivity = 1;
            }
            else if (strcmp(argv[i], "--path") == 0) {
                i++;
                if (i >= argc || atoi(argv[i]) <= 0) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                v1 = atoi(argv[i]);
                i++;
                if (i >= argc || atoi(argv[i]) <= 0) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                v2 = atoi(argv[i]);
            }
            else if (strcmp(argv[i], "--help") == 0) {
                help();
            }
            else {
                fprintf(stderr, "Error! The flag does not exist. For further info please refer to the manual");
                exit(1);
            }
        }
    }

    if (fileout == NULL) {
        fileout = fd;
    }

    if (filein == NULL)
    {
        g = initialise_graph(rows, columns);
        generate_graph(g, w1, w2);

    }
    else
    {
        FILE * in = fopen(filein, "w");
        if (in == NULL) {
            fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
            exit(1);
        }
        if (fscanf(in, "%d %d\n", &rows, &columns) != 2) {
            fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
            exit(1);
        }

        g = initialise_graph(rows, columns);
        if (read_graph(g, in) == 1) {
            fprintf(stderr, "Error! Incorrect file format. For further info please refer to the manual");
            exit(1);
        }
        fclose(in);
    }

#ifdef DEBUG
    print_graph(g);
#endif

    if (connectivity == 1) {
        check_connectivity(g);
    }

    write_graph(g, fileout);

    free_graph(g);

    return 0;
}
