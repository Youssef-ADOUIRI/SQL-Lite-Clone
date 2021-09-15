
#include "funcs.h"

void inputData(DATA_NATURE type, void *ptr)
{
    int *inte;
    char *text;
    float *real;
    switch (type)
    {
    case INTEGER:
        inte = (int *)ptr;
        scanf("%d", inte);
        break;
    case TEXT:
        text = (char *)ptr;
        printf("(lenght : %d", strlen(text));
        scanf("%s", ptr);
        break;
    case REAL:
        real = (float *)ptr;
        scanf("%f", real);
        break;
    default:
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