#include "circulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct circulo_{
    PONTO * centro;
    float raio;
};

CIRCULO * circulo_criar(PONTO *p, float raio){
    CIRCULO * circulo;

    if((circulo = (CIRCULO *) malloc(sizeof(CIRCULO))) == NULL)
        exit(1);

    circulo -> centro = p;
    circulo -> raio = raio;

    return circulo;
}

void circulo_apagar(CIRCULO ** circ){
    ponto_apagar(&((*circ)->centro));

    free(*circ);
    *circ = NULL;
}

float circulo_area (CIRCULO * circ){
    float area = pow((circ -> raio), 2) * 3.14159;
    return area;
}

float distancia_pontocirc(PONTO *p, CIRCULO * circ){
    return distancia_pontoponto(p, circ -> centro);
}

void posicao_relativa_pontocirc(PONTO *p, CIRCULO *circ){
    float dist = distancia_pontocirc(p, circ);
    if(dist < circ -> raio)
        printf("O ponto é interior à circunferência.\nDistância: %.2f\n", dist);
    else if(dist > circ -> raio)
        printf("O ponto é exterior à circunferência.\nDistância: %.2f\n", dist);
    else
        printf("O ponto pertence à circunferência.\nDistância: %.2f\n", dist);
}
