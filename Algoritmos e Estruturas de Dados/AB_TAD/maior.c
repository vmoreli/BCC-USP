#include "item.h"
#include "ab.h"

/* 
Duas alternativas para a implementação da função que retorna o maior elemento de uma árvore binária:
- Na primeira, a árvore é percorrida em pós ordem, assim vendo qual o maior elemento das sub-árvores esquerda 
    e direita até a raiz;
- Na segunda, usa-se uma variável auxiliar, a qual é alterada diretamente pelo seu endereço caso o elemento
    em que se encontra naquele ponto do trajeto seja maior do que o valor guardado pela variável, realizando assim
    um percurso em pré-ordem
*/

// int ab_maior(NO * no){

//     if(no == NULL)
//         return -2147483648;

//     int maior = item_get_chave(no -> item);
//     int maior_esq = ab_maior(no -> esq);
//     int maior_dir = ab_maior(no -> dir);

//     if(maior_esq > maior)
//         maior = maior_esq;
//     if(maior_dir > maior)
//         maior = maior_dir;

//     return maior;
// }

void ab_maior(NO * no, int * maior){
    
    if(no != NULL){
        if(item_get_chave(no -> item) > *maior)
                *maior = item_get_chave(no -> item);

        ab_maior(no -> esq, maior);
        ab_maior(no -> dir, maior);
    }
    
}


int maior (AB * T){

    if(T != NULL){
        int maior = item_get_chave(T -> raiz -> item);
        ab_maior(T -> raiz, &maior);
        return maior;
    }

}