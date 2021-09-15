#include "structures.h"
#include "display.h"
#include "funcs.h"
#include "tabs.h"
#include "display.h"
#include "tokenizer.h"
#include "rows.h"

#define Help_print() printf("\nEnter .tables to see all tables ( none : there's no table yet )\n\n")


#define printError() printf("\nError Code : %d !!\n", errno)



tab_header *current_table;

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
            //throwCmd(CMD);
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
            Help_print();
        }
        else if (strcmp(CMD->cmd, ".tables") == 0)
        {
            showALLTabs();
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
            size_t count = insert_row_into(tab_all);
            CMD->type = insertCmd;
            return insertCmd;
        }
        else if (strncmp(CMD->cmd, "select", 6) == 0)
        {   
            showTable(tab_all[0]);
            CMD->type = selectCmd;
            return selectCmd;
        }
        else if (strncmp(CMD->cmd, "create", 6) == 0)
        {
            CMD->type = createCmd;
            listCols COLS = NULL;
            char ptr_to_name[44];
            size_t cols_count = 0;
            tab_header headerOfTable;
            create_result result_creation = create_Tokenizer(CMD, &COLS, &cols_count, ptr_to_name , &headerOfTable);
            switch (result_creation)
            {
            case ERROR_AT_CREATION:
                SetColorRed(true);
                printf("Error during the tokinizing of this command");
                resetColor();
                return unknown;
                break;
            case NON_SPECIFIED:
                SetColorRed(true);
                printf("Error : type of creation non_specified");
                resetColor();
                return createCmd;
                break;
            case DATABASE_CREATION:
                // free(ptr_to_name);
                // ptr_to_name = NULL;
                return createCmd;
                break;
            case TABLE_CREATION:
                if (cols_count != 0)
                {
                    printf("Done processing!\nColumns count is %d\n", cols_count);
                    addTableTo(COLS, ptr_to_name, cols_count);
                    printf("out from table adding \n");
                    printTable_header(COLS);
                    return createCmd;
                }
                else
                {
                    SetColorRed(true);
                    printf("Error during the tokinizing of this command");
                    resetColor();
                    // free(ptr_to_name);
                    // ptr_to_name = NULL;
                    return createCmd;
                }
                break;
            default:
                return unknown;
                break;
            }

            // free(ptr_to_name);
            // ptr_to_name = NULL;

            return createCmd;
        }
        else if (strncmp(CMD->cmd, "use", 3) == 0)
        {
            tab_header *ptr = NULL;
            use_result result_use = use_tok_function(CMD, ptr);
            switch (result_use)
            {
            case ERROR_AT_CMD:
                SetColorRed(true);
                printf("Error during the tokinizing of this command");
                resetColor();
                return unknown;
                break;
            case NON_SPECIFIED_use:
                SetColorRed(false);
                printf("Error : NON_SPECIFIED_use");
                resetColor();
                return unknown;
                break;
            case NON_FOUND:
                SetColorRed(false);
                printf("Error : NON_FOUND");
                resetColor();
                return useCmd;
                break;
            case FOUND:
                if(ptr != NULL){
                    current_table = ptr;
                }
                break;
            default:
                return unknown;
                break;
            }

            return useCmd;
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



