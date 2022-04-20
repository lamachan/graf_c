#include <stdio.h>
#include <string.h>
#include <ctype.h>

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


void format_error(char *argument)
{
	fprintf(stderr, "Error! The flag '%s' does not accept the given format of arguments.\nFor further info please refer to the manual.\n", argument);
}

void range_error(char *argument)
{
	fprintf(stderr, "Error! The values of arguments for flag '%s' are out of the allowed range.\nFor further info please refer to the manual.\n", argument);
}

void unknown_arg_error(char *argument)
{
	fprintf(stderr, "Error! The flag '%s' does not exist.\nFor further info please refer to the manual.\n", argument);
}

void conflict_error(char *argument1, char *argument2, char *argument3, char *conflict)
{
	fprintf(stderr, "Error! The flags '%s', '%s' and '%s' are mutually exclusive with the flag '%s'.\nFor further info please refer to the manual.\n", argument1, argument2, argument3, conflict);
}

void file_error(char *argument)
{
	fprintf(stderr, "Error! Incorrect '%s' file format.\nFor further info please refer to the manual.\n", argument);
}

void memory_error()
{
	fprintf(stderr, "Critical error! Memory allocation fail.\n");
}