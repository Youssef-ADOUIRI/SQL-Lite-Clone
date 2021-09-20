#define InitStrSize 10
#include "memory.h"

InputComand *NewCmd()
{
    InputComand *CMD = (InputComand *)malloc(sizeof(InputComand));
    CMD->cmd = (char *)malloc(InitStrSize * sizeof(char));
    CMD->isMetaCmd = true;
    CMD->SizeOfCmd = 0;
    CMD->type = unknown;
    return CMD;
}

row *newRow(listCols all_columns)
{

    row *col = (row *)malloc(sizeof(row));
    col->head = all_columns;
    listCols temp = all_columns;
    while (temp != NULL)
    {
        col->memorySize += temp->memorySize;
        col->cols_count += 1;
        temp = temp->next;
    }
    col->next = NULL;

    return col;
}

void throwCmd(InputComand *CMD)
{
    free(CMD->cmd);
    free(CMD);
}

void destroy_list_ROWS(list_rows L)
{
    list_rows temp = L;
    while (temp != NULL)
    {
        destroy_row(temp);
        temp = temp->next;
    }
}

void destroy_row(row *r)
{
    destroy_list_COLS(r->head);
}

void destroy_list_COLS(listCols c)
{
    listCols temp = c;
    while (temp != NULL)
    {
        destroy_column(temp);
        temp = temp->next;
    }
}
void destroy_column(column *c)
{
    free(c->title);
    free(c->dataCase);
}

void fKey(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void destroy_Table(table * t){

    destroy_list_COLS(t->header.column_list_attributes);
    destroy_list_ROWS(t->rows);

}