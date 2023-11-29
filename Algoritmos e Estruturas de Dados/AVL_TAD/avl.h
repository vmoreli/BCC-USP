#ifndef AVL_H
    #define AVL_H

    #include "item.h"
    #define max(a, b) ((a > b) ? a :  b)

    typedef struct avl_ AVL;

    AVL * avl_criar();
    void avl_apagar(AVL ** avl);
    bool avl_inserir(AVL * avl, int chave);
    bool avl_remover(AVL * T, int chave);
    void avl_imprimir_crescente(AVL * T);
    bool pertence(AVL * set, int chave);
    AVL * uniao(AVL * set1, AVL * set2);

#endif