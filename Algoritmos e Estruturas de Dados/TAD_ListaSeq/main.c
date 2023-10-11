#include <stdio.h>
#include "lista.h"

int main(){
    int n, tmp;
    LISTA * lista = lista_criar();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        lista_inserir(lista, tmp);
    }
    
    lista_imprimir(lista);
    lista_apagar(&lista);

    return 0;
}