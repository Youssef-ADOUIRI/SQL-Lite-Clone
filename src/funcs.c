
#include "funcs.h"



void *ptrToType(DATA_NATURE type, void *ptr)
{
    int *inte;
    char *text;
    float *real;
    switch (type)
    {
    case INTEGER:
        inte = (int *)ptr;
        return inte;
        break;
    case TEXT:
        text = (char *)ptr;
        return text;
        break;
    case REAL:
        real = (float *)ptr;
        return real;
        break;
    default:
        return NULL;
        break;
    }
}

void* inputData(DATA_NATURE type, size_t SIZE)
{
    int *inte = (int*)malloc(sizeof(int));
    char *text = (char*)malloc(SIZE);
    float *real = (float*)malloc(sizeof(float));
    fflush(stdin);
    switch (type)
    {
    case INTEGER:
        scanf("%d", inte);
        return inte;
        break;
    case TEXT:
        printf("[Max lenght : %d]", SIZE/(sizeof(char)) );
        scanf("%s", text);
        fKey();
        return text;
        break;
    case REAL:
        scanf("%f", real);
        return real;
        break;
    default:
        return NULL;
        break;
    }

}

char *strtok_rh(char *str, const char *delim, char **nextp) // found in https://stackoverflow.com/questions/12975022/strtok-r-for-mingw
{
    char *ret;

    if (str == NULL)
    {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0')
    {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}