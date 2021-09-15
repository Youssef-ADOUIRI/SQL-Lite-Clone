#include "tabs.h"
#include "funcs.h"
#include "memory.h"



static u_int tab_count_db = 0;

void addcolumn(listCols *List, char *titre, void *data, DATA_NATURE VarType, tab_header *headerTab)
{
    listCols col = (column *)malloc(sizeof(column));
    col->title = (char *)malloc(sizeof(char) * (strlen(titre) + 1));
    strcpy(col->title, titre);
    col->dataCase = data;
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
    (headerTab->cols_count)++;
    return;
}

void addTableTo(listCols List, char name[], u_int colsCount)
{
    tab_header tab;
    if (List != NULL)
    {   
        tab.column_list_attributes = List;
        strcpy(tab.name, name);
        tab.cols_count = colsCount;
        addHeadersTab(tab);
    }
    else
    {
        SetColorRed(true);
        printf("Error has occurred");
        resetColor();
    }
    //free(name);
}

void addHeadersTab(tab_header TabHeader)
{

    tab_all[tab_count_db].header = TabHeader;
    tab_all[tab_count_db].rows = NULL;
    tab_count_db++;
}

void destroy_all_tabHeaders()
{
    destroyTabHeader(tab_all[0].header);
}

void destroyTabHeader(tab_header TabHeader)
{
    destroy_list_COLS(TabHeader.column_list_attributes);    
}

// Virtual Machine
void *transfertToType(char *string, DATA_NATURE *type)
{

    if (strncmp(string, "varchar", 7) == 0)
    {
        //string type

        *type = TEXT;
        char *copie = (char *)malloc(sizeof(char) * (strlen(string) + 1));
        strcpy(copie, string);
        char *saveptr;
        char *typeEntr = strtok_rh(copie, "[]", &saveptr);
        typeEntr = strtok_rh(NULL, "[]", &saveptr);
        //verification
        size_t sizeSTR = atoi(typeEntr);
        if (sizeSTR == 0 || typeEntr == NULL)
        {
            SetColorRed(true);
            printf("The value 0 cannot be entred as an input in varchar");
            resetColor();
            free(copie);
            copie = NULL;
            return NULL;
        }
        char *charType = NULL;
        charType = (char *)malloc(sizeof(char) * sizeSTR);

        strcpy(charType, "");
        free(copie);
        copie = NULL;
        return charType;
    }
    else if (strncmp(string, "int", 3) == 0)
    {
        *type = INTEGER;

        int *integerType = (int *)malloc(sizeof(int));
        *integerType = 0; // intitialiser
        return integerType;
    }
    else if (strncmp(string, "float", 5) == 0)
    {
        *type = REAL;

        float *reelType = (float *)malloc(sizeof(float));
        *reelType = 0.0f; // intitialiser

        return reelType;
    }
    //add the others later for test
    else if (string == NULL)
    { //Default
        //string type

        *type = TEXT;

        char *charType = (char *)malloc(sizeof(char) * STANDARD_ALLOCATION_SIZE);

        strcpy(charType, "");

        return charType;
    }
    else
    {
        SetColorRed(false);
        printf("Error Format : Data type '%S' not recognized", string);
        resetColor();
        return NULL;
    }
}

void printTable_header(listCols L)
{

    listCols temp = L;
    // tous les types de pointeur
    
    int *inte;
    char *text;
    float *reel;

    
    printf("[");
    if (temp != NULL)
    {

        printf("%s ", temp->title);
        
        switch (temp->type)
        {
        case INTEGER:
            inte = (int *)(temp->dataCase);
            printf("%d ", *inte);
            break;
        case TEXT:
            text = (char *)(temp->dataCase);
            printf("%s ", text);
            break;
        case REAL:
            reel = (float *)(temp->dataCase);
            printf("%f ", *reel);
            break;
        default:
            printf("Corupted Format !\n");
            break;
        }

    }


    while (temp->next != NULL)
    {
        temp = temp->next;
        printf(",%s ", temp->title);
        switch (temp->type)
        {
        case INTEGER:
            inte = (int *)(temp->dataCase);
            printf("%d ", *inte);
            break;
        case TEXT:
            text = (char *)(temp->dataCase);
            printf("%s ", text);
            break;
        case REAL:
            reel = (float *)(temp->dataCase);
            printf("%f ", *reel);
            break;
        default:
            printf("Corupted Format !\n");
            break;
        }
    }

    printf("]\n");
}

void printTable(table * t)
{
    //showTable();
}

void showALLTabs()
{
    if (tab_count_db <= 0)
    {
        printf("none");
    }
    else
    {
        for (int i = 0; i < tab_count_db; i++)
        {
            printf("%s ",tab_all[i].header.name);
        }
    }
    printf("\n");
}

bool find_table(const char *name, table *ptr_to_found)
{
    for (int i = 0; i < tab_count_db; i++)
    {
        if (strcmp(tab_all[i].header.name, name) == 0)
        {
            ptr_to_found = &tab_all[i];
            return true;
        }
    }
    ptr_to_found = NULL;
    return false;
}