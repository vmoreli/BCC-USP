#ifndef ITEM_H
	#define ITEM_H
	
	#include <stdbool.h>

	typedef struct item_ ITEM;

	ITEM *item_criar(int chave1, int chave2);
	bool item_apagar(ITEM **item);
	void item_imprimir(ITEM *item);
	int item_get_chave1(ITEM *item);
	int item_get_chave2(ITEM *item);
	bool item_set_chave(ITEM *item, int chave);

#endif
