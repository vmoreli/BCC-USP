#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"

//Função que lê uma palavra (sem espaços) e retorna o endereço da string alocada
//Para evitar desperdício de memória, a string é primeiramente alocada na heap com o tamanho máximo previsto,
//e então alocada dinamicamente com seu tamanho exato.
char * ler_palavra(){
    char aux[MAXPLVR], * str;
    scanf(" %s", aux); //Primeiramente alocada na stack com o tamanho máximo
    str = (char *) malloc((strlen(aux) + 1) * sizeof(char)); //Alocação dinâmica com o tamanho da palavra, economizando memória
    strcpy(str, aux); //Copiando string da stack para a heap

    return str;
}

//Função que lê a definição (até a quebra de linha - \n). 
//Para evitar desperdício de memória, a string é primeiramente alocada na heap com o tamanho máximo previsto,
//e então alocada dinamicamente com seu tamanho exato.
char * ler_definicao(){
    char aux[MAXDESCR], * str; //string que será lida
    char c;
    int tam = 0; //tamanho da string
    c = getchar();

    while(c == ' '){
        c = getchar();
    }

    while (c != '\n' && tam < MAXDESCR - 1){ //lê a string até o \n
        aux[tam] = c;
        tam++;
        c = getchar();
    }

    if(tam == 0)
        return ler_definicao();

    aux[tam] = '\0';

    str = (char *) malloc((tam + 1) * sizeof(char)); //Alocação dinâmica com o tamanho da descrição
    strcpy(str, aux); //Copiando string da stack para a heap
    return str;
}

//Função que é chamada pelo comando 'insercao'. Lê a palavra e a definição, inserindo o verbete no dicionario por meio da 
// função sklist_insere do TAD SKIPLIST
void insercao(SKIPLIST * skiplist){

    char * palavra = ler_palavra();
    char * definicao = ler_definicao();


    if(sklist_insere(skiplist, palavra, definicao) == false){ //inserção do verbete
        printf("OPERACAO INVALIDA\n"); // não foi possível realizar a inserção, pois a lista não existe/está cheia, ou porque a palavra já está no dicionario
        free(palavra);
        free(definicao);
    }
}

//Função que é chamada pelo comando 'remocao'. Lê a palavra e a remove por meio da função sklist_remover do TAD SKIPLIST
void remocao(SKIPLIST * skiplist){
    char * palavra = ler_palavra();

    VERBETE * tmp = sklist_remover(skiplist, palavra); // remoção do verbete
    if(tmp == NULL)
        printf("OPERACAO INVALIDA\n"); // palavra não está no dicionário
    else
        verbete_apagar(&tmp);
    free(palavra);
}

//Função que é chamada pelo comando 'busca'. Lê a palavra, busca por meio do comando sklist_busca do TAD SKIPLIST e então
// faz a impressão do verbete por meio da função verbete_imprimir do TAD VERBETE
void busca(SKIPLIST * skiplist){
    char * palavra = ler_palavra();
    VERBETE * aux = sklist_busca(skiplist, palavra); //busca palavra
    if (aux == NULL)
        printf("OPERACAO INVALIDA\n"); //palavra não está no dicionario
    else{
        verbete_imprimir(aux); //imprime verbete
        printf("\n");
    }
    free(palavra);
}

//Função que é chamada pelo comando 'alteracao'. Lê a palavra e a definição, procura o verbete na lista por meio da função
// sklist_busca do TAD SKIPLIST e altera sua definicao por meio da função verbete_set_definicao do TAD VERBETE
void alteracao(SKIPLIST * skiplist){
    char * palavra = ler_palavra();
    char * definicao = ler_definicao();
    VERBETE * aux = sklist_busca(skiplist, palavra); //busca a palavra
    if (aux == NULL){
        printf("OPERACAO INVALIDA\n"); //não foi possível encontrar a palavra no dicionario
        free(definicao);
    }
    else
        verbete_set_definicao(aux, definicao); //altera a definicao da palavra
        
    free(palavra);
}

//Função que é chamada pelo comando 'impressao'. Lê a letra e imprime todas as palavras iniciadas por essa letra por meio da funcao
// sklist_imprimir do TAD SKIPLIST
void impressao(SKIPLIST * skiplist){
    char letra;

    scanf(" %c", &letra); //leitura da letra
    sklist_imprimir(skiplist, letra); //impressao das palavras iniciadas pela letra
}

//Função que lê o comando desejado e chama a função correspondente
void ler_comando(SKIPLIST * skiplist){
    char comando[10] = {0};
    scanf(" %s", comando); //leitura do comando

    if(!strcmp(comando, "insercao"))
        insercao(skiplist); //chama insercao

    else if(!strcmp(comando, "remocao")){
        remocao(skiplist); //chama remocao
    }

    else if(!strcmp(comando, "busca"))
        busca(skiplist); //chama busca

    else if(!strcmp(comando, "alteracao"))
        alteracao(skiplist); //chama alteracao

    else if(!strcmp(comando, "impressao"))
        impressao(skiplist); //chama impressao
        
    else
        return;

    ler_comando(skiplist); // recursão - leitura de comandos continua até a execução ser encerrada
}

int main(){
    SKIPLIST * skiplist = sklist_criar(); //criacao da lista

    ler_comando(skiplist);

    sklist_apagar(&skiplist); //apaga a lista
}