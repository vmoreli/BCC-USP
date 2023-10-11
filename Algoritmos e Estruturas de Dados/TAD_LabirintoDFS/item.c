#include <stdio.h>
#include <stdlib.h>
#include "item.h"

struct item_ {
    int chave1;
    int chave2;
};

ITEM *item_criar(int chave1, int chave2){
    ITEM * item = (ITEM *) malloc(sizeof(ITEM));

    if(item != NULL){
        item -> chave1 = chave1;
        item -> chave2 = chave2;
    }

    return item;
}

bool item_apagar(ITEM **item){
    if(*item != NULL){
        free(*item);
        *item = NULL;
        return true;
    }

    return false;
}

int item_get_chave1(ITEM * item){
    if(item != NULL){
        return item -> chave1;
    }
    exit(1);
}

int item_get_chave2(ITEM * item){
    if(item != NULL){
        return item -> chave2;
    }
    exit(1);
}
