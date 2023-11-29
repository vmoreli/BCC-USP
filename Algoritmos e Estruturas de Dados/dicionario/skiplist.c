#include "skiplist.h"
#include <string.h>


/*
Este é o arquivo .c da estrutura Skiplist, que representa o dicionário. 
A struct skiplist_ está definida em seguida, e usa um nó sentinela para auxiliar na busca, inserção e remoção.
Autores: Giordano Santorum Lorenzetto e Victor Moreli dos Santos, 2023
*/

typedef struct no_ NO;

struct no_{
    int camada; //numero de camadas que o no está presente
    VERBETE * verbete; //item armazenado
    NO ** proxs; //vetor de ponteiros que contém os proximos nós de cada camada em que o nó está presente
};

struct skiplist_{
    int camadas; //quantidade de camadas que possuem pelo menos 1 nó na lista
    NO * sentinela; //nó sentinela
};

//cria um novo nó
NO * novo_no(char * palavra, char * definicao, int camada){
    //criando o verbete
    VERBETE * verbete = verbete_criar(palavra, definicao);

    //alocando a memoria que será utilizada pelo nó
    NO * no = (NO *) malloc(sizeof(NO));
    if(no != NULL){
        no -> camada = camada;
        no -> verbete = verbete;

        //alocação do vetor de proximos nós
        no -> proxs = (NO **) malloc(sizeof(NO*) * camada);
        if(no -> proxs != NULL)
            for (int i = 0; i < camada; i++)
                no -> proxs[i] = NULL; //inicialização de todos os ponteiros para NULL
        
    } else {
        //alocação do nó falhou
        verbete_apagar(&verbete);
    }

    return no;
}

//libera o vetor de proximos do no e o ponteiro para o nó (não libera a memoria ocupada pelo verbete!)
void apagar_no(NO ** no){
    if(*no == NULL)
        return;

    free((*no) -> proxs);
    free(*no);
    *no = NULL;
}

// gera um numero aleatorio entre 1 e CAMADASMAX inclusive
int camada_aleatoria(SKIPLIST * skiplist){
    int t = rand(), //numero aleatorio entre 0 e RAND_MAX
        i = 1,
        j = 2; //j = 2^{i}

    //probabilidade de gerar um número i + 1 = 1/2 * probabilidade de gerar um numero i.
    while(i < CAMADASMAX && t <= RAND_MAX/j){
        j *= 2;
        i ++;
    }

    return i;
}


//cria a skiplist e inicializa as suas variáveis
SKIPLIST * sklist_criar(void){
    SKIPLIST * skiplist = (SKIPLIST *) malloc(sizeof(SKIPLIST));

    if(skiplist != NULL){
        skiplist -> camadas = 0;//lista vazia possui 0 camadas
        skiplist->sentinela = novo_no(NULL, NULL, CAMADASMAX);//nó sentinela presente em todas as camadas

        //fazendo com que o nó sentinela aponte para ele mesmo em todas as camadas(skiplist circular)
        for (int i = 0; i < CAMADASMAX; i++)
            skiplist->sentinela->proxs[i] = skiplist->sentinela;
           
    }
    return skiplist;
}

//função recursiva que busca um verbete na lista (retorna NULL caso não o encontre)
VERBETE * busca_camada(NO * no, char * palavra, int camada, NO * sentinela){
    int compara = strcmp(palavra, verbete_get_palavra(no->proxs[camada]->verbete));
    
    if(compara <= 0){
        if(no->proxs[camada] != sentinela && compara == 0)
            return no -> proxs[camada] -> verbete; // nó encontrado
        else
            if(camada != 0)
                return busca_camada(no, palavra, camada - 1, sentinela);//o nó não foi encontrado na camada atual a busca segue na camada abaixo
            else
                return NULL;//o nó não foi encontrado na lista
    }
    return busca_camada(no->proxs[camada], palavra, camada, sentinela);//o nó ainda pode estar na camada, segue a busca com o proximo nó da camada
}

//função que faz a busca de um verbete na lista (retorna NULL caso não encontre)
VERBETE * sklist_busca(SKIPLIST * skiplist, char * palavra){
    if(sklist_vazia(skiplist) || skiplist == NULL) //se a lista estiver vazia ou for nula, não é necessário fazer a busca
        return NULL;

    verbete_set_palavra(skiplist->sentinela->verbete, palavra);//definindo a palavra do verbete do nó sentinela para 'palavra', a fim de auxiliar na busca
    VERBETE * aux = busca_camada(skiplist -> sentinela, palavra, (skiplist -> camadas) - 1, skiplist -> sentinela);//chamada da função recursiva de busca
    verbete_set_palavra(skiplist->sentinela->verbete, NULL);//definindo a palavra do verbete do nó sentinela para NULL, a fim de evitar erros

    return aux;
}

//função recursiva que insere um verbete na lista
void insere_camada(SKIPLIST * skiplist, NO * anterior, NO * no, int camada){
    int compara = strcmp(verbete_get_palavra(no -> verbete), verbete_get_palavra(anterior -> proxs[camada] -> verbete));

    if(compara <= 0){//local de inserção na camada atual encontrado
        if(camada < no -> camada){//se o nó tem pelo menos 'camada' camadas, inserimos na camada atual
            no -> proxs[camada] = anterior -> proxs[camada];
            anterior -> proxs[camada] = no;
            if(camada == 0){
                if(no->camada > skiplist -> camadas)
                    skiplist -> camadas = no->camada;//se o nó tiver o maior numero de camadas até o momento, atualizamos a quantidade de camadas da lista.
                return;//fim da inserção
            }
        }
        insere_camada(skiplist, anterior, no, camada - 1);//continuando a inserção em camadas inferiores
        
    }
    else//local da inserção não encontrado na camada atual, continua a inserção com o proximo nó da camada
        insere_camada(skiplist, anterior -> proxs[camada], no, camada);

}

//função que faz a inserção de um verbete na lista (retorna false caso não seja possível inserir)
bool sklist_insere(SKIPLIST * skiplist, char * palavra, char * definicao){
    //se a lista for nula, estiver cheia, ou o item já estiver presente na lista, não é possível fazer a inserção
    if(skiplist != NULL && !sklist_cheia(skiplist) && sklist_busca(skiplist, palavra) == NULL){
        NO * no = novo_no(palavra, definicao, camada_aleatoria(skiplist));//nó que será inserido

        verbete_set_palavra(skiplist->sentinela->verbete, palavra);//definindo a palavra do verbete do nó sentinela para 'palavra', a fim de auxiliar na inserção
        insere_camada(skiplist, skiplist->sentinela, no, CAMADASMAX - 1);//chamada da função recursiva de inserção
        verbete_set_palavra(skiplist->sentinela->verbete, NULL);//definindo a palavra do verbete do nó sentinela para NULL, a fim de evitar erros
        return true;
    }
    return false;
}

//função recursiva que remove um verbete da lista (retorna NULL caso não encontre o verbete na lista)
VERBETE * remove_camada(SKIPLIST * skiplist, NO * anterior, char * palavra, int camada){
    int compara = strcmp(palavra, verbete_get_palavra(anterior -> proxs[camada] -> verbete));

    if(compara == 0 && anterior -> proxs[camada] != skiplist->sentinela){// se o nó achado for o nó cabeça, então o nó não foi encontrado na camada atual
        // nó encontrado, então será removido da camada atual
        NO * atual = anterior->proxs[camada];
        anterior -> proxs[camada] = atual -> proxs[camada];

        if((anterior == skiplist -> sentinela) && (atual -> proxs[camada] == skiplist -> sentinela)){ 
            if(skiplist -> camadas != 0) skiplist -> camadas--;//nó removido é o unico presente na camada,logo diminuimos o numero de camadas da lista
        }

        if(camada == 0){
            VERBETE * tmp = atual -> verbete;
            apagar_no(&atual);//liberando a memoria que não será mais utilizada
            return tmp;//fim da remoção
        }
        return remove_camada(skiplist, anterior, palavra, camada - 1);//continuando a remoção em camadas inferiores
    }
    if(compara <= 0){ // nó não encontrado na camada (se camada == 0, então o nó não esta presente na lista)
        if(camada == 0)
            return NULL;
        return remove_camada(skiplist, anterior, palavra, camada - 1);//continuando a remoção em camadas inferiores
    }
    return remove_camada(skiplist, anterior-> proxs[camada], palavra, camada);//continuando a remoção na mesma camada
}

//função que faz a remoção de um verbete da lista (retorna NULL caso não encontre o verbete na lista)
VERBETE * sklist_remover(SKIPLIST * skiplist, char * palavra){
    //se a lista for nula ou estiver vazia, não é possível fazer a remoção
    if(skiplist != NULL && !sklist_vazia(skiplist)){
        verbete_set_palavra(skiplist -> sentinela -> verbete, palavra);//definindo a palavra do verbete do nó sentinela para 'palavra', a fim de auxiliar na remoção
        VERBETE * aux = remove_camada(skiplist, skiplist->sentinela, palavra, (skiplist -> camadas) - 1);//chamada da função recursiva de remoção
        verbete_set_palavra(skiplist->sentinela->verbete, NULL);//definindo a palavra do verbete do nó sentinela para NULL, a fim de evitar erros
        return aux;
    }
    return NULL;
}

//função que apaga a lista e libera toda a memória utilizada
void sklist_apagar(SKIPLIST **skiplist){
    if(*skiplist == NULL)
        return;

    //liberando a memória de todos os nós da lista e seus respectivos vetores de próximos
    NO * sentinela = (*skiplist)->sentinela, * aux;
    while (sentinela->proxs[0] != sentinela){
        aux = sentinela->proxs[0];
        sentinela->proxs[0] = aux->proxs[0];
        verbete_apagar(&(aux->verbete));
        apagar_no(&aux);
    }

    //liberando a memória do nó sentinela e seu vetor de próximos
    verbete_apagar(&(sentinela->verbete));
    apagar_no(&sentinela);

    free((*skiplist));
    *skiplist = NULL;
}

//função que retorna true caso a lista esteja vazia, e false caso contrário
bool sklist_vazia(SKIPLIST * skiplist){
    if(skiplist == NULL) 
        return false;

    //verifica se o nó sentinela aponta para ele mesmo na camada 0, nesse caso, retorna true, caso contrario, falso
    return (skiplist -> sentinela -> proxs[0] == skiplist -> sentinela? true : false);
}

//função que retorna true caso a lista seja nula ou esteja cheia, e false caso contrário
bool sklist_cheia(SKIPLIST * skiplist){
    if(skiplist == NULL) 
        return true;

    //tenta fazer a alocação de um nó com um vetor de próximos de tamanho máximo, caso falhe, significa que não há mais espaço na memoria
    NO * no = novo_no(NULL, NULL, CAMADASMAX);
    if(no != NULL){
        //liberando a memoria que não será utilizada
        verbete_apagar(&no->verbete);
        apagar_no(&no);
        return false;
    }
    return true;
}

//função recursiva que imprime as palavras que começam com o caractere letra e retorna a quantidade de palavras impressas
int imprimir(SKIPLIST * skiplist, NO * anterior, int camada, char letra){
    if(anterior -> proxs[camada] != skiplist -> sentinela){ //chegou ao final da camada atual

        char inicial_palavra = verbete_get_palavra(anterior->proxs[camada]->verbete)[0];//letra inicial da palavra do nó atual
        

        if(inicial_palavra == letra){
            /*imprime apenas se estiver na camada mais inferior para garantir que 
            não irá pular nenhuma palavra que comece com o caractere letra*/
            if(camada == 0){
                verbete_imprimir(anterior->proxs[camada]->verbete);
                printf("\n");
                return 1 + imprimir(skiplist, anterior->proxs[camada], camada, letra);//continua a impressão na mesma camada
            }

                return imprimir(skiplist, anterior, camada - 1, letra);//continua a impressão na camada abaixo
        }
        if(inicial_palavra < letra)
            return imprimir(skiplist, anterior->proxs[camada], camada, letra);//continua a impressão na mesma camada
        
    }
    if(camada == 0) return 0;//não há mais palavras na lista que começam com a letra 'letra'

    return imprimir(skiplist, anterior, camada - 1, letra);//continua a impressão na camada abaixo
}

//imprime todas as palavras que começam com o caractere letra e retorna a quantidade de palavras impressas
int sklist_imprimir(SKIPLIST * skiplist, char letra){
    if(skiplist == NULL || sklist_vazia(skiplist)){//se a lista for nula ou estiver vazia, não tem verbetes para imprimir
        return 0;
    }
    return imprimir(skiplist, skiplist->sentinela, (skiplist -> camadas) - 1, letra);//chamada de função recursiva da impressão
}