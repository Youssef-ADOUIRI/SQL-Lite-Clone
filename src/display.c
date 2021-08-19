#include <stdio.h>
#include "display.h"

void SetColorRed(bool Bold)
{
    if (Bold == true)
        printf("\n\033[1;31m");
    else
        printf("\033[0;31m");
}
void resetColor()
{
    printf("\033[0m");
    printf("\n");
}


