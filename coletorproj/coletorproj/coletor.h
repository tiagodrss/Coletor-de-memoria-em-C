#ifndef _COLETOR_H_
#define _COLETOR_H_

typedef struct heap
{
    int contador;
    void *endereco;
    struct heap *prox;
} Heap;

void *malloc2(int tam);
void coletor();
void atrib2(void **endereco1, void *endereco2);
void dump();

#endif
