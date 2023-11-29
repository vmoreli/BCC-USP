#ifndef VERBETE_H
	#define VERBETE_H
	
	#include <stdbool.h>
	#include <stdlib.h>
	#include <stdio.h>
    #define ERRO -32000
    #define MAXPLVR 51 //maximo de caracteres de uma palavra = 50 + '\0' = 51
    #define MAXDESCR 141 //maximo de caracteres de uma descricao = 140 + '\0' = 141

	/*
	Este é o arquivo .h do TAD Verbete, que representa um verbete de um dicionário, tendo em sua formação
	duas strings: uma palavra (sem espaços) e uma definição.
	*/

	typedef struct verbete_ VERBETE;

	VERBETE *verbete_criar(char * palavra, char * definicao);
	bool verbete_apagar(VERBETE ** verbete);
	void verbete_imprimir(VERBETE *verbete);
	char * verbete_get_definicao(VERBETE *verbete);
	bool verbete_set_definicao(VERBETE *verbete, char * definicao);
	char * verbete_get_palavra(VERBETE * verbete);
	bool verbete_set_palavra(VERBETE * verbete, char * palavra);

#endif