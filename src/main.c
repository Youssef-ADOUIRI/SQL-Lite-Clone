#include "structures.h"
#include "display.h"
#include "funcs.h"
#include "tabs.h"
#include "display.h"
#include "tokenizer.h"

#define MAX_PAGE_SIZE 50

#define InitStrSize 10
#define printError() printf("\nError Code : %d !!\n", errno)



char *DB_NAME = "db"; //exemple

FILE *dataFile = NULL;



int main(int argc, char *argv[])
{
    //intialzer
    dataFile = fopen("data.bin", "rb");
    if (dataFile == NULL)
    {
        //The data file does not exist
        dataFile = fopen("data.bin", "wb");
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
    destroy_all_tabheaders();
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
        else if (strcmp(CMD->cmd, ".help") == 0)
        {
            printf("HELP\n");
        }
        else
        {
            SetColorRed(false);
            printf("Unknown MetaCommand : '%s'", CMD->cmd);
            resetColor();
            return unknown;
        }
        return metaCmd;
    }
    else
    {
        /*toknizer*/
        CMD->isMetaCmd = false;
        // insert or select
        if (strncmp(CMD->cmd, "insert", 6) == 0)
        {
            //insert cmd tokenizing
            size_t count = insert_tokenizer(CMD);
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
            listCols COLS = NULL;
            
            size_t cols_count = create_Tokenizer(CMD, &COLS);
            

            if (cols_count != 0)
                printf("done processing!\ncolumns count is %d\n", cols_count);
            else
            {
                SetColorRed(true);
                printf("Error during the tokinizing of this command");
                resetColor();
                return createCmd;
            }
            /*
            //Engistrer le tableau dans fichier
            FILE *TAB1 = fopen("tab1.bin", "ab");
            tab_row row0;
            row0.AllColumns = COLS;
            row0.Total_memory_Size = sizeof(*COLS);
            TABLES_LIST exemple = NULL;
            addTableTo(&exemple, row0);
            print_ALL_Tables(exemple);
            //printf("\nSize tab std : %d\nSize list : %d\nSize list basic : %d\n", sizeof(tab_row), sizeof(row0), sizeof(*COLS));
            fwrite(&row0, row0.Total_memory_Size, 1, TAB1);
            tab_row row1;
            rewind(TAB1);
            fread(&row1, row0.Total_memory_Size, 1, TAB1);
            printf("size 2 : %d\n", row1.Total_memory_Size);
            fclose(TAB1);
            */
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