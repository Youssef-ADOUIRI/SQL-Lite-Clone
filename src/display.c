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
void resetColor(void)
{
    printf("\033[0m");
    printf("\n");
}

void showTable(table *TABLE)
{
    if (TABLE == NULL)
    {
        printf("NONE\n");
        return;
    }
    tab_header *head = TABLE->header;
    printTable_header(head->column_list_attributes);
    listCols tempCol = head->column_list_attributes;
    printf("\n-----------------------------------------------------------------------\n|");
    while (tempCol != NULL)
    {
        printf("    ");
        printf("%s", tempCol->title);
        printf("    |");
        tempCol = tempCol->next;
    }
    printf("\n------------------------------------------------------------------------\n", TABLE->row_count);
    tempCol = head->column_list_attributes;
    list_rows ROWS_LIST = TABLE->rows;
    while (ROWS_LIST != NULL)
    {
        listValues L = ROWS_LIST->valuesList;
        printf("|");
        while (L != NULL)
        {
            
            int y = strlen(tempCol->title);
            int x = print_unkown(*L);

            for (int i = 0; i < y - x + 8; i++)
                printf(" ");
            printf("|");

            L = L->next;
        }
        ROWS_LIST = ROWS_LIST->next;
        printf("\n");
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
        printf("%.2f     ", *reel);
        s = snprintf(NULL, 0, "%.2f", *reel);
        if (s > 10)
            s = 10;
        return s;
        break;
    }
    return s;
}
