#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha {
    ITEM * item[TAM_MAX];
    int tamanho;
};

PILHA * pilha_criar(){
    PILHA * pilha = (PILHA *) malloc(sizeof(PILHA));
    if(pilha != NULL){
        pilha->tamanho = 0;
    }

    return pilha;
}

bool pilha_vazia(PILHA * pilha){
    if(pilha != NULL && pilha -> tamanho == 0) return true;
    return false;
}

bool pilha_cheia(PILHA * pilha){
    if(pilha != NULL && pilha -> tamanho == TAM_MAX) return true;
    return false;
}

int pilha_tamanho(PILHA * pilha){
    return(pilha != NULL? pilha -> tamanho : ERRO);
}

bool pilha_empilhar(ITEM * item, PILHA * pilha){
    if(pilha != NULL && !pilha_cheia(pilha)){
        pilha -> item[pilha -> tamanho] = item;
        pilha -> tamanho++;
        return true;
    }

    return false;
}

ITEM * pilha_desempilhar(PILHA * pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        ITEM * item = pilha -> item[pilha -> tamanho - 1];
        pilha -> item[pilha -> tamanho - 1] = NULL;
        pilha -> tamanho--;

        return item;
    }

    return NULL;
}

bool pilha_apagar(PILHA ** pilha){
    if(*pilha != NULL){
        for (int i = 0; i < (*pilha) -> tamanho; i++)
        {
            free((*pilha) -> item[i]);
            (*pilha) -> item[i] = NULL;
        }

        free(*pilha);
        *pilha = NULL;

        return true;
    }

    return false;

}
