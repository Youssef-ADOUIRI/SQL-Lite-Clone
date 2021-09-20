#ifndef DEF_tabs
#define DEF_tabs

#include "structures.h"

#define STANDARD_ALLOCATION_SIZE 45

table *tab_all[40];


void addcolumn(listCols *List, char *titre, void *dataType, DATA_NATURE VarType , tab_header*);
void addTableTo(listCols List ,char* , u_int);
bool find_table(const char* , table *);
void addHeadersTab(tab_header);
void destroy_all_tabHeaders(void);
void destroyTabHeader(tab_header);
void *transfertToType(char *, DATA_NATURE *);
void showALLTabs();
void printTable(table*);
void printTable_header(listCols);


#endif
