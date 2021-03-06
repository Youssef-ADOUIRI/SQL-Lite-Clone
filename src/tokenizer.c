
#include "tokenizer.h"
#include <string.h>
#include "tabs.h"

#define dilim1 " ()"

create_result create_Tokenizer(InputComand *CMD,
                               listCols *tabCOLs,
                               size_t *nbrCOlsResult,
                               char nameResult[],
                               tab_header *headerOfTable)
{

    //start tokenizing
    *nbrCOlsResult = 0;

    char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    strcpy(copie, CMD->cmd);

    char *token = strtok(copie, " ");
    if (token == NULL || strcmp(token, "create") != 0)
    {
        free(copie);
        copie = NULL;
        return ERROR_AT_CREATION;
    }

    token = strtok(NULL, " ");
    if (token == NULL)
    {
        free(copie);
        copie = NULL;
        return ERROR_AT_CREATION;
    }
    else
    {
        if (strchr(token, '(') != NULL)
        {
            free(copie);
            copie = NULL;
            return ERROR_AT_CREATION;
        }
        if (strcmp(token, "table") == 0)
        {

            token = strtok(NULL, " ()");

            if (token == NULL)
            {
                SetColorRed(false);
                printf("Error : enter a name before '(' ");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CREATION;
            }
            //nameResult = (char *)malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(nameResult, token);
            printf("Name of table : %s\n", nameResult);

            /*   data tokenizing    */

            token = strtok(NULL, "()"); //ce qui est entre parenthéses

            if (token == NULL)
            {
                SetColorRed(false);
                printf("Error : Empty input between brackets ");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CREATION;
            }

            DATA_NATURE type;
            size_t SIZE = 0;
            char *subtokens = strtok(token, ", "); //start tokinizing the token

            if (subtokens == NULL)
            {
                SetColorRed(false);
                printf("Error : Input fromat error ");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CREATION;
            }

            char *typeData = strtok(NULL, " ");
            if (typeData == NULL)
            {
                SetColorRed(false);
                printf("Error : Input fromat error ");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CREATION;
            }

            if (strncmp(typeData, ",", 1) == 0)
            {
                SetColorRed(false);
                printf("Error : Input fromat error ");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CREATION;
            }

            SIZE = transfertToType(typeData, &type);
            addcolumn(tabCOLs, subtokens, SIZE, type, headerOfTable);

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
                    return ERROR_AT_CREATION;
                }

                SIZE = transfertToType(typeData, &type);
                //printf("SIZE   : %d\n" , SIZE);
                addcolumn(tabCOLs, subtokens, SIZE, type, headerOfTable);
                subtokens = strtok(NULL, ", ");
            }
            free(copie);
            copie = NULL;
            headerOfTable->column_list_attributes = *tabCOLs;
            strcpy(headerOfTable->name, nameResult);
            *nbrCOlsResult = nbrCol;
            //printTable_header(headerOfTable->column_list_attributes);
            return TABLE_CREATION;
        }
        else if (strcmp(token, "database") == 0)
        {
            //create database
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                SetColorRed(false);
                printf("Error : enter a name before '(' ");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CREATION;
            }

            //name
            //nameResult = (char *)malloc(sizeof(char) * (strlen(token) + 1));

            strcpy(nameResult, token);
            printf("name : %s\n", nameResult);
            free(copie);
            copie = NULL;

            return DATABASE_CREATION;
        }
        else
        {
            free(copie);
            copie = NULL;
            return NON_SPECIFIED;
        }
    }
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
        printf("Error : An '(' expected after 'insert' ");
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
        printf("v :%s\n", subtokens);
        cmd_count++;
        subtokens = strtok(NULL, ", ");
    }

    free(copie);
    copie = NULL;
}

table *use_tok_function(InputComand *CMD, use_result *rUse)
{
    table *returned_tab = NULL;
    if (CMD->cmd == NULL || strlen(CMD->cmd) < 1)
    {
        SetColorRed(true);
        printf("Error : NO INPUT ");
        resetColor();
        *rUse = ERROR_AT_CMD;
        return NULL;
    }

    char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    strcpy(copie, CMD->cmd);

    char *token = strtok(copie, " ");
    if (strcmp(token, "use") != 0 || token == NULL)
    {
        SetColorRed(false);
        printf("Error : Input fromat error ");
        resetColor();
        free(copie);
        copie = NULL;
        *rUse = ERROR_AT_CMD;
        return NULL;
    }

    token = strtok(NULL, " "); // gives : table or database

    if (token == NULL)
    {

        SetColorRed(false);
        printf("Error : no enough inputs in the query");
        resetColor();

        free(copie);
        copie = NULL;

        *rUse = NON_SPECIFIED_use;
        return NULL;
    }
    else
    {

        if (strcmp(token, "table") == 0)
        {
            token = strtok(NULL, " "); //table name

            if (token != NULL)
            {
                //return a pointer to the right db :
                table *ptr = find_table(token); // search by name
                //printTable_header(ptr->header->column_list_attributes);
                //printf("You are now using hh '%s' table\n", ptr->header->name);
                if (ptr == NULL)
                {
                    free(copie);
                    copie = NULL;
                    *rUse = NON_FOUND;
                    return NULL;
                }
                else
                {
                    returned_tab = ptr;
                    printf("You are now using '%s' table\n", returned_tab->header->name);
                }
            }
            else
            {
                free(copie);
                copie = NULL;
                SetColorRed(false);
                printf("Error : insufficient arguments : add a name");
                resetColor();
                *rUse = ERROR_AT_CMD;
                return NULL;
            }
        }
        else if (strcmp(token, "database") == 0)
        {
            token = strtok(NULL, " "); //db name

            if (token != NULL)
            {
                // point to the table
            }
            else
            {
                SetColorRed(false);
                printf("Error : insufficient arguments : add a name");
                resetColor();
                free(copie);
                *rUse = ERROR_AT_CMD;
                return NULL;
            }
        }
        else
        {

            SetColorRed(false);
            printf("Error : arguments:  %s  is unkown", token);
            resetColor();
            free(copie);
            copie = NULL;
            *rUse = NON_SPECIFIED_use;
            return NULL;
        }
    }

    free(copie);
    copie = NULL;
    *rUse = FOUND;
    return returned_tab;
}