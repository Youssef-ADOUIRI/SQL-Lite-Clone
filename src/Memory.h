#ifndef DEF_Memory
#define DEF_Memory

#include "structures.h"


#define PAGE_SIZE 8162 // 8 kB

InputComand *NewCmd();
void throwCmd(InputComand *);
Page *newPage();
row *newRow(listValues);
caseValue *newCaseVal(column);
table *newTable(tab_header*);
void serilizehead(void*place , char*);
void destroy_row(row *);
void destroy_column(column *);
void destroy_List_Cases(listValues);
void destroy_Case_Value(caseValue *);
void destroy_list_ROWS(list_rows);
void destroy_list_COLS(listCols);
void destroy_Table(table *);
void destroyTabHeader(tab_header *);
void fKey();

#endif