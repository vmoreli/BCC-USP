#ifndef CIRCULO_H
    #define CIRCULO_H

    #include "ponto.h"

    typedef struct circulo_ CIRCULO;
    CIRCULO *circulo_criar(PONTO *p, float raio);

    /*
    Mudança: círculo apagar necessita da passagem por referência do ponteiro para atribuição de NULL
    */
    void circulo_apagar (CIRCULO** circ);
    float circulo_area (CIRCULO* circ);
    
    /*
    A tarefa de calcular a distancia entre um ponto e um circulo (feita pela função abaixo) é equivalente a chamar a função
    que calcula distancia entre dois pontos, passando o ponto e o centro do círculo. Mas, para uma melhor modularização,
    a função abaixo foi implementada.
    */
    float distancia_pontocirc(PONTO *p, CIRCULO * circ);

    /*
    Função que imprime a posição relativa entre ponto e círculo e a distancia
    */
    void posicao_relativa_pontocirc(PONTO *p, CIRCULO * circ);

#endif


