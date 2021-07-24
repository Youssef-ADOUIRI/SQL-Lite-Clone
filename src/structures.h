#ifndef DEF_structures
#define DEF_structures

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>


enum typeCmd
{
    insertCmd,
    selectCmd,
    createCmd,
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

struct column
{
    char* title;
    void* dataCase;
    DATA_NATURE type;
    struct Coloms * next;
};
typedef struct column  column ;
typedef column  * listCols;


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

struct tab
{
    size_t ColNumber;
    size_t RowNumber;
};


//les prototypes
void SetColorRed(bool);
void resetColor();
void printDB();
InputComand * NewCmd();
void throwCmd(InputComand*);
typeCmd CommandProcessor(InputComand*);
size_t create_Function(InputComand*,listCols*);
void addcolumn(listCols *, char *, void *, DATA_NATURE);
void *transfertToType(char *,DATA_NATURE*);
void freeCOLS (listCols);

#endif
