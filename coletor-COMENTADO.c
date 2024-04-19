#include <stdio.h>
#include <stdlib.h>
#include "coletor.h"

// Lista global
Heap *hp = NULL;

void *malloc2(int tamanho)
{
    // Criação de um nó 'h'
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->contador = 1;                        // Conta a primeira referência
    h->endereco = malloc(tamanho);          // Efetua a alocação
    h->prox = NULL;                         // Como é a primeira referência, o próximo nó é nulo

    if (hp)                                 // Se a lista global não for vazia (nula)
    {
        h->prox = hp;                       // O novo nó é inserido no início
    }
    hp = h;                                 // Hp passa a apontar para h. Atualizamos o ponteiro para o novo início da lista.
    return hp->endereco;                    // Retornamos o endereço alocado.
}

void coletor()
{
    if (!hp)
        return;

    Heap *b, *aux = hp;

    while (aux && aux->contador == 0)   // Enquanto o primeiro da lista for coletavel    
    {
        hp = aux->prox;                     // Atualiza o ponteiro do inicio da lista para o próximo nó
        free(aux->endereco);                // Libera o ponteiro do endereço
        free(aux);                          // Libera o ponteiro do nó
        aux = hp;                           // Atualiza aux para percorrer a lista
    }

    while (aux)                         // Após coletar os nós do começo, verifica os nós do meio
    {
        if (aux->contador != 0)             // Se o nó atual não for coletável
        {
            b = aux;                        // Armazena o anterior (serve de ponto de conexão para a remoção do próximo nó.)
            aux = aux->prox;                // Atualiza aux para percorrer a lista
        }
        else
        {
            b->prox = aux->prox;        // O próximo do anterior será o próximo do atual (aux)
            free(aux->endereco);        // libera o ponteiro de referencia
            free(aux);                  // libera o ponteiro do nó
            aux = b->prox;              // atualiza aux
        }
    }
}

void atrib2(void **endereco1, void *endereco2)   // Endereço 1: Será atribuido, Endereço 2: Origem do valor a ser atribuido.
{
    Heap *aux = hp;                                    // Auxiliar para percorrer a lista
    Heap *prox;
    
    while (aux)
    {
        prox = aux->prox;                                   // Armazena o ponteiro para o próximo nó. (Importante para não gerar conflito de iteração ao coletar um nó da lista enquanto ela é percorrida dentro da função)

        if (aux->endereco == *endereco1)                    // Se encontrar o endereço 1
        {
            aux->contador -= 1;                                     // A contagem de referencias do primeiro ponteiro passado será decrementada pois passará a apontar para um novo valor.
            if (aux->contador == 0)                                 // Se a referencia removida for a unica
            {
                coletor();                                                      // Chame o coletor
            }
        }                                                           
        if (aux->endereco == endereco2)                     // Se encontrar o endereço 2
        {
            aux->contador += 1;                                     // A contagem de referencias do segundo ponteiro é aumentada pois está sendo referenciado por outro ponteiro
        }
        aux = prox;                                    // Percorre a lista
    }
    *endereco1 = endereco2;                          // Efetua a atribuição
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
    printf("\n\n----------------------\n\n");
}
