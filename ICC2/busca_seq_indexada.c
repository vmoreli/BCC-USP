#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

Acompanha arquivos de entrada (1.in) e saída (1.out)

*/

//struct que representa um bloco da tabela de kindex - contém o kindex e a posição correspondente
typedef struct bloco_indice_ {
    int kindex;
    int pos;
} bloco_indice;

//função que cria a tabela de índices de acordo com o vetor original (v), seu tamanho (n), a tabela de indices (indice[]), e o numero de índices
//desejados (tam_indice)
void cria_indice(bloco_indice indice[], int tam_indice, int v[], int n){
    int pos, i = 0;

    while(i < tam_indice){
        pos = i * n/tam_indice;
        indice[i].kindex = v[pos];
        indice[i].pos = pos;
        i++;
    }
}

//função que realiza a busca sequencial indexada do elemento x
int busca_sequencial_indexada(bloco_indice indice[], int v[], int n, int tam_indice, int x){
    int i;

    for(i = 0; i < tam_indice && indice[i].kindex <= x; i++);

    i = indice[i - 1].pos;

    while(i < n && v[i] < x)
        i++;

    if(i < n && v[i] == x)
        return i;
    else
        return -1;  
}

//função que realiza um busca sequencial convencional do elemento x
int busca_sequencial_convencional(int v[], int n, int x){
    int i;

    for(i = 0; i < n && v[i] < x; i++); 

    if(i < n && v[i] == x)
        return i;
    else
        return -1;
}

//algoritmo usado para ordenar o vetor original (passo necessário para a implementação de uma busca sequencial indexada)
void shell_sort(int * v, int n){
    int i, j, x, h;

    h = 1;
    while(h < n)
        h = 3*h + 1;
    
    while(h > 0){
        for(i = h; i < n; i++){
            x = v[i]; 
            j = i;
            while(j > h - 1 && x < v[j - h]){
                v[j] = v[j - h];
                j -= h;
            }
            v[j] = x;
        }
        h /= 3;
    }
}

int main(){
    int v[10000], tmp, x;
    
    //leitura do vetor original
    for (int i = 0; i < 10000; i++)
    {
        scanf(" %d", &tmp);
        v[i] = tmp;
    }

    //ordenação
    shell_sort(v, 10000);

    clock_t inicio_conv = clock(); //início da contagem da busca convencional

    //busca convencional
    for (int i = 0; i < 50; i++)
    {
        scanf(" %d", &x);
        for(int j = 0; j < 1000; j++)
            busca_sequencial_convencional(v, 10000, x);
    }

    clock_t final_conv = clock(); //fim da contagem da busca convencional
    
    //criação da tabela de índices
    bloco_indice * indice = malloc(sizeof(bloco_indice) * 50);
    cria_indice(indice, 50, v, 10000);

    clock_t inicio_index = clock(); //ínicio da contagem da busca indexada

    //busca indexada
    for (int i = 0; i < 50; i++)
    {
        scanf(" %d", &x);
        for(int j = 0; j < 1000; j++)
            busca_sequencial_indexada(indice, v, 10000, 50, x);
    }

    clock_t final_index = clock(); //fim da contagem da busca indexada

    double tempo_conv = (double) (final_conv -  inicio_conv)/CLOCKS_PER_SEC;
    double tempo_index = (double) (final_index - inicio_index)/CLOCKS_PER_SEC;

    printf("Tempo da busca sequencial convencional: %lf\n", tempo_conv);
    printf("Tempo da busca sequencial indexada: %lf", tempo_index);

}