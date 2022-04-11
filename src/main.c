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
        char* filein;
        char* fileout;
        char fileoutdef[] = "graph.output";

        if (argc > 1)
        {
            for (i = 1; i < argc; i++)
            {
                if (strcmp(argv[i], "--size") == 0) {
                    i++;
                    if (i >= argc || atoi(argv[i]) <= 0) {
                        fprintf(stderr, "Argument musi byc liczba");
                    }
                    row = atoi(argv[i]);
                    i++;
                    if (i >= argc || atoi(argv[i]) == 0) {
                        fprintf(stderr, "Argument musi byc liczba");
                    }
                    column = atoi(argv[i]);
                    if (row * column == 0) {
                        fprintf(stderr, "Argument przy --size nie moze byc rowny 0");
                    }
                    if (row * column <= 1000000) {
                        fprintf(stderr, "Za duze arguementy, row*columns <= 1000000");
                    }
                }
                if (strcmp(argv[i], "--weigth") == 0) {
                    i++;
                    if (i >= argc || atof(argv[i]) == 0) {
                        fprintf(stderr, "Argument musi byc liczba typu double");
                    }
                    w1 = atof(argv[i]);
                    i++;
                    if (i >= argc || atof(argv[i]) == 0) {
                        fprintf(stderr, "Argument musi byc liczba typu double");
                    }
                    w2 = atof(argv[i]);
                    if (w1 >= w2) {
                        fprintf(stderr, "w1 nie moze byc wieksze od w2");
                    }
                    if (w1 <= 0 || w1 > 100 || w2 <= 0 || w2 > 100) {
                        fprintf(stderr, "Zakres lowsowanych wag musi zawierac sie w przedziale (0.0, 100.0>");
                    }

                }
                if (strcmp(argv[i], "--segments") == 0) {
                    i++;
                    if (i >= argc || atoi(argv[i]) == 0) {
                        fprintf(stderr, "Argument musi byc liczba");
                    }
                    n = atoi(argv[i]);
                    if (n < 1 || n > 10) {
                        fprintf(stderr, "Argument musi zawierac sie w przedziale <1, 10>");
                    }
                }
                if (strcmp(argv[i], "--in") == 0) {
                    i++;
                    if (i >= argc) {
                        fprintf(stderr, "Brak argumentu");
                    }
                    filein = argv[i];
                    if (column != 100 || row != 100 || w2 != 10.0 || w1 != 0.1 || n != 1) {
                        fprintf(stderr, "Argument --in nie moze byc uzywany z argumentami --size, --weight, --segments");
                    }
                }
                if (strcmp(argv[i], "--out") == 0) {
                    i++;
                    if (i >= argc) {
                        fprintf(stderr, "Brak argumentu");
                    }
                    fileout = argv[i];
                }
                if (strcmp(argv[i], "--connecivity") == 0) {
                    //
                }
                if (strcmp(argv[i], "--path") == 0) {
                    i++;
                    if (i >= argc || atoi(argv[i]) == 0) {
                        fprintf(stderr, "Argument musi byc wierzcholkiem (liczba)");
                    }
                    v1 = atof(argv[i]);
                    i++;
                    if (i >= argc || atoi(argv[i]) == 0) {
                        fprintf(stderr, "Argument musi byc wierzcholkiem (liczba)");
                    }
                    v2 = atof(argv[i]);
                }
                if (strcmp(argv[i], "--help") == 0) {
                    help();
                }
                else {
                    fprintf(stderr, "Podano bledne flage");
                }
            }
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
