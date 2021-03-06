#include "structures.h"
#include "display.h"
#include "funcs.h"
#include "tabs.h"
#include "display.h"
#include "tokenizer.h"
#include "rows.h"
#include "memory.h"

#define Help_print() printf("\nEnter .tables to see all tables ( none : there's no table yet )\n\n")

#define printError() printf("\nError Code : %d !!\n", errno)

#define tablesCount 2

unsigned int used_table = 0;
unsigned int used_db = 0;

tab_header *current_table;

FILE *dataFile = NULL;

typeCmd CommandProcessor(InputComand *);

int main(int argc, char *argv[])
{
    //intialzer
    // dataFile = fopen("data.bin", "rb");
    // if (dataFile == NULL)
    // {
    //     //The data file does not exist
    //     dataFile = fopen("data.bin", "wb");
    // }
    // //close
    // fclose(dataFile);

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
        fflush(stdin);
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
        typeCmd cmt =  CommandProcessor(CMD) ;
        if ( cmt == unknown)
        {
            printError();
        }
        else if(cmt == exitCmd){
            throwCmd(CMD);
            break;
        }
        throwCmd(CMD);
    }

    for (int i = 0; i < tablesCount; i++)
        destroy_Table(tab_all[i]);
    

    return 0;
}



typeCmd CommandProcessor(InputComand *CMD)
{

    if (CMD->cmd[0] == '.')
    {
        CMD->isMetaCmd = true;
        if (strcmp(CMD->cmd, ".exit") == 0)
        {
            return exitCmd;
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
        if (strncmp(CMD->cmd, "insert into", 11) == 0)
        {
            //insert cmd tokenizing
            Insert_result result_insertion = insert_row_into(tab_all[used_table]);
            CMD->type = insertCmd;
            return insertCmd;
        }
        else if (strncmp(CMD->cmd, "select", 6) == 0)
        {
            showTable(tab_all[used_table]);
            CMD->type = selectCmd;
            return selectCmd;
        }
        else if (strncmp(CMD->cmd, "create", 6) == 0)
        {
            CMD->type = createCmd;
            listCols COLS = NULL;
            char ptr_to_name[440];
            size_t cols_count = 0;
            tab_header* headerOfTable = (tab_header*)malloc(sizeof(tab_header));
            create_result result_creation = create_Tokenizer(CMD, &COLS, &cols_count, ptr_to_name, headerOfTable);

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
                    printf("NAME : %s\n", headerOfTable->name);
                    //printTable_header(COLS);
                    table * t = NULL;
                    t = newTable(headerOfTable);
                    addTableTo(t);
                    printTable_header(t->header->column_list_attributes);
                    return createCmd;
                }
                else
                {
                    SetColorRed(true);
                    printf("Error during the tokinizing of this command");
                    resetColor();
                    return createCmd;
                }
                break;
            default:
                return unknown;
                break;
            }
            return createCmd;
        }
        else if (strncmp(CMD->cmd, "use", 3) == 0)
        {
            table *ptr = NULL;
            use_result result_use= unknown;
            ptr = use_tok_function(CMD, &result_use);
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

                if (ptr != NULL)
                {
                    current_table = ptr->header;

                    for (int i = 0; i < 40; i++)
                    {
                        if (strcmp(current_table->name, tab_all[i]->header->name) == 0)
                        {
                            used_table = i;
                            break;
                        }
                    }
                }
                else
                {
                    printf("out \n");
                    return unknown;
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
