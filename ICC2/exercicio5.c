/*
Exercicio: implementar uma funcao que insira de um elemento x
do tipo int em uma lista encadeada ordenada.
Alunos:
Giordano Santorum Lorenzetto
Karl Cruz Altenhofen
Luiz Fellipe Catuzzi Araujo Hotoshi
Maicon Chaves Marques
Paulo Henrique dos Santos Almeida
Victor Moreli dos Santos
*/

#include <stdio.h>
#include <stdlib.h>

struct cel{
    int conteudo;
    struct cel *prox;

};
typedef struct cel cell;

void insere(int x, cell* ini){
    cell *p;
    p = (cell*)malloc(sizeof(cell));
    p->conteudo = x;
    if(ini == NULL){
        ini = p;
        return;
    }
    if(ini->prox != NULL){
        while(ini->prox->conteudo < x){
            ini = ini->prox;
            if(ini->prox == NULL){
                break;
            }
        }
    }

    p->prox = ini->prox;
    ini->prox = p;

}

