#include "tokenizer.h"
#include <string.h>
#include "tabs.h"
#include "funcs.h"
#include "rows.h"
#include "memory.h"
#include "pager.h"

#define dilim1 " ()"
#define initAllocN 5

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

size_t insert_tokenizer(InputComand *CMD,
                        listValues *VALS,
                        T_Cursor cur)
{
    size_t cmd_count = 0;
    //start tokenizing

    char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    strcpy(copie, CMD->cmd);

    char *token = strtok(copie, " ");

    if (token == NULL || strcmp(token, "insert") != 0)
    {
        SetColorRed(false);
        printf("Error : incomplete format after 'insert'");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    token = strtok(NULL, " "); // into

    if (token == NULL || strchr(token, '(') != NULL)
    {
        SetColorRed(false);
        printf("Error : 'into' is expected ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    token = strtok(NULL, " "); //NAME

    if (token == NULL || strchr(token, '(') != NULL)
    {
        SetColorRed(false);
        printf("Error : An '(' isn't expcted here ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }
    char NAME[100];
    strcpy(NAME, token);
    int ID = getID(NAME);
    printf("NAME is : '%s'?%d\n", NAME, ID);
    tab_header *tab = NULL;
    tab = getTablebyID(ID);

    if (ID == -1 || tab == NULL)
    {
        SetColorRed(false);
        printf("Error : Table not found ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }
    cur->index = ID;
    cur->t.header = tab;

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

    // char*ptr_temp = token;
    // char *subtokens; //start tokinizing the token
    // char**allToken = (char**)malloc(sizeof(char*) * initAllocN);
    // while(subtokens = strtok_rh(ptr_temp, "," , &ptr_temp)){
    //     *allToken = (char*)malloc(sizeof(char) * strlen(subtokens));
    //     strcpy(*allToken , subtokens );
    // }

    char *subtokens; //start tokinizing the token
    char *ptr_temp = token;
    subtokens = strtok_rh(ptr_temp, ",", &ptr_temp);
    listCols temp = cur->t.header->column_list_attributes;
    caseValue *tempOut = newCaseVal(*temp);

    if (subtokens == NULL)
    {
        SetColorRed(false);
        printf("Error : Input fromat error ");
        resetColor();
        free(copie);
        copie = NULL;
        return 0;
    }

    //convert to type
    tempOut->data = strToType(subtokens, temp->type);

    if (add_Value_ToList(tempOut, &VALS) != 1)
    {
        printf("Error : List already in use \nContent is ereased\n");
        destroy_List_Cases(VALS);
        add_Value_ToList(tempOut, &VALS);
    }
    temp = temp->next;

    cmd_count++;
    subtokens = strtok_rh(ptr_temp, ",", &ptr_temp);
    while (subtokens != NULL)
    {

        caseValue *tempOut2 = newCaseVal(*temp);

        tempOut2->data = strToType(subtokens, temp->type);
        add_Value_ToList(tempOut2, &VALS);
        printf("v :%s\n", subtokens);
        cmd_count++;
        temp = temp->next;
        subtokens = strtok_rh(ptr_temp, ",", &ptr_temp);
    }

    free(copie);
    copie = NULL;
    return cmd_count;
}

void *strToType(char *str, DATA_NATURE type)
{
    int *inte = (int *)malloc(sizeof(int));
    char *txt = (char *)malloc(sizeof(char) * strlen(str));
    float *real = (float *)malloc(sizeof(float));
    switch (type)
    {
    case INTEGER:
        *inte = atoi(str);
        return inte;
        break;
    case TEXT:
        strcpy(txt, str);
        return txt;
        break;
    case REAL:
        *real = atof(str);
        return real;
        break;
    default:
        return NULL;
        break;
    }
}

table *select_tok(InputComand *CMD)
{

    if (CMD->cmd == NULL || strlen(CMD->cmd) < 1)
    {
        SetColorRed(true);
        printf("Error : NO INPUT ");
        resetColor();
        return NULL;
    }
    char *copie = (char *)malloc(sizeof(char) * (CMD->LenOfCmd + 1));
    strcpy(copie, CMD->cmd);
    char *tempPtr = copie;
    char *token = strtok_rh(tempPtr, " ", &tempPtr);
    if (strcmp(token, "select") != 0 || token == NULL)
    {
        SetColorRed(false);
        printf("Error : Input fromat error ");
        resetColor();
        free(copie);
        copie = NULL;
        return NULL;
    }
    token = strtok_rh(tempPtr, " ", &tempPtr);
    tab_header* usingHead;
    char **colNames;
    if (strcmp(token, "*") == 0)
    {
        //select all columns
        token = strtok_rh(tempPtr, " ", &tempPtr);
        if (strcmp(token, "from") != 0)
        {
            SetColorRed(false);
            printf("Error : Input fromat error ");
            resetColor();
            free(copie);
            copie = NULL;
            return NULL;
        }
        token = strtok_rh(tempPtr, " ", &tempPtr);//Name
        int ID = getID(token);
        if(ID == -1){
            SetColorRed(false);
            printf("Error : TABLE '%s' not found " , token);
            resetColor();
            free(copie);
            copie = NULL;
            return NULL;
        }
        usingHead = getTablebyID(ID);
        if(usingHead == NULL){
            SetColorRed(false);
            printf("Error : TABLE '%s' not found " , token);
            resetColor();
            free(copie);
            copie = NULL;
            return NULL;
        }
    }
    else if ((strcmp("from", token) != 0))
    {

        // colNames = (char **)malloc(sizeof(char *));
        // *colNames = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        // strcpy(*colNames, token);
        // token = strtok_rh(tempPtr, ",", &tempPtr);
        // int i = 1 ;
        // while((strcmp("from", token) != 0)){
        // i++;
        // colNames = (char **)realloc(colNames , sizeof(char *) * i);
        // *colNames = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        // }
        printf("MULTIPLE COLUMNS : SORRY THIS OPTION IS NOT YET IN USE :)\n");
    }
    else
    {
        SetColorRed(false);
        printf("Error : No column specified ");
        resetColor();
        free(copie);
        copie = NULL;
        return NULL;
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
                table *ptr; //= find_table(token); // search by name
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