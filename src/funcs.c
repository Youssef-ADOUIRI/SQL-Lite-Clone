
#include "funcs.h"



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