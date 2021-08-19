
#ifndef DEF_funcs
#define DEF_funcs

#include "structures.h"



void addcolumn(listCols *List, char *titre, void *dataType, DATA_NATURE VarType);
void addTableTo(TABLES_LIST *List, tab_row tab);
void print_ALL_Tables(TABLES_LIST L);
char *strtok_rh(char *str, const char *delim, char **nextp); // found in https://stackoverflow.com/questions/12975022/strtok-r-for-mingw



#endif

