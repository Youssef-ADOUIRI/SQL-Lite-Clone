#ifndef DEF_rows
#define DEF_rows

#include "structures.h"


typedef enum {
    ERROR_AT_INSERT, TABLE_NOT_FOUND , INSERT_SUCCESS
}Insert_result;

Insert_result insert_row_into(table*);

void add_row_into_list(row *, list_rows*);
void destroy_row();








#endif