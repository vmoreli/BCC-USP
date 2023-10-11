#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main(){

    int m, n;
    int pos[2] = {0, 0};

    scanf("%d %d", &m, &n);

    int lab[m][n];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf(" %d", &lab[i][j]);
        }
    }

    PILHA * pilha = pilha_criar();

    printf("(%d, %d)\n", pos[0], pos[1]);


    while(lab[pos[0]][pos[1]] != 2){

        lab[pos[0]][pos[1]] = 0;

        if(pos[0] + 1 < m && lab[pos[0] + 1][pos[1]] != 0){
            pilha_empilhar(pilha, item_criar(pos[0] + 1, pos[1]));
        } 

        if(pos[1] - 1 >= 0 && lab[pos[0]][pos[1] - 1] != 0){
            pilha_empilhar(pilha, item_criar(pos[0], pos[1] - 1));
        }

        if(pos[0] - 1 >= 0 && lab[pos[0] - 1][pos[1]] != 0){
            pilha_empilhar(pilha, item_criar(pos[0] - 1, pos[1]));
        }

        if(pos[1] + 1 < n && lab[pos[0]][pos[1] + 1] != 0){
            pilha_empilhar(pilha, item_criar(pos[0], pos[1] + 1));
        }

        if(pilha_vazia(pilha)){
            printf("Saída não encontrada.");
            break;
        }

        ITEM * tmp = pilha_desempilhar(pilha);

        if(tmp != NULL){
            pos[0] = item_get_chave1(tmp);
            pos[1] = item_get_chave2(tmp);
            item_apagar(&tmp);

            if(lab[pos[0]][pos[1]] != 0) printf("(%d, %d)\n", pos[0], pos[1]);
        }
        
    }

    pilha_apagar(&pilha);
    
}