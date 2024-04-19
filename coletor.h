#ifndef _COLETOR_H_
#define _COLETOR_H_

typedef struct heap             // Lista encadeada
{
    int contador;                   // Conta as referências ao endereço de memória
    void *endereco;                 // Endereço referido
    struct heap *prox;              // Ponteiro para o próximo nó da lista
} Heap;

void *malloc2(int tam);
void coletor();
void atrib2(void **endereco1, void *endereco2);
void dump();

#endif
