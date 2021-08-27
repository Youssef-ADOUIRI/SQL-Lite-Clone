#ifndef DEF_structures
#define DEF_structures

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define MAX_HEADER_NAME 44

enum typeCmd
{
    insertCmd,
    selectCmd,
    createCmd,
    useCmd,
    metaCmd,
    unknown
}; //les types de commande d'entré
typedef enum typeCmd typeCmd;

enum DATA_NATURE
{
    NONE,
    TEXT,
    INTEGER,
    REAL
};
typedef enum DATA_NATURE DATA_NATURE;

typedef enum MemoryPrep
{
    successfully_ALLOCATED,
    unsuccessfully_ALLOCATED
};

struct column
{
    char *title;
    void *dataCase;
    DATA_NATURE type;
    struct Coloms *next;
};
typedef struct column column;
typedef column *listCols;

struct InputComand
{
    // la structure qui represente les comandes d'entré :: utilsée dans la machine virtuelle (après)
    char *cmd;
    typeCmd type;
    size_t SizeOfCmd; //
    int LenOfCmd;     //
    bool isMetaCmd;
};
typedef struct InputComand InputComand;

typedef struct
{
    char name[MAX_HEADER_NAME];
    listCols column_list_attributes;
    u_int cols_count;
} tab_header;



//les prototypes
void printDB();
InputComand *NewCmd();
void throwCmd(InputComand *);
typeCmd CommandProcessor(InputComand *);



#endif
