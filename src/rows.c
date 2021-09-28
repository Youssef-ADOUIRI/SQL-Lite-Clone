#include <stdlib.h>
#include "rows.h"
#include "funcs.h"
#include "memory.h"
#include "tabs.h"
#include "display.h"

extern u_int tab_count_db;

Insert_result insert_row_into(table *TABLE)
{
    table* found =NULL;
    // find_table(TABLE->header->name);
    if (!found)
    {
        return TABLE_NOT_FOUND;
    }
    else
    {
        row *inputRow = newRow(get_Values(*TABLE));
        add_row_into_list(inputRow, &(TABLE->rows));
        return INSERT_SUCCESS;
    }
}

listValues get_Values(table tab)
{
    listValues output = NULL;
    
    tab_header *head = tab.header;
    printf("Inserting into '%s' table : \n", head->name);
    listCols temp = head->column_list_attributes;
    printTable_header(temp);
    for (int i = 0; i < head->cols_count; i++)
    {
        if (temp != NULL)
        {
            printf("%s : ", temp->title);
            // printf("size :%d\n" , temp->memorySize);

            caseValue* tempOut = newCaseVal(*temp);
            
            tempOut->data =  inputData(temp->type, temp->memorySize);
            add_Value_ToList(tempOut, &output);

            temp = temp->next;
        }
        else
        {
            break;
        }
    }
    return output;
}

size_t add_Value_ToList(caseValue *val, listValues *List)
{
    size_t count = 0;
    val->next = NULL;
    if (*List == NULL)
    {
        *List = val;
        count++;
    }
    else
    {
        listValues temp = *List;
        while (temp->next != NULL)
        {
            count++;
            temp = temp->next;
        }
        temp->next = val;
    }
    return count;
}

void add_row_into_list(row *r, list_rows *List)
{
    r->next = NULL;
    if (*List == NULL)
    {
        *List = r;
    }
    else
    {
        list_rows temp = *List;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = r;
    }

    return;
} // create table io ( id int , sal float)
