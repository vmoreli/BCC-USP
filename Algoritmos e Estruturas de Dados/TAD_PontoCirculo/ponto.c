#include "ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ponto_{
    float x;
    float y;
};

PONTO * ponto_criar(float x, float y){
    PONTO * ponto;
    
    if((ponto = (PONTO *) malloc(sizeof(PONTO))) == NULL)
        exit(1);
    
    ponto -> x = x;
    ponto -> y = y;

    return ponto;
}

void ponto_apagar(PONTO **p){
    free(*p);
    *p = NULL;
}

bool ponto_set(PONTO *p, float x, float y){
    if(p != NULL){

        p -> x = x;
        p -> y = y;

        return 1; //Operacao bem sucedida
    } else 

        return 0; //Operacao nao pode ser feita
}

float distancia_pontoponto(PONTO * p1, PONTO * p2){
    float distancia = sqrt(fabs(pow((p1 -> x) - (p2 -> x), 2) + pow((p1 -> y) - (p2 -> y), 2)));
    return distancia;
}