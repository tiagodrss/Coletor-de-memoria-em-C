#include <stdio.h>
#include <stdlib.h>
#include "coletor.h"

Heap *hp = NULL;

void *malloc2(int tamanho)
{
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->contador = 1;
    h->endereco = malloc(tamanho);
    h->prox = NULL;

    if (hp)
    {
        h->prox = hp;
    }
    hp = h;
    return hp->endereco;
}

void coletor()
{
    if (!hp)
        return;

    Heap *b, *aux = hp;

    while (aux && aux->contador == 0)
    {
        hp = aux->prox;
        free(aux->endereco);
        free(aux);
        aux = hp;
    }

    while (aux)
    {
        if (aux->contador != 0)
        {
            b = aux;
            aux = aux->prox;
        }
        else
        {
            b->prox = aux->prox;
            free(aux->endereco);
            free(aux);
            aux = b->prox;
        }
    }
}

void atrib2(void **endereco1, void *endereco2)
{
    Heap *aux = hp;
    Heap *prox;

    while (aux)
    {
        prox = aux->prox;

        if (aux->endereco == *endereco1)
        {
            aux->contador -= 1;
            if (aux->contador == 0)
            {
                coletor();
            }
        }
        if (aux->endereco == endereco2)
        {
            aux->contador += 1;
        }
        aux = prox;
    }
    *endereco1 = endereco2;
}

void dump()
{
    Heap *aux = hp;
    while (aux != NULL)
    {
        printf("Endereco: %p\t",aux->endereco);
        printf("Ref:%d\n",aux->contador);
        aux=aux->prox;
    }
    printf("\n-----------------------------\n\n");
}
