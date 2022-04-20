#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

//avaliable arguments short description
void help();
//check if the argument is a natural number (positive int)
int is_int(char* argument);
//check if the argument is a positive double
int is_double(char* argument);

void format_error(char *argument);

void range_error(char *argument);

void unknown_arg_error(char *argument);

void conflict_error(char *argument1, char *argument2, char *argument3, char *conflict);

void file_error(char *argument);

void memory_error();

#endif
