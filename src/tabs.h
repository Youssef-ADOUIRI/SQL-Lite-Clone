#ifndef DEF_tabs
#define DEF_tabs

#include "structures.h"

#define STANDARD_ALLOCATION_SIZE 45

table *tab_all[40];


void addcolumn(listCols *List, char *titre, size_t memorySize, DATA_NATURE VarType, tab_header *headerTab);
void addTableTo(table*);
table* find_table(const char*);
void print_Constrains(column);
void destroy_all_tabHeaders(void);

size_t transfertToType(char *, DATA_NATURE *);
void showALLTabs();
void printTable_header(listCols);


#endif
