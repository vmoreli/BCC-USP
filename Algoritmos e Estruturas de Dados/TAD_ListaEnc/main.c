#include "item.h"
#include "lista.h"

int main(){
    int n, chave;
    LISTA * lista = lista_criar();

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &chave);
        lista_inserir(lista, chave);
    }
    
    lista_inverter(lista);
    lista_imprimir(lista);
    lista_apagar(&lista);
}