#include "structures.h"
#include "display.h"

#define MAX_PAGE_SIZE 50
#define InitStrSize 10
#define printError() printf("\nError Code : %d !!\n", errno)

char *DB_NAME = "db";

FILE *dataFile = NULL;

int main(int argc, char *argv[])
{
    //intialzer
    dataFile = fopen("data.bin", "rb");
    if (dataFile == NULL)
    {
        //The data file does not exist
        dataFile = fopen("data.bin", "wb");
        //The data file is created
    }
    //close
    fclose(dataFile);

    printf("\n------------Welcome to sqlLite clone------------\nEnter .help to get help page\nEnter .exit to exit\n");

    while (1)
    {
        printDB();
        InputComand *CMD = NULL;
        CMD = NewCmd(); //init
        if (CMD == NULL)
        {
            SetColorRed(true);
            printf("Memory allocation problem");
            resetColor();
            exit(EXIT_FAILURE);
        }
        int len = 0;
        len = getline(&(CMD->cmd), &(CMD->SizeOfCmd), stdin);
        if (len == -1)
        {
            printError();
            throwCmd(CMD);
            exit(EXIT_FAILURE);
        }
        CMD->LenOfCmd = len;

        CMD->cmd[len - 1] = 0; // supprimer la \n

        //Processeur des commandes
        if (CommandProcessor(CMD) == unknown)
        {
            throwCmd(CMD);
            continue;
        }
        throwCmd(CMD);
    }

    return 0;
}

typeCmd CommandProcessor(InputComand *CMD)
{
    if (CMD->cmd[0] == '.')
    {
        CMD->isMetaCmd = true;
        if (strcmp(CMD->cmd, ".exit") == 0)
        {
            //printf("EXIT\n");

            throwCmd(CMD);
            exit(EXIT_SUCCESS);
        }
        return metaCmd;
    }
    else
    {
        //toknizer
        CMD->isMetaCmd = false;
        // insert or select
        if (strncmp(CMD->cmd, "insert", 6) == 0)
        {
            CMD->type = insertCmd;
            return insertCmd;
        }
        else if (strncmp(CMD->cmd, "select", 6) == 0)
        {
            CMD->type = selectCmd;
            return selectCmd;
        }
        else if (strncmp(CMD->cmd, "create", 6) == 0)
        {
            CMD->type = createCmd;
            listCols *COLS;
            size_t COLs_NUMBER = create_Function(CMD, COLS);
            return createCmd;
        }
        else
        {
            SetColorRed(false);
            printf("Unknown Command : '%s'", CMD->cmd);
            resetColor();
            return unknown;
        }
    }
}

size_t create_Function(InputComand *CMD, listCols *tabCOLs)
{
    char *copie = (char *)malloc(sizeof(char) * (strlen(CMD) + 1));
    strcpy(copie, CMD->cmd);
    char *token = strtok(copie, "()");

    if (token == NULL || strcmp(token, "create ") != 0)
    {
        SetColorRed(false);
        printf("Error an '(' expected after 'create'");
        resetColor();
        free(copie);
        return 0;
    }
    token = strtok(NULL, "()"); //entre parenthéses

    //tokenize
    DATA_NATURE type;
    void * data;
    char *subtokens = strtok(token, ", ");
    printf("SubToken 1 : .%s. \n", subtokens);
    char *typeData = strtok(NULL, ", ");
    printf("SubToken 2 : .%s. \n", typeData);
    
    data = transfertToType(typeData, &type);
    addcolumn(tabCOLs, subtokens, data , type);
    printList(tabCOLs);
    free(copie);
    freeCOLS(tabCOLs);
    return true;
}

void addcolumn(listCols *List, char *titre, void *dataType,DATA_NATURE VarType)
{
    listCols col = (column *)malloc(sizeof(column));
    col->title = (char *)malloc(sizeof(char) * (strlen(titre) + 1));
    strcpy(col->title, titre);
    col->dataCase = dataType;
    col->type = VarType;
    col->next = NULL;
    if (*List == NULL)
        *List = col;
    else
    {
        listCols temp = *List;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = col;
    }
    printf("add columns is done : ---------\n");

    return;
}

void *transfertToType(char *string, DATA_NATURE * type)
{

    if (strncmp(string, "varchar", 7) == 0)
    {
        //string type
        printf("data is varcah\n");
        type = TEXT;
        char *copie = (char *)malloc(sizeof(char) * (strlen(string) + 1));
        strcpy(copie, string);
        char *type = strtok(copie, "()");
        printf("");
        type = strtok(NULL, "()");
        size_t sizeSTR = atoi(type);
        if (sizeSTR == 0)
        {
            SetColorRed(true);
            printf("The value 0 is not compatible in varchar type !!");
            resetColor();
            return NULL;
        }
        char *charType = (char *)malloc(sizeof(char) * sizeSTR);
        free(copie);
        printf("data is done\n");
        return charType;
    }
    else if (strncmp(string, "int", 7) == 0)
    {
        type = INTEGER;
        printf("data is int\n");
        int *integerType = (int *)malloc(sizeof(int));
        return integerType;
    }
    //add the others later
}

void freeCOLS(listCols list)
{
    while (list != NULL)
    {
        listCols temp = list;
        list = list->next;
        free(temp->dataCase);
        free(temp->title);
        free(temp);
    }
}

void printList(listCols gg)
{
}

InputComand *NewCmd()
{
    InputComand *CMD = (InputComand *)malloc(sizeof(InputComand));
    CMD->cmd = (char *)malloc(InitStrSize * sizeof(char));
    CMD->isMetaCmd = true;
    CMD->SizeOfCmd = 0;
    CMD->type = unknown;
    return CMD;
}

void throwCmd(InputComand *CMD)
{
    free(CMD->cmd);
    free(CMD);
}

void printDB()
{
    printf("%s>", DB_NAME);
}