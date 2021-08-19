
#include "funcs.h"

void addcolumn(listCols *List, char *titre, void *dataType, DATA_NATURE VarType)
{
    listCols col = (column *)malloc(sizeof(column));
    col->title = (char *)malloc(sizeof(char) * (strlen(titre) + 1));
    strcpy(col->title, titre);
    col->dataCase = dataType;
    col->type = VarType;
    col->next = NULL;

    if (*List == NULL)
    {
        *List = col;
    }
    else
    {
        listCols temp = *List;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = col;
    }

    return;
}

void addTableTo(TABLES_LIST *List, tab_row tab)
{
    TABLES_LIST col = (tab_row *)malloc(sizeof(tab_row));
    col->Total_memory_Size = tab.Total_memory_Size;

    col->AllColumns = tab.AllColumns;

    col->next = NULL;

    if (*List == NULL)
    {
        *List = col;
    }
    else
    {
        listCols temp = *List;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = col;
    }

    return;
}

void print_ALL_Tables(TABLES_LIST L)
{
    TABLES_LIST temp = L;

    if (temp != NULL){
        printf("SIZZE : %d\n", temp->Total_memory_Size);
    }
}

char *strtok_rh(char *str, const char *delim, char **nextp) // found in https://stackoverflow.com/questions/12975022/strtok-r-for-mingw
{
    char *ret;

    if (str == NULL)
    {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0')
    {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}