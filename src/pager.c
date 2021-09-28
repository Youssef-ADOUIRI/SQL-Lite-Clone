#include <stdint.h>
#include "pager.h"
#include "memory.h"
#include "display.h"
#include "tabs.h"
#include <stdio.h>


extern u_int tab_count_db;
int getID(char * str){
    for (int i = 0; i < tab_count_db; i++)
    {
        //printTable_header(preTabs[i]->column_list_attributes);
        if (strcmp(preTabs[i]->name, str) == 0)
        {
            return preTabs[i]->index;
        }
    }
    return -1;
}

tab_header* getTablebyID(int id){
    
    printf("tab_count_db : %d\n", tab_count_db);
    for (int i = 0; i < tab_count_db; i++)
    {
        if (preTabs[i]->index == id)
        {
            return preTabs[i];
            //printTable_header(tab->column_list_attributes);

        }
    }
    return NULL;
}

Page* getPage(int pID , int tID){
    //search in file
    Page* page  =  newPage();
    FILE* f_data = fopen(fileNAME , "rb" );
    if(f_data != NULL){
        fseek(f_data , META_DATA_OFFSET , SEEK_SET  );
        size_t tableCount;
        fread(&tableCount , sizeof(size_t) , 1 , f_data);
        if(tableCount == 0 ){
            printf("NO tables in file\n");
            return NULL;
        }
        int IDtable;
        size_t offsetTable = 0;
        for(int i = 0 ; i < tableCount; i++){
            fseek(f_data , offsetTable , SEEK_CUR);
            fread(&IDtable , sizeof(int) , 1 , f_data);
            fread(&offsetTable , sizeof(size_t) , 1 , f_data);
            if(IDtable == tID){
                //function to get header
                //Btree structure
                //pages
                //btree
                //search for page
                void* tempPage = malloc(PAGE_SIZE);
                fread(page , PAGE_SIZE , 1 , f_data);
                
                //return diserable page

                break;
            }
        }
        

    }
    else{
        SetColorRed(false);
        printf("Unable to open the file");
        resetColor();
        return NULL;
    }
}

void addRowToPage(Page *page, row *r)
{

    if (r == NULL || page == NULL)
    {
        SetColorRed(false);
        printf("PAGE or Row is NULL ");
        resetColor();
        return;
    }

    if (page->ptr_Rows == NULL)
    {
        if (page->Rows_Count != 0)
        {
            SetColorRed(true);
            printf("FATAL TECH ERROR ");
            resetColor();
        }
        else
        {
            SetColorRed(false);
            printf("PAGE is not found ");
            resetColor();
        }
        return;
    }

    size_t size = r->TotalSize;
    uint32_t offset = (page->Rows_Count) * (r->TotalSize);
    if (page->Rows_Count <= MAX_ROW_PER_PAGE)
        makeCompactRow((uint32_t)(page->ptr_Rows) + offset, r);
    else
    {
        SetColorRed(false);
        printf("PAGE is Full \n");
        resetColor();
    }
}

void makeCompactRow(void *place, row *r)
{
    //pRow p;
    uint32_t size = r->TotalSize;
    listValues L = r->valuesList;
    if (!(size == 0 || place == NULL || r == NULL || L == NULL))
    {
        uint32_t tempOffset = 0;
        while (L != NULL)
        {
            memcpy(((uint32_t)place + tempOffset), L->data, L->memorySize);
            tempOffset += L->memorySize;
            L = L->next;
        }

        //p.Values = place;
    }
    return;
}

row *makeLsitRow(pRow p, tab_header tab)
{
    size_t count = tab.cols_count;
    listCols Cols = tab.column_list_attributes;
    listValues L = NULL;
    void *place = p.Values;
    uint32_t tempOffset = 0;
    size_t verify = 0;

    for (size_t i = 0; i < count; i++)
    {
        caseValue *Data = newCaseVal(*Cols);

        memcpy(Data->data, ((uint32_t)place + tempOffset), Cols->memorySize);

        tempOffset += Cols->memorySize;

        verify += add_Value_ToList(Data, &L);

        Cols = Cols->next;

        //destroy_Case_Value(Data);
        if (Cols == NULL || verify > count)
            break;
    }
    row *r = newRow(L);
    return r;
}
