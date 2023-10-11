#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

// typedef struct no_ NO;

// struct no_ {
//     ITEM * item;
//     NO * proximo;
// };

// struct lista_ {
//     NO * inicio;
//     NO * final;
//     int tamanho;
// };

struct lista_ {
    ITEM * itens[TAM_MAX];
    int inicio;
    int fim;
};

LISTA * lista_criar(){
    LISTA * lista = (LISTA *) malloc(sizeof(LISTA));

    if(lista != NULL)
    {
        lista -> inicio = 0;
        lista -> fim = 0;
    }

    return lista;
}

void lista_apagar(LISTA ** lista){
    for (int i = 0; i < (*lista) -> fim; i++)
    {
        free((*lista)->itens[i]);
        (*lista)->itens[i] = NULL;
    }

    free(*lista);
    *lista = NULL;
}

int busca_binaria(LISTA * lista, int chave){
    if(lista == NULL) return ERRO;

    if(!lista_vazia(lista)){
        int inf = lista->inicio-1, sup = lista->fim;

        while (inf < sup-1) {  
            int meio = (inf + sup)/2;
            if (item_get_chave(lista->itens[meio]) < chave) inf = meio;
            else sup = meio; 
        }

        return sup;
    }

    return 0; //Lista Vazia
}

bool lista_inserir(LISTA * lista, int chave){
    if(!lista_cheia(lista) && lista != NULL){
        ITEM * item = item_criar(chave);

        int posicao = busca_binaria(lista, chave);

        for (int i = lista->fim; i > posicao; i--)
        {
            lista->itens[i] = lista->itens[i-1]; //Deslocamento dos itens
        }

        lista->itens[posicao] = item;
        lista -> fim++;

        return true;
    }
    
    return false;
}

void lista_imprimir(LISTA * lista){
    for (int i = 0; i < lista->fim; i++)
    {
        printf("[%d]; ", item_get_chave(lista->itens[i]));
    }
    printf("\n\n");
}

bool lista_cheia(LISTA * lista){
    return (lista->fim == TAM_MAX? true : false);
}

bool lista_vazia(LISTA * lista){
    return (lista->inicio == lista->fim? true: false);
}

int lista_tamanho(LISTA * lista){
    return (lista->fim - lista->inicio);
}

ITEM * lista_remover(LISTA * lista, int chave){
    if(lista != NULL){
        int posicao = busca_binaria(lista, chave);
        ITEM * item = lista->itens[posicao];

        lista_imprimir(lista);

        for (int i = posicao+1; i < lista->fim; i++)
        {
            lista->itens[i-1] = lista->itens[i]; //Deslocando elementos da lista
        }
        
        lista->fim--;
        return item;
    }

    return NULL;
}