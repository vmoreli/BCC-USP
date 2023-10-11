#ifndef PONTO_H
    #define PONTO_H
	#include <stdbool.h>
	
    typedef struct ponto_ PONTO;
    PONTO *ponto_criar(float x, float y);
     /*
    Mudança: ponto apagar necessita da passagem por referência do ponteiro para atribuição de NULL
    */
    void ponto_apagar(PONTO **p);
    bool ponto_set(PONTO *p, float x, float y);

    /*
    Função que recebe dois pontos e retorna a distancia entre eles. Essa função é utilizada pela função que calcula
    a distancia entre um ponto e um circulo, mas também é aplicável em outros contextos, por isso a escolha de 
    implementa-lá separadamente.
    */
    float distancia_pontoponto(PONTO *p1, PONTO *p2);

#endif





