#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct no_ NO;

struct no_ {
    ITEM * item;
    NO * proximo;
};

struct lista_ {
    NO * inicio;
    NO * fim;
    int tamanho;
};

LISTA * lista_criar(){
    LISTA * lista = (LISTA *) malloc(sizeof(LISTA));

    if(lista != NULL){
        NO * cabeca = (NO *) malloc(sizeof(NO));
        lista -> inicio = cabeca; //Implementaçao com no cabeça
        lista -> fim = cabeca;
        cabeca -> proximo = NULL;
        lista -> tamanho = 0;
    }

    return lista;
}

ITEM * lista_busca(LISTA * lista, int chave){
    if(lista != NULL){
        NO * pno = lista -> inicio;
        while (pno != NULL && item_get_chave(pno -> item) != chave){
            pno = pno -> proximo;
        }
        return (pno != NULL? pno -> item : NULL);
    }

    return NULL;
}

//Como a lista é não ordenada, a inserção ocorrerá no fim
bool lista_inserir(LISTA * lista, int chave){
    if(lista != NULL && !lista_cheia(lista)){
        ITEM * item = item_criar(chave);
        NO * no = malloc(sizeof(NO));
        no -> item = item;

        lista -> fim -> proximo = no;

        no -> proximo = NULL;
        lista -> fim = no;
        lista -> tamanho++;

        return true;
    }

    return false;
}

ITEM * lista_remover(LISTA * lista, int chave){
    if(lista != NULL && !lista_vazia(lista)){
        NO * pno = lista -> inicio;
        NO * aux;
        ITEM * item_procurado = lista_busca(lista, chave);

        while(pno != NULL && pno -> proximo -> item != item_procurado){
            pno = pno -> proximo;
        }

        if(pno != NULL){
            aux = pno -> proximo;
            pno -> proximo = aux -> proximo;
            free(aux);

            return item_procurado;
        }
        
    }
    return NULL;
}


bool lista_cheia(LISTA * lista){
    if(lista != NULL){
        NO * no = malloc(sizeof(NO));
        bool cheia = (no == NULL? true : false);
        free(no);

        return cheia;
    }
    
    return ERRO;
}

bool lista_vazia(LISTA * lista){
    if(lista != NULL) return (lista -> tamanho == 0? true : false);
    return ERRO;
}

bool lista_apagar(LISTA ** lista){
    NO * aux1 = (*lista) -> inicio;
    NO * aux2;
    while(aux1 != NULL){
        aux2 = aux1 -> proximo;
        free(aux1);
        aux1 = aux2;
    }

    free(*lista);
    *lista = NULL;
}

int lista_tamanho(LISTA * lista){
    return lista->tamanho;
}

bool lista_inverter(LISTA * lista){
    if(lista != NULL){
        NO * anterior = lista -> inicio -> proximo;
        NO * atual = anterior -> proximo;
        NO * proximo = atual -> proximo;
        anterior -> proximo = NULL;
        lista -> fim = atual;

        while(atual != NULL){
            atual -> proximo = anterior;
            anterior = atual;
            atual = proximo;
            if (atual != NULL) proximo = atual -> proximo;
        }

        lista -> inicio -> proximo = anterior; //reposicionando no cabeça
    }
}

void lista_imprimir(LISTA * lista){
    NO * aux = lista -> inicio -> proximo;

    while(aux != NULL){
        printf("[%d]; ", item_get_chave(aux -> item));
        aux = aux -> proximo;
    }

    printf("\n");
}