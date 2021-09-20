#ifndef DEF_structures
#define DEF_structures

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>



#define MAX_HEADER_NAME 44
//char DB_NAME[45] = "db";

//if using wingw32
typedef unsigned int u_int;

enum typeCmd
{
    insertCmd,
    selectCmd,
    createCmd,
    useCmd,
    metaCmd,
    exitCmd,
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
    size_t memorySize; 
    DATA_NATURE type;
    struct Coloms *next;
};
typedef struct column column;
typedef column *listCols;

struct row
{
    listCols head;
    u_int cols_count;
    size_t memorySize;
    struct row* next;
};
typedef struct row row;
typedef row * list_rows;



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


typedef struct {
    tab_header header;
    size_t row_count;
    list_rows rows;
}table;


//les prototypes
typeCmd CommandProcessor(InputComand *);



#endif
