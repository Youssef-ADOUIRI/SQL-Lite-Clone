#include "tabs.h"
#include "funcs.h"

void addHeadersTab(listCols TabHeader){
    tab_Headers[0] = tab_Headers;
}

void destroy_all_tabHeaders(){
    destroyTabHeader(tab_Headers[0]);
}

void destroyTabHeader(listCols TabHeader){
  listCols temp = NULL;
    while (TabHeader != NULL)
    {
        temp = TabHeader;
        TabHeader = TabHeader->next;
        free(temp->dataCase);
        free(temp->title);
        free(temp);
    }
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

void printList(listCols L)
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
