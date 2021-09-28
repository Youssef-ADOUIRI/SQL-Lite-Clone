#define InitStrSize 10
#include "memory.h"

InputComand *NewCmd()
{
    InputComand *CMD = NULL;
    CMD = (InputComand *)malloc(sizeof(InputComand));
    CMD->cmd = (char *)malloc(InitStrSize * sizeof(char));
    CMD->isMetaCmd = true;
    CMD->SizeOfCmd = 0;
    CMD->type = unknown;
    return CMD;
}

caseValue *newCaseVal(column col)
{
    caseValue *val = NULL;
    val = (caseValue *)malloc(sizeof(caseValue));
    val->memorySize = col.memorySize;
    val->type = col.type;
    switch (col.type)
    {
    case INTEGER:
        val->data = (int *)malloc(sizeof(int));
        break;
    case REAL:
        val->data = (float *)malloc(sizeof(float));
        break;
    case TEXT:
        val->data = (char *)malloc(sizeof(char) * (val->memorySize));
        break;
    case NONE:
        val->data = NULL;
        break;
    default:
        val->data = NULL;
        break;
    }
    val->next = NULL;
    return val;
}

row *newRow(listValues listVal)
{
    row *ROW = NULL;
    if (listVal != NULL)
    {
        ROW = (row *)malloc(sizeof(row));
        ROW->valuesList = listVal;
        listValues temp = listVal;

        while (temp != NULL)
        {
            ROW->TotalSize += temp->memorySize;
            temp = temp->next;
        }

        ROW->next = NULL;
    }

    return ROW;
}

table *newTable(tab_header *head)
{
    table *tab = NULL;
    tab = (table *)malloc(sizeof(table));
    tab->header = head;
    tab->row_count = 0;
    tab->rows = NULL;
    
    return tab;
}


void serilizehead(void*place , char* str){
    memcpy(place , str , strlen(str) * sizeof(char));
}

void throwCmd(InputComand *CMD)
{
    free(CMD->cmd);
    free(CMD);
    CMD = NULL;
}

void destroy_Case_Value(caseValue *C)
{
    free(C->data);
    free(C);
    C = NULL;
}

void destroy_List_Cases(listValues L)
{
    while (L != NULL)
    {
        list_rows temp = L;
        L = L->next;
        destroy_Case_Value(temp);
    }
    L = NULL;
}

void destroy_list_ROWS(list_rows L)
{

    while (L != NULL)
    {
        list_rows temp = L;
        L = L->next;
        destroy_row(temp);
    }
    L = NULL;
}

void destroy_row(row *r)
{
    destroy_List_Cases(r->valuesList);
    free(r);
    r = NULL;
}

void destroy_list_COLS(listCols L)
{
    while (L != NULL)
    {
        list_rows temp = L;
        L = L->next;
        destroy_column(temp);
    }
    L = NULL;
}
void destroy_column(column *c)
{
    free(c->title);
    free (c);
    c = NULL;
}



void destroy_Table(table *t)
{
    destroyTabHeader(t->header);
    destroy_list_ROWS(t->rows);
    free(t);
    t = NULL;
}


void destroyTabHeader(tab_header *TabHeader)
{
    destroy_list_COLS(TabHeader->column_list_attributes);
    free(TabHeader);
    TabHeader = NULL;  
}

void fKey()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}