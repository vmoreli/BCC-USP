#include "verbete.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Este é o arquivo .c do TAD Verbete, que representa um verbete de um dicionário, tendo em sua formação
duas strings: uma palavra (sem espaços) e uma definição. A struct verbete_ está definida em seguida.
*/

struct verbete_{
    char * palavra;
    char * definicao;
};

// Função que cria o verbete, dado uma palavra e definição já alocadas anteriormente
VERBETE * verbete_criar(char * palavra, char * definicao){
    VERBETE * verbete = (VERBETE *) malloc(sizeof(VERBETE));
    if(verbete != NULL){
        verbete -> palavra = palavra;
        verbete -> definicao = definicao;
    }
    return verbete;
}

//Função que apaga um verbete, liberando a memória alocada para si e para as strings que o compõem
bool verbete_apagar(VERBETE ** verbete){
    if(*verbete == NULL)
        return false;
    
    free((*verbete)->palavra);
    free((*verbete)->definicao);
    free(*verbete);
    return true;
}

//Função que imprime um verbete, com a palavra seguida por um espaço e a definição
void verbete_imprimir(VERBETE * verbete){
    if(verbete != NULL)
        printf("%s %s", verbete -> palavra, verbete -> definicao);
}

//Função que, dado um verbete, retorna um ponteiro para a sua palavra
char * verbete_get_palavra(VERBETE * verbete){
    return verbete != NULL ? verbete -> palavra : NULL;
}

//Função que, dado um verbete, retorna um ponteiro para a sua definição
char * verbete_get_definicao(VERBETE * verbete){
    return verbete != NULL ? verbete -> definicao : NULL;
}

//Função que, dado um verbete e uma definição, altera a definição do verbete
bool verbete_set_definicao(VERBETE * verbete, char * definicao){
    if(verbete == NULL)
        return false;
    
    if(verbete -> definicao != NULL)
        free(verbete -> definicao); //Caso o verbete tenha uma definição anterior, ela precisa ser desalocada

    verbete -> definicao = definicao; //Alterando a definição
    return true;
}

//Função que, dado um verbete e uma palavra, altera a palavra do verbete.
//Essa função é utilizada no contexto de alterar a palavra do nó cabeça para criar uma condição de parada na busca
bool verbete_set_palavra(VERBETE * verbete, char * palavra){
    if(verbete == NULL)
        return false;

    verbete -> palavra = palavra; //Alterando a palavra
    return true;
}
