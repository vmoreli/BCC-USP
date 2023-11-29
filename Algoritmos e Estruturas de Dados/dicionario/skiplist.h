#ifndef SKIPLIST_H
	#define SKIPLIST_H
	/*
	Este é o arquivo .h da estrutura Skiplist, que representa o dicionário.
	*/

	/*a maior entrada para esse problema sera de aproximadamente 10000 insercoes,
	 como floor[log_2(10000)] = 13, essa foi a nossa escolha para o numero maximo de camadas*/
	#define CAMADASMAX 13

	#include "verbete.h"

	typedef struct skiplist_ SKIPLIST;

	SKIPLIST * sklist_criar(void);
	bool sklist_insere(SKIPLIST * skiplist, char * palavra, char * definicao);
	VERBETE * sklist_remover(SKIPLIST * skiplist, char * palavra);
	void sklist_apagar(SKIPLIST **skiplist);
	VERBETE * sklist_busca(SKIPLIST * skiplist, char * palavra);
	bool sklist_vazia(SKIPLIST *skiplist);
	bool sklist_cheia(SKIPLIST *skiplist);
	int sklist_imprimir(SKIPLIST *skiplist, char letra);
	int sklist_get_camadas(SKIPLIST * skiplist);

#endif