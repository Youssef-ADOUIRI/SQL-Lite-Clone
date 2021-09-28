#ifndef DEF_Pager
#define DEF_Pager

#include "structures.h"

int getID(char * str);
 tab_header* getTablebyID(int );
void addRowToPage(Page* page , row* r);
Page* getPage(int , int );
void makeCompactRow( void * , row * );
row* makeLsitRow(pRow , tab_header);


// this table structure will store data as a compact format




#endif