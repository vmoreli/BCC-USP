#include "ab.h"

typedef struct no_ NO;

struct no_{
    ITEM  *item;
    NO *esq;
    NO *dir;
};

struct ab_{
    NO *raiz;
    int profundidade;
};

#include "maior.c"

void troca_max_esq(NO *troca, NO *raiz, NO *ant){
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }

    if(raiz == ant) ant->esq = troca->esq;
    else ant->dir = troca->esq;

    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

bool ab_remover_aux(NO **raiz, int chave){
    NO *p;

    if(*raiz == NULL) return (false);

    if(chave == item_get_chave((*raiz)->item)){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            p = *raiz;

            if((*raiz)->esq == NULL) *raiz = (*raiz)->dir;
            else *raiz = (*raiz)->esq;

            item_apagar(&p->item);
            p->item = NULL;
            free(p);
            p = NULL;
        }

        else troca_max_esq((*raiz)->esq, (*raiz), (*raiz));

        return (true);
    }
    
    else if(chave < item_get_chave((*raiz)->item)) return ab_remover_aux(&(*raiz)->esq, chave);
    else return ab_remover_aux(&(*raiz)->dir, chave);
}

void apagar_arvore(NO **raiz){
    if(*raiz != NULL){
        apagar_arvore(&(*raiz)->esq);
        apagar_arvore(&(*raiz)->dir);

        item_apagar(&(*raiz)->item);

        free(*raiz);

        *raiz = NULL;
    }
}

NO *ab_criar_no(ITEM *item){
    NO *no = (NO*) malloc(sizeof(NO));

    no->item = item;
    no->esq = NULL;
    no->dir = NULL;

    return (no);
}

NO *ab_inserir_no(NO *raiz, ITEM *item, int lado, int chave){
    if(raiz != NULL){
        raiz->esq = ab_inserir_no(raiz->esq, item, lado, chave);
        raiz->dir = ab_inserir_no(raiz->dir, item, lado, chave);

        if(chave == item_get_chave(raiz->item)){
            if(lado == FILHO_ESQ) raiz->esq = ab_criar_no(item);
            else if(lado == FILHO_DIR) raiz->dir = ab_criar_no(item);
        }
    }

    return (raiz);
} 


AB *ab_criar(void){
    AB *r = (AB*) malloc(sizeof(AB));

    if(r != NULL){
        r->raiz = NULL;
        r->profundidade = -1;
    }

    return (r);
}

bool ab_inserir(AB *T, ITEM *item, int lado, int chave){
    if(T->raiz == NULL) return ((T->raiz = ab_criar_no(item)) != NULL);

    return ((T->raiz = ab_inserir_no(T->raiz, item, lado, chave)) != NULL);
}

void ab_apagar_arvore(AB **T){
    apagar_arvore(&(*T)->raiz);
    free(*T);
    *T = NULL;
}

bool ab_remover(AB *T, int chave){
    if(T != NULL) return (ab_remover_aux(&T->raiz, chave));
    return (false);
}  
