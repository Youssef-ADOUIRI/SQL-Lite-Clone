
#include "tokenizer.h"

size_t create_Tokenizer(InputComand *CMD, listCols *tabCOLs)
{

    //start tokenizing

    char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    strcpy(copie, CMD->cmd);

    char *token = strtok(copie, " ()");

    if (token == NULL || strcmp(token, "create") != 0)
    {
        SetColorRed(false);
        printf("Error : An '(' expected after 'create' ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    token = strtok(NULL, "()"); //ce qui est entre parenthéses

    if (token == NULL)
    {
        SetColorRed(false);
        printf("Error : Empty input between brackets ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    DATA_NATURE type;
    void *data;
    char *subtokens = strtok(token, ", "); //start tokinizing the token

    if (subtokens == NULL)
    {
        SetColorRed(false);
        printf("Error : Input fromat error ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    char *typeData = strtok(NULL, " ");

    if (strncmp(typeData, ",", 1) == 0)
    {
        SetColorRed(false);
        printf("Error : Input fromat error ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    data = transfertToType(typeData, &type);

    addcolumn(tabCOLs, subtokens, data, type);

    size_t nbrCol = 1;
    subtokens = strtok(NULL, ", ");

    while (subtokens != NULL)
    {
        nbrCol += 1;

        typeData = strtok(NULL, ", ");
        if (typeData == NULL)
        {
            SetColorRed(true);
            printf("Error Format : Data_type of '%s' is not entered ", subtokens);
            resetColor();
            free(copie);
            copie = NULL;
            return 0;
        }
        data = transfertToType(typeData, &type);
        addcolumn(tabCOLs, subtokens, data, type);
        subtokens = strtok(NULL, ", ");
    }

    printList(*tabCOLs);
    free(copie);
    copie = NULL;

    return nbrCol;
}

size_t insert_tokenizer(InputComand *CMD)
{
    size_t cmd_count = 0;
    //start tokenizing

    char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    strcpy(copie, CMD->cmd);

    char *token = strtok(copie, " ()");

    if (token == NULL || strcmp(token, "insert") != 0)
    {
        SetColorRed(false);
        printf("Error : An '(' expected after 'create' ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    token = strtok(NULL, "()"); //ce qui est entre parenthéses

    if (token == NULL)
    {
        SetColorRed(false);
        printf("Error : Empty input between brackets ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    char *subtokens = strtok(token, ", "); //start tokinizing the token

    if (subtokens == NULL)
    {
        SetColorRed(false);
        printf("Error : Input fromat error ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }
    printf("subtoken 1 : %s;\n", subtokens);
    cmd_count++;
    subtokens = strtok(NULL, ", ");
    while (subtokens != NULL)
    {
        printf("v :%s\n",subtokens);
        cmd_count++;
        subtokens = strtok(NULL, ", ");
    }

    

    free(copie);
    copie = NULL;
}
