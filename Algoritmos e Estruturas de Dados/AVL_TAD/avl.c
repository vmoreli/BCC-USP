#include "avl.h"

typedef struct no_ NO;
struct no_ {
    ITEM * item;
    NO * fesq;
    NO * fdir;
    int altura;
};

struct avl_ {
    NO * raiz;
    int profundidade;
};

AVL * avl_criar(void){
    AVL * arvore = (AVL *) malloc(sizeof(AVL));
    if (arvore != NULL) {
        arvore -> raiz = NULL; arvore -> profundidade = -1;
    }
    return arvore;
}

void avl_apagar_aux(NO * raiz) {
    if(raiz != NULL) {
        avl_apagar_aux(raiz -> fesq);
        avl_apagar_aux(raiz -> fdir);

        //Apaga o nó e o item, com percurso em pós-ordem
        item_apagar(&raiz -> item);
        free(raiz);
    }
}

void avl_apagar(AVL ** arvore) {
    avl_apagar_aux((*arvore) -> raiz);
    free(*arvore);
    *arvore = NULL;
}

int avl_altura_no(NO * raiz) {
    if(raiz == NULL) {
        return -1;
    } else {
        return raiz -> altura;
    }
}

NO * avl_cria_no(ITEM * item) {
    NO * no = (NO *) malloc(sizeof(NO));
    if(no != NULL) {
        no -> altura = 0;
        no -> fdir = NULL;
        no -> fesq = NULL;
        no -> item = item;
    }
    return no;
}

NO * rodar_direita(NO * a) {
    NO * b = a -> fesq;
    a -> fesq = b -> fdir;
    b -> fdir = a;

    a -> altura = max(avl_altura_no(a -> fesq), 
                        avl_altura_no(a -> fdir)) + 1;
    b -> altura = max(avl_altura_no(b -> fesq), a -> altura) + 1;

    return b;
}

NO * rodar_esquerda(NO * a) {
    NO * b = a -> fdir;
    a -> fdir = b -> fesq;
    b -> fesq = a;

    a -> altura = max(avl_altura_no(a -> fesq), 
                    avl_altura_no(a -> fdir)) + 1;
    b -> altura = max(avl_altura_no(b -> fdir),
                    a -> altura) + 1;

    return b;
}

NO * rodar_esquerda_direita(NO * a) {
    a -> fesq = rodar_esquerda(a -> fesq);
    return rodar_direita(a);
}

NO * rodar_direita_esquerda(NO * a){
    a -> fdir = rodar_direita(a -> fdir);
    return rodar_esquerda(a);
}

NO * avl_inserir_no(NO * raiz, NO * no) {
    if (raiz == NULL)
        raiz = no;
    else if (item_get_chave(no -> item) < item_get_chave(raiz -> item))
        raiz -> fesq = avl_inserir_no(raiz -> fesq, no);
    else if (item_get_chave(no -> item) > item_get_chave(raiz -> item))
        raiz -> fdir = avl_inserir_no(raiz -> fdir, no);

    raiz -> altura = max(avl_altura_no(raiz -> fesq), avl_altura_no(raiz -> fdir)) + 1;

    if (avl_altura_no(raiz -> fesq) - avl_altura_no(raiz -> fdir) == -2)
        if(item_get_chave(no -> item) > item_get_chave(raiz -> fdir -> item))
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);

    if (avl_altura_no(raiz -> fesq) - avl_altura_no(raiz -> fdir) == 2)
        if (item_get_chave(no -> item) < item_get_chave(raiz -> fesq -> item))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);

    return raiz;
}

bool avl_inserir(AVL * arvore, int chave) {
    NO * novo;
    ITEM * item = item_criar(chave);

    if(arvore == NULL) return (false);
    novo = avl_cria_no(item);
    if (novo != NULL) {
        arvore -> raiz = avl_inserir_no(arvore -> raiz, novo);
        return(true);
    }

    return(false);
}

void troca_max_esq(NO *troca, NO *raiz, NO *ant){
    if(troca->fdir != NULL){
        troca_max_esq(troca->fdir, raiz, troca);
        return;
    }

    if(raiz == ant) ant->fesq = troca->fesq;
    else ant->fdir = troca->fesq;

    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

NO * avl_remover_aux(NO ** raiz, int chave){
    NO *p;

    if(*raiz == NULL)
        return NULL;
    else if(chave == item_get_chave((*raiz)->item)) {

        if((*raiz)->fesq == NULL || (*raiz)->fdir == NULL) {
            p = *raiz;
            if((*raiz)->fesq == NULL)
                *raiz = (*raiz)->fdir;
            else
                *raiz = (*raiz)->fesq;
            free(p);
            p = NULL;
        } else 
            troca_max_esq((*raiz) -> fesq, (*raiz), (*raiz));

    } else if (chave < item_get_chave((*raiz) -> item))
        (*raiz) -> fesq = avl_remover_aux(&(*raiz) -> fesq, chave);
    else if (chave > item_get_chave((*raiz) -> item))
        (*raiz) -> fdir = avl_remover_aux(&(*raiz) -> fdir, chave);

    if(*raiz != NULL){
        (*raiz) -> altura = max(avl_altura_no((*raiz) -> fesq), avl_altura_no((*raiz) -> fdir)) + 1;
        if (avl_altura_no((*raiz) -> fesq) - avl_altura_no((*raiz) -> fdir) == -2){
            if(avl_altura_no((*raiz) -> fdir -> fesq) - avl_altura_no((*raiz)->fdir->fdir) <= 0)
                *raiz = rodar_esquerda(*raiz);
            else
                *raiz = rodar_esquerda(*raiz);
        }
        if (avl_altura_no((*raiz) -> fesq) - avl_altura_no((*raiz) -> fdir) == 2) {
            if (avl_altura_no((*raiz) -> fesq -> fesq) - avl_altura_no((*raiz) -> fesq -> fdir) >= 0)
                *raiz = rodar_direita(*raiz);
            else
                *raiz = rodar_esquerda_direita(*raiz);
        }
    }

    return *raiz;
}

bool avl_remover(AVL * T, int chave){
    return ((T -> raiz = avl_remover_aux(&T->raiz, chave)) != NULL);
}

void avl_imprime_aux(NO * raiz) {
    if(raiz != NULL) {
        avl_imprime_aux(raiz -> fesq);

        item_imprimir(raiz -> item);
        printf("\n");

        avl_imprime_aux(raiz -> fdir);
    }
}

void avl_imprimir_crescente(AVL * T){
    avl_imprime_aux(T -> raiz);
}

bool pertence_aux(NO * raiz, int chave){
    if(raiz == NULL) return false;

    if(chave == item_get_chave(raiz -> item)) return true;

    if(chave > item_get_chave(raiz -> item)) return pertence_aux(raiz -> fdir, chave);
    
    if(chave < item_get_chave(raiz -> item)) return pertence_aux(raiz -> fesq, chave);
}

bool pertence(AVL * set, int chave){
    if(set != NULL) return pertence_aux(set -> raiz, chave);
    return false;
}

void uniao_insere(NO * raiz, AVL * set_dest){
    if(raiz == NULL) return;

    //qual percurso na árvore seria melhor para gerar inserções mais simples (sem muitas rotações)?
    //em ordem - elementos em ordem crescente -> necessita de rotação simples a cada duas inserções
    //ou seja: pré-ordem ou pós-ordem

    uniao_insere(raiz -> fesq, set_dest);
    uniao_insere(raiz -> fdir, set_dest);

    avl_inserir(set_dest, item_get_chave(raiz -> item));
}

AVL * uniao(AVL * set1, AVL * set2){
    AVL * set_uniao = avl_criar();

    uniao_insere(set1 -> raiz, set_uniao);
    uniao_insere(set2 -> raiz, set_uniao);

    return set_uniao;
}