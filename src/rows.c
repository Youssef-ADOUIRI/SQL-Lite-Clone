#include <stdlib.h>
#include "rows.h"
#include "funcs.h"

Insert_result insert_row_into(table *TABLE)
{
    bool found = find_table(TABLE->header.name, NULL);
    if (!found)
    {
        return TABLE_NOT_FOUND;
    }
    else
    {
        tab_header header = TABLE->header;
        listCols columns = header.column_list_attributes;
        row *inputRow = newRow(TABLE->header.column_list_attributes);
        printf("Insert into ' %s ' table :\n", header.name);
        for (int i = 0; i < header.cols_count; i++)
        {
            if (columns != NULL)
            {
                printf("%s : ", columns->title);
                inputData(columns->type, inputRow->head->dataCase);            
                columns = columns->next;
            }
            else
            {
                break;
            }
        }
        add_row_into_list(inputRow, &(TABLE->rows));
        return INSERT_SUCCESS;
    }   
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
