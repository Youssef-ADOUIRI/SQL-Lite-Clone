#ifndef DEF_structures
#define DEF_structures

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#define MAX_HEADER_NAME 60
#define MAX_PAGES_TABLE 45
#define MAX_TABLES 50
#define fileNAME "data.bin"
#define META_DATA_OFFSET 0 // currently 0
//if using wingw32
typedef unsigned int u_int;


typedef enum
{
    NOT_NULL,
    UNIQUE,
    PRIMARY_KEY,
    FOREIGN_KEY,
    AUTO_INCREMENT
} Constrains;

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

/* TABLES STRUCTURE */

typedef struct
{
    /*constrains*/
    bool isUnique;
    bool isNotNull;
    bool isPriKey; // unique ans notNull
    bool isForgKey;
    bool isAutoInc;
} CONSTRAINS_DEF;

struct column
{
    char *title;

    size_t memorySize;
    DATA_NATURE type;

    CONSTRAINS_DEF constrains;

    struct Coloms *next;
};
typedef struct column column;
typedef column *listCols;

struct caseValue
{
    void *data;
    DATA_NATURE type;
    size_t memorySize;
    struct caseValue *next;
    //DATA_NATURE type;
};
typedef struct caseValue caseValue;
typedef caseValue *listValues;

struct row
{
    //listCols head;
    listValues valuesList;
    size_t TotalSize;
    struct row *next;
};
typedef struct row row;
typedef row *list_rows;

typedef struct
{
    int index;
    char name[MAX_HEADER_NAME];
    listCols column_list_attributes;
    size_t cols_count;
} tab_header;

typedef struct
{
    tab_header *header;
    size_t row_count;
    list_rows rows;
} table;

#define MAX_ROW_PER_PAGE 12

typedef struct
{
    void *Values; // compact format
} pRow;

typedef struct
{
    int index;
    size_t Rows_Count;
    void *ptr_Rows;
} Page;

typedef struct
{
    tab_header *header;
    size_t row_count;
} pTable;

struct t_Cursor
{
    int index;
    pTable t;
    Page page;
    // P_Cursor;
    // R_Cursor;
};
typedef struct t_Cursor * T_Cursor;


tab_header *preTabs[MAX_TABLES];

// typedef struct
// {
//     int index;
// } P_Cursor;

// typedef struct
// {
//     int index;
// } R_Cursor;

#endif
