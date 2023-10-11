#include <stdio.h>
#include "ponto.h"
#include "circulo.h"

int main(){

    float p_x, p_y, c_x, c_y, raio;
    PONTO * p;
    CIRCULO * circ;

    //Leitura das coordenadas do ponto e criação do ponto
    scanf("%f %f", &p_x, &p_y);
    p = ponto_criar(p_x, p_y);

    /*
    Leitura do raio e das coordenadas do centro do circulo,
    e criacao do circulo
    */
    scanf("%f %f %f", &c_x, &c_y, &raio);
    circ = circulo_criar(ponto_criar(c_x, c_y), raio);

    posicao_relativa_pontocirc(p, circ);

    ponto_apagar(&p);
    circulo_apagar(&circ);

    return 0;
}