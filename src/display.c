#include <stdio.h>
#include "display.h"
#include "tabs.h"

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
void resetColor()
{
    printf("\033[0m");
    printf("\n");
}

void showTable(table TABLE)
{
    tab_header head = TABLE.header;
    listCols tempCol = head.column_list_attributes;
    printf("\n-----------------------------------------------------------------------\n|");
    while (tempCol != NULL)
    {
        printf("    ");
        printf("%s", tempCol->title);
        printf("    |");
        tempCol = tempCol->next;
    }
    printf("\n------------------------------------------------------------------------\n", TABLE.row_count);

    list_rows ROWS_LIST = TABLE.rows;
    while (ROWS_LIST != NULL)
    {
        listCols L = ROWS_LIST->head;

        while (L != NULL)
        {
            print_unkown(*L);
            L = L->next;
        }
        ROWS_LIST = ROWS_LIST->next;
        printf("\n");
    }
}

void print_unkown(column L)
{
    column temp = L;
    // tous les types de pointeur
    int *inte;
    char *text;
    float *reel;
    switch (temp.type)
    {
    case INTEGER:
        inte = (int *)(temp.dataCase);
        printf("%d ", *inte);
        break;
    case TEXT:
        text = (char *)(temp.dataCase);
        printf("%s ", text);
        break;
    case REAL:
        reel = (float *)(temp.dataCase);
        printf("%f ", *reel);
        break;
    }
}
