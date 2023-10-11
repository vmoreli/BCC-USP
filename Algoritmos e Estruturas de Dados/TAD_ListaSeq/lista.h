#ifndef LISTA_H

    #define LISTA_H
    #define TAM_MAX 100
    #define ORDENADA 1
    #define ERRO -2000
    #include "item.h"
    #include <stdbool.h>


    typedef struct lista_ LISTA;

    LISTA * lista_criar();
    void lista_apagar(LISTA ** lista);
    bool lista_inserir(LISTA * lista, int chave);
    ITEM * lista_remover(LISTA * lista, int chave);
    int lista_tamanho(LISTA * lista);
    bool lista_vazia(LISTA * lista);
    bool lista_cheia(LISTA * lista);
    void lista_imprimir(LISTA * lista);


#endif