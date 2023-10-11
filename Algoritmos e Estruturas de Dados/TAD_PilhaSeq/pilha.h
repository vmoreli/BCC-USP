

#ifndef PILHA_H

    #define PILHA_H

    #include "item.h"
    #include <stdbool.h>

    #define TAM_MAX 50
    #define ERRO -1

    typedef struct pilha PILHA;

    PILHA * pilha_criar();
    bool pilha_vazia(PILHA * pilha);
    bool pilha_cheia(PILHA * pilha);
    bool pilha_empilhar(ITEM *  item, PILHA * pilha);
    ITEM * pilha_desempilhar(PILHA * pilha);
    int pilha_tamanho(PILHA * pilha);
    bool pilha_apagar(PILHA ** pilha);


#endif