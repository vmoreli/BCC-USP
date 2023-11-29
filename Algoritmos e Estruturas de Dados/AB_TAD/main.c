#include "ab.h"

int main(int argc, char *argv[]){ 
    AB *A = ab_criar();

    int n, m;
    int a, b, c;

    scanf("%d", &n);

    while(n--){
        scanf("%d %d %d", &a, &b, &c);

        ITEM *item = item_criar(a);

        ab_inserir(A, item, b, c);
    }

    int sum = maior(A);
    printf("%d", sum);

    ab_apagar_arvore(&A);
      	
    return (0);
}