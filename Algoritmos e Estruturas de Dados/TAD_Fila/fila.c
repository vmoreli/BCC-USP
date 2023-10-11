/* Fila: Implementação sequencial com vetor circular */

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_ {
    ITEM * fila[N_MAX];
    int inicio;
    int fim;
    int tamanho;
};

FILA *fila_criar(void){
    FILA * fila = (FILA *) malloc(sizeof(FILA));

    if(fila != NULL){
        fila -> inicio = 0;
        fila -> fim = 0;
        fila -> tamanho = 0;
    }

    return fila;
}

bool fila_inserir(FILA *fila, ITEM *item){
    if(fila != NULL && !fila_cheia(fila)){
        fila -> fila[fila -> fim] = item;
        fila -> fim = (fila -> fim + 1) % N_MAX;
        fila -> tamanho++;

        return true;
    }

    return false;
}

ITEM *fila_remover(FILA * fila){
    if(fila != NULL && !fila_vazia(fila)){
        ITEM * item = fila -> fila[fila -> inicio];
        fila -> fila[fila -> inicio] = NULL;
        fila -> inicio = (fila -> inicio + 1) % N_MAX;
        fila -> tamanho--;

        return item;
    }

    return NULL;
}

void fila_apagar(FILA **fila){
    for (int i = 0; i < ((*fila) -> tamanho); i++)
    {
        item_apagar(&((*fila) -> fila[i]));
    }

    free(*fila);
    *fila = NULL;
}

int fila_tamanho(FILA * fila){
    return fila -> tamanho;
}

bool fila_vazia(FILA * fila){
    if(fila -> tamanho == 0) return true;
    return false;
}

bool fila_cheia(FILA * fila){
    if(fila -> tamanho == N_MAX) return true;
    return false;
}

void fila_imprimir(FILA * fila){
    for (int i = 0; i < (fila -> tamanho); i++)
    {
        printf("%d\n", item_get_chave(fila -> fila[fila -> inicio + i]));
    }
}

void cartas(int n){
    FILA * fila = fila_criar();

    //Inserindo as cartas na fila
    for (int i = 1; i <= n; i++)
    {
        fila_inserir(fila, item_criar(i));
    }

    printf("Discarded cards:");

    //Faz as operações de remoção e inserção na fila, printando as cartas removidas, até sobrar uma carta
    while(fila_tamanho(fila) != 1){
        printf(" %d", item_get_chave(fila_remover(fila)));
        if(fila_tamanho(fila) != 1) printf(",");
        fila_inserir(fila, fila_remover(fila));
    }
        
    //Printa a carta remanescente
    printf("\nRemaining card: %d\n", item_get_chave(fila_remover(fila)));

    fila_apagar(&fila);
    
}