
#include "tokenizer.h"
#include <string.h>

#define dilim1 " ()"

create_result create_Tokenizer(InputComand *CMD, listCols *tabCOLs, size_t *nbrCOlsResult, char nameResult[] , tab_header * headerOfTable)
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
            void *data;
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
            if (typeData == NULL){
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


            data = transfertToType(typeData, &type);



            addcolumn(tabCOLs, subtokens, data, type  , headerOfTable);

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

                data = transfertToType(typeData, &type);
                addcolumn(tabCOLs, subtokens, data, type , headerOfTable);
                subtokens = strtok(NULL, ", ");
            }
            
            //printTable_header(*tabCOLs); // debugging
            free(copie);
            copie = NULL;

            *nbrCOlsResult = nbrCol;

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
    // size_t cmd_count = 0;
    // //start tokenizing

    // char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    // strcpy(copie, CMD->cmd);

    // char *token = strtok(copie, " ()");

    // if (token == NULL || strcmp(token, "insert") != 0)
    // {
    //     SetColorRed(false);
    //     printf("Error : An '(' expected after 'insert' ");
    //     resetColor();
    //     free(copie);
    //     copie = NULL;
    //     return 0;
    // }

    // token = strtok(NULL, "()"); //ce qui est entre parenthéses

    // if (token == NULL)
    // {
    //     SetColorRed(false);
    //     printf("Error : Empty input between brackets ");
    //     resetColor();
    //     free(copie);
    //     copie = NULL;
    //     return 0;
    // }

    // char *subtokens = strtok(token, ", "); //start tokinizing the token

    // if (subtokens == NULL)
    // {
    //     SetColorRed(false);
    //     printf("Error : Input fromat error ");
    //     resetColor();
    //     free(copie);
    //     copie = NULL;
    //     return 0;
    // }
    // printf("subtoken 1 : %s;\n", subtokens);
    // cmd_count++;
    // subtokens = strtok(NULL, ", ");
    // while (subtokens != NULL)
    // {
    //     printf("v :%s\n", subtokens);
    //     cmd_count++;
    //     subtokens = strtok(NULL, ", ");
    // }

    // free(copie);
    // copie = NULL;



}

use_result use_tok_function(InputComand *CMD, tab_header *returned_tab)
{

    if (CMD->cmd == NULL || strlen(CMD->cmd) < 1)
    {
        SetColorRed(true);
        printf("Error : NO INPUT ");
        resetColor();
        return ERROR_AT_CMD;
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
        return ERROR_AT_CMD;
    }

    token = strtok(NULL, " "); // gives : table or database

    if (token == NULL)
    {

        SetColorRed(false);
        printf("Error : no enough inputs in the query");
        resetColor();

        free(copie);
        copie = NULL;

        return NON_SPECIFIED_use;
    }
    else
    {

        if (strcmp(token, "table") == 0)
        {
            token = strtok(NULL, " "); //table name

            if (token != NULL)
            {
                //return a pointer to the right db :
                tab_header *ptr;
                bool isfound = find_table(token, ptr);
                if (!isfound || ptr == NULL)
                {
                    free(copie);
                    copie = NULL;
                    return NON_FOUND;
                }
                else
                {
                    returned_tab = ptr;
                    printf("You are now using %s table\n", token);
                }
            }

            else
            {
                free(copie);
                copie = NULL;
                SetColorRed(false);
                printf("Error : insufficient arguments : add a name");
                resetColor();
                return ERROR_AT_CMD;
            }
        }
        else if (strcmp(token, "database") == 0)
        {
            token = strtok(NULL, " "); //table name

            if (token != NULL){
                // point to the table
            }
            else
            {
                SetColorRed(false);
                printf("Error : insufficient arguments : add a name");
                resetColor();
                free(copie);
                copie = NULL;
                return ERROR_AT_CMD;
            }
        }
        else
        {

            SetColorRed(false);
            printf("Error : arguments:  %s  is unkown", token);
            resetColor();
            free(copie);
            copie = NULL;
            return NON_SPECIFIED_use;
        }
    }

    free(copie);
    copie = NULL;
    return FOUND;
}