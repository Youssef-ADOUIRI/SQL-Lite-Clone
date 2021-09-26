#include <stdint.h>
#include "pager.h"
#include "memory.h"
#include "display.h"

pRow makeCompactRow(row *r)
{
    pRow p;
    uint32_t size = r->TotalSize;
    void *place = malloc(size);
    listValues L = r->valuesList;
    if (size == 0 || place == NULL || r == NULL || L == NULL)
    {
        free(place);
        p.Values = NULL;
    }
    else
    {
        uint32_t tempOffset = 0;
        while (L != NULL)
        {
            memcpy(((uint32_t)place + tempOffset), L->data, L->memorySize);
            tempOffset += L->memorySize;
            L = L->next;
        }

        p.Values = place;
    }
    return p;
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
