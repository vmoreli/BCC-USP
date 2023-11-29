#include <stdio.h>
#include <stdlib.h>

/*
Esse arquivo se trata da implementação de um hashing estático fechado, com função de hash (i = 0) e rehash (i > 0) combinadas.
A tabela de hash é armazenada na memória heap.
As operações  de busca, inserção e remoção foram implementadas.
Posições nunca preenchidas tem valor -1, e previamente preenchidas tem valor -2.
*/

#define B 10 //definição do número de buckets

//função de hashing
int h(int k, int i){
    return((k + i) % B);
}

int * inicializa_hashing(){
    int * T = malloc(B * sizeof(int));

    for (int i = 0; i < B; i++)
    {
        T[i] = -1;
    }
}

int buscar(int T[], int k){
    if(T != NULL){
        int j;
        for (int i = 0; i < B; i++)
        {
            j = h(k, i); //aplicação da função de hashing em k, com i
            if(T[j] == k)
                return j; //encontra elemento na tabela de hashing
            else if(T[j] == -1)
                    return(-1); //encontra marcador de ausência de elemento
        }
    }

    return(-1); //Tabela de hashing nula ou busca não encontrou o elemento e nem -1 em posições contíguas
}

int inserir(int T[], int k){
    if(T != NULL){
        int j;
        for (int i = 0; i < B; i++)
        {
            j = h(k, i);
            if(T[j] == -1 || T[j] == -2){ //se posição desocupada (-1) ou posição previamente ocupada (-2)
                T[j] = k; //insere elemento
                return j;
            }
        }
    }

    return(-1); //tabela de hashing nula ou não foi encontrada posição disponível para a inserção
}

int remocao(int T[], int k){
    if(T != NULL){
        int j;
        for (int i = 0; i < B; i++)
        {
            j = h(k, i);
            if(T[j] == k){
                T[j] = -2;
                return j;
            }
            if(T[j] == -1)
                return -1; //elemento não está presente na tabela - otimização
        }
    }

    return(-1); //tabela de hashing nula ou não está na tabela (todas as posições ocupadas ou previamente ocupadas)
}