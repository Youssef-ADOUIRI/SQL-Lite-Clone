
#ifndef DEF_funcs
#define DEF_funcs

#include "structures.h"
void *ptrToType(DATA_NATURE, void *);
void *inputData(DATA_NATURE, size_t);
char *strtok_rh(char *str, const char *delim, char **nextp); // found in https://stackoverflow.com/questions/12975022/strtok-r-for-mingw

#endif
