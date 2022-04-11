#include "graph.h"
#include "bfs.h"
#include "dijkstry.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void help();


int main(int argc, char** argv)
{
    int row = 100;
    int column = 100;
    int n = 1;
    double w1 = 0.1;
    double w2 = 10.01;
    int i;
    int v1, v2;
    char* filein = NULL;
    char* fileout = NULL;
    int flag1 = 0;

    if (argc > 1)
    {
        for (i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "--size") == 0) {
                i++;
                if (i >= argc || atoi(argv[i]) <= 0) {
                    fprintf(stderr, "Error! The flag 'size' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                row = atoi(argv[i]);
                i++;
                if (i >= argc || atoi(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'size' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                column = atoi(argv[i]);
                if (row * column <= 0 || row * column >= 1000000) {
                    fprintf(stderr, "Error! The values of arguments for flag 'size' are outof the allowed range.For further info please refer to the manual.");
                    exit(1);
                }
                flag1 = 1;
            }
            if (strcmp(argv[i], "--weigth") == 0) {
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
                flag1 = 1;

            }
            if (strcmp(argv[i], "--segments") == 0) {
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
                flag1 = 1;
            }
            if (strcmp(argv[i], "--in") == 0) {
                i++;
                if (i >= argc) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                filein = argv[i];
                if (flag1 == 1) {
                    fprintf(stderr, "Error! The flags 'size', 'weight' and 'segments' are mutually exclusive with the flag 'in'.For further info please refer to the manual");
                    exit(1);
                }
            }
            if (strcmp(argv[i], "--out") == 0) {
                i++;
                if (i >= argc) {
                    fprintf(stderr, "Error! The flag 'out' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                fileout = argv[i];
            }
            if (strcmp(argv[i], "--connecivity") == 0) {
                //
            }
            if (strcmp(argv[i], "--path") == 0) {
                i++;
                if (i >= argc || atoi(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                v1 = atof(argv[i]);
                i++;
                if (i >= argc || atoi(argv[i]) == 0) {
                    fprintf(stderr, "Error! The flag 'segments' does not accept the given format of arguments.For further info please refer to the manual");
                    exit(1);
                }
                v2 = atof(argv[i]);
            }
            if (strcmp(argv[i], "--help") == 0) {
                help();
            }
            else {
                fprintf(stderr, "Error! The flag does not exist. For further info please refer to the manual");
                exit(1);
            }
        }
    }

    if (fileout == NULL) {
        // *fileout = "graph.output";
    }

    if (filein == NULL)
    {
        graph_t initialise_graph(int row, int column);
        void generate_graph(graph_t g, double w1, double w2);
    }
    else
    {
        graph_t initialise_graph(int row, int column);
        int read_graph(graph_t g, char* filein);
    }
}

void help() {
    printf("HELP\nGraf - program generujacy i analizujacy grafy\n");
    printf("--size rows columns - rozmiar generowanego grafu\n\tmax rozmiar row x column < 10 ^ 6\n\tdomyslnie: row = 100 column = 100\n");
    printf("--weight w1 w2 - zakres losowanych wag dla krawedzi\n\tw1, w2 >= 0.1; w1,w2 <=100.0\n\tdomyslnie: w1 = 0.1 w2 = 10.0\n");
    printf("--segments - liczba segmentow na ktore podzielony jest graf\n\tn <= 10\n\tdomyslnie: n = 1\n");
    printf("--in - plik wejsciowy\n");
    printf("--out - plik wyjsciowy do ktorego zostanie zapisany graf\n");
    printf("--connectivoty - sprawdzenie spojnosci grafu\n");
    printf("--path v1 v2 - znalezienie sciezki z wierzcholka v1 do v2\n");
    printf("--help\n");
}


