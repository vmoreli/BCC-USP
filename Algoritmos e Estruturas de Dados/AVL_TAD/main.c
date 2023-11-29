#include "avl.h"

int main() {
    AVL * set1 = avl_criar();

    avl_inserir(set1, 10);
    avl_inserir(set1, 17);
    avl_inserir(set1, 7);
    avl_inserir(set1, 5);
    avl_inserir(set1, 8);
    avl_inserir(set1, 7);
    
    avl_imprimir_crescente(set1);

    printf("\n////////////////\n");

    AVL * set2 = avl_criar();

    avl_inserir(set2, 65);
    avl_inserir(set2, 1);
    avl_inserir(set2, 2);
    avl_inserir(set2, 10);
    avl_inserir(set2, 0);
    avl_inserir(set2, 9);
    avl_inserir(set2, 5);
    avl_inserir(set2, 7);
    
    avl_imprimir_crescente(set2);

    printf("\n////////////////\n");

    AVL * set3 = uniao(set1, set2);
    avl_imprimir_crescente(set3);

    pertence(set3, 10)? printf("pertence\n") : printf("não pertence\n");
    pertence(set3, 5)? printf("pertence\n") : printf("não pertence\n");
    pertence(set1, 43)? printf("pertence\n") : printf("não pertence\n");
    pertence(set3, 11)? printf("pertence\n") : printf("não pertence\n");

    avl_apagar(&set1);
    avl_apagar(&set2);
    avl_apagar(&set3);

    
}