/*
Exercicio: implementar uma funcao que receba 2 vetores ordenados, 
e adicione os elementos desses 2 vetores num terceiro vetor de forma ordenada,
considerando que o final de um dos vetores não necessariamente comece no outro
Alunos:
Giordano Santorum Lorenzetto
Karl Cruz Altenhofen
Luiz Fellipe Catuzzi Araujo Hotoshi
Maicon Chaves Marques
Paulo Henrique dos Santos Almeida
Victor Moreli dos Santos
*/
#include <stdio.h>

void merge(int * v1, int N1, int * v2, int N2,int * v3){
    if(N1==0 && N2==0){
        return;
    } else {
        if(N1 == 0){
            *v3 = *v2;
            merge(v1, N1, (N2 == 1? v2 : v2 + 1), N2-1, v3 + 1);
        } else if(N2 == 0){
                *v3 = *v1;
                merge((N1 == 1? v1 : v1 + 1), N1-1, v2, N2, v3 + 1);
        } else if((*v1) < (*v2)){
                *v3 = *v1;
                merge((N1 == 1? v1 : v1 + 1), N1-1, v2, N2, v3 + 1);
        } else {
                *v3 = *v2;
                merge(v1, N1, (N2 == 1? v2 : v2 + 1), N2-1, v3 + 1);
        }

    }

}

