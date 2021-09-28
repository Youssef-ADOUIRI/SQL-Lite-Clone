#include <stdio.h>
#include "display.h"
#include "tabs.h"
#include "pager.h"
#include "memory.h"

void printDB()
{
    printf("%s>", "DB_NAME");
}

//works only in linux
void SetColorRed(bool Bold)
{
    if (Bold == true)
        printf("\n\033[1;31m");
    else
        printf("\033[0;31m");
}
void resetColor(void)
{
    printf("\033[0m");
    printf("\n");
}

void showTable(int ID)
{

    tab_header *head = getTablebyID(ID);
    printTable_header(head->column_list_attributes);
    listCols tempCol = head->column_list_attributes;
    printf("\n---------------------------------------------------------------------\n|");
    while (tempCol != NULL)
    {
        printf("\t");
        printf("%s", tempCol->title);
        printf("\t|");
        tempCol = tempCol->next;
    }
    printf("\n----------------------------------------------------------------------\n");
    tempCol = head->column_list_attributes;
    
    list_rows ROWS_LIST = TABLE->rows;
    while (ROWS_LIST != NULL)
    {
        listValues L = ROWS_LIST->valuesList;
        
        while (L != NULL)
        {
            printf("|\t");
            int y = strlen(tempCol->title);
            int x = print_unkown(*L);

            // for (int i = 0; i < y - x + 8; i++)
            //     printf(" ");
            printf("\t");
            L = L->next;
        }  
        ROWS_LIST = ROWS_LIST->next;
        printf("|\n");
    }
}

int print_unkown(caseValue L)
{
    caseValue temp = L;
    // tous les types de pointeur
    int *inte;
    char *text;
    float *reel;
    int s = 0;
    switch (temp.type)
    {
    case INTEGER:
        inte = (int *)(temp.data);
        printf("%d", *inte);
        s = snprintf(NULL, 0, "%d", *inte);
        if (s > 10)
            s = 10;
        return s;
        break;
    case TEXT:
        text = (char *)(temp.data);
        printf("%s", text);
        s = strlen(text);
        return s;
        break;
    case REAL:
        reel = (float *)(temp.data);
        printf("%.2f", *reel);
        s = snprintf(NULL, 0, "%.2f", *reel);
        if (s > 10)
            s = 10;
        return s;
        break;
    default:
        printf("NULL");
        break;
    }
    return s;
}

void print_Row(row *pr)
{

    if (pr == NULL)
    {
        printf("NULL\n");
        return;
    }
    listValues L = pr->valuesList;
    printf("| ");
    while (L != NULL)
    {
        int x = print_unkown(*L);
        printf(" | ");
        L = L->next;
    }
}
