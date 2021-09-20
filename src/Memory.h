#ifndef DEF_Memory
#define DEF_Memory

#include "structures.h"

#define MAX_PAGE_SIZE 50

InputComand *NewCmd();
void throwCmd(InputComand *CMD);
row* newRow(listCols);
void destroy_row(row *);
void *table_to_memory();
void destroy_column(column *c);
void destroy_list_ROWS(list_rows L);
void destroy_list_COLS(listCols c);
void destroy_Table(table *);
void fKey();

#endif