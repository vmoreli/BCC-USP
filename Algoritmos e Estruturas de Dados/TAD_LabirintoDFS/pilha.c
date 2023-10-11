#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct no_ {
    ITEM * item;
    NO * anterior;
};

struct pilha_ {
    NO * topo;
    int tamanho;
};

PILHA * pilha_criar(void){
    PILHA * pilha = (PILHA *) malloc(sizeof(PILHA));

    if(pilha != NULL){
        pilha -> topo = NULL;
        pilha -> tamanho = 0;
    }

    return pilha;
}


void pilha_apagar(PILHA **pilha){
    NO * paux;
    while((*pilha)->topo != NULL){
        paux = (*pilha) -> topo;
        (*pilha) -> topo = (*pilha) -> topo -> anterior;

        item_apagar(&(paux -> item));
        paux -> anterior = NULL;
        free(paux);
        paux = NULL;
    }

    free(*pilha);
    *pilha = NULL;
}


bool pilha_vazia(PILHA *pilha){
    if(pilha != NULL) return (pilha -> tamanho == 0? true: false);
    return false;
}

bool pilha_cheia(PILHA *pilha){
    NO * novo = (NO *) malloc(sizeof(NO));

    if(novo != NULL){
        free(novo);
        novo = NULL;
        return false;
    }

    return true;
}

int pilha_tamanho(PILHA * pilha){
    return pilha -> tamanho;
}

ITEM *pilha_topo(PILHA *pilha){
    return pilha -> topo -> item;
}

bool pilha_empilhar(PILHA * pilha, ITEM * item){
    NO * novo = (NO *) malloc(sizeof(NO));
    if(novo != NULL){
        novo -> item = item;
        novo -> anterior = pilha -> topo;
        pilha -> topo = novo;
        pilha -> tamanho++;
        return true;
    } 
    return false;
}

ITEM * pilha_desempilhar(PILHA * pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        NO * novo = pilha -> topo;
        ITEM * item = pilha -> topo -> item;
        pilha -> topo = pilha -> topo -> anterior;
        novo -> anterior = NULL;
        free(novo);
        novo = NULL;
        pilha -> tamanho--;
        return item;
    }
    return NULL;
}