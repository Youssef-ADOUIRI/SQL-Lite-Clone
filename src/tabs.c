#include "tabs.h"
#include "funcs.h"
#include "memory.h"

static u_int tab_count_db = 0;

void addcolumn(listCols *List, char *titre, size_t memorySize, DATA_NATURE VarType, tab_header *headerTab)
{
    listCols col = (column *)malloc(sizeof(column));
    col->title = (char *)malloc(sizeof(char) * (strlen(titre) + 1));
    strcpy(col->title, titre);
    col->type = VarType;
    col->memorySize = memorySize;
    
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

void addTableTo(table *tab)
{
    if (tab != NULL)
    {
        tab_all[tab_count_db] = tab;
        tab_count_db++;
    }
    else
    {
        SetColorRed(true);
        printf("Error has occurred");
        resetColor();
    }
}

// Virtual Machine
size_t transfertToType(char *string, DATA_NATURE *type)
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
        //printf("int : %d , str : %s\n", sizeSTR , typeEntr);
        if (sizeSTR == 0 || typeEntr == NULL)
        {
            SetColorRed(true);
            printf("The value 0 cannot be entred as an input in varchar");
            resetColor();
            free(copie);
            copie = NULL;
            return 0;
        }

        free(copie);
        copie = NULL;
        return sizeof(char) * sizeSTR;
    }
    else if (strncmp(string, "int", 3) == 0)
    {
        *type = INTEGER;

        return sizeof(int);
    }
    else if (strncmp(string, "float", 5) == 0)
    {
        *type = REAL;

        return sizeof(float);
    }
    //add the others later for test
    else if (string == NULL)
    { //Default
        //string type

        *type = TEXT;

        return 44 * sizeof(char); //don't ask me why
    }
    else
    {
        SetColorRed(false);
        printf("Error Format : Data type '%s' not recognized", string);
        resetColor();
        return 0;
    }
}

void print_Constrains(column c)
{

    if (c.constrains.isPriKey)
    {
        printf("PRIMARY_KEY");
    }
    else if (c.constrains.isForgKey)
    {
        printf("FOREIGN_KEY");
    }
    else
    {
        if (c.constrains.isUnique)
        {
            printf("UNIQUE");
        }
        else if (c.constrains.isNotNull)
        {
            printf("NOT_NULL");
        }
    }
    if (c.constrains.isAutoInc)
    {
        printf("AUTO_INCREMENT");
    }
}

void printTable_header(listCols L)
{
    listCols temp = L;
    printf("[");
    if (temp != NULL)
    {
        printf("%s ", temp->title);

        switch (temp->type)
        {
        case INTEGER:
            //inte = (int *)(temp->dataCase);
            printf("(INTEGER) ");
            print_Constrains(*temp);
            break;
        case TEXT:
            //text = (char *)(temp->dataCase);
            printf("(VARCHAR[%d]) ", temp->memorySize / sizeof(char));
            print_Constrains(*temp);
            break;
        case REAL:
            //reel = (float *)(temp->dataCase);
            printf("(FLOAT) ");
            print_Constrains(*temp);
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
            //inte = (int *)(temp->dataCase);
            printf("(INTEGER) ");
            print_Constrains(*temp);
            break;
        case TEXT:
            //text = (char *)(temp->dataCase);
            printf("(VARCHAR[%d]) ", temp->memorySize / sizeof(char));
            print_Constrains(*temp);
            break;
        case REAL:
            //reel = (float *)(temp->dataCase);
            printf("(FLOAT) ");
            print_Constrains(*temp);
            break;
        default:
            printf("Corupted Format !\n");
            break;
        }
    }

    printf("]\n");
}

void showALLTabs()
{
    if (tab_count_db <= 0)
    {
        printf("NONE");
    }
    else
    {
        for (int i = 0; i < tab_count_db; i++)
        {
            printf("%s ", tab_all[i]->header->name);
        }
    }
    printf("\n");
}

table *find_table(const char *name)
{
    for (int i = 0; i < tab_count_db; i++)
    {
        if (strcmp(tab_all[i]->header->name, name) == 0)
        {
            return tab_all[i];
        }
    }
    return NULL;
}