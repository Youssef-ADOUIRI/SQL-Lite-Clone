#ifndef DEF_tok
#define DEF_tok

#include "structures.h"
typedef enum {
    ERROR_AT_CREATION, NON_SPECIFIED ,TABLE_CREATION , DATABASE_CREATION 
}create_result;

typedef enum {
    ERROR_AT_CMD, NON_SPECIFIED_use , NON_FOUND , FOUND
}use_result;

// typedef enum {
//     ERROR_AT_CREATION ,TABLE_CREATION , DATABASE_CREATION 
// }insert_result;

create_result create_Tokenizer(InputComand *CMD, listCols *tabCOLs , size_t*, char * ,  tab_header *);
size_t insert_tokenizer(InputComand*);

table*  use_tok_function(InputComand * , use_result*);



#endif
