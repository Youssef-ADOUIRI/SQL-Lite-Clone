#ifndef DEF_tabs
#define DEF_tabs

#include "structures.h"

#define STANDARD_ALLOCATION_SIZE 45

listCols tab_Headers[4]; // just for now


void addHeadersTab(listCols);
void destroy_all_tabHeaders(void);
void destroyTabHeader(listCols);
void *transfertToType(char *string, DATA_NATURE *type);
void printList(listCols L);


#endif
