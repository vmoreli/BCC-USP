#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void cartas(int n){
    FILA * fila = fila_criar();

    //Inserindo as cartas na fila
    for (int i = 1; i <= n; i++)
    {
        fila_inserir(fila, item_criar(i));
    }

    printf("Discarded cards:");

    //Faz as operações de remoção e inserção na fila, printando as cartas removidas, até sobrar uma carta
    while(fila_tamanho(fila) != 1){
        printf(" %d", item_get_chave(fila_remover(fila)));
        if(fila_tamanho(fila) != 1) printf(",");
        fila_inserir(fila, fila_remover(fila));
    }
        
    //Printa a carta remanescente
    printf("\nRemaining card: %d\n", item_get_chave(fila_remover(fila)));

    fila_apagar(&fila);
    
}