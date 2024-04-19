#include <stdio.h>
#include <stdlib.h>
#include "coletor.h"

int main()
{
    int *v = (int*)malloc2(sizeof(int));
    *v = 10;
    dump();

    int *w = (int*)malloc2(sizeof(int));
    *w = 20;
    dump();

    atrib2((void**)&v, w);
    dump();

    char *c = (char*)malloc2(sizeof(char));
    *c = 'Z';
    dump();

    atrib2((void**)&w, NULL);
    atrib2((void**)&v, NULL);
    dump();

    return 0;
}
