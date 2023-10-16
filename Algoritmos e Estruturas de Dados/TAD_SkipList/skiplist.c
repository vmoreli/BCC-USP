#include "skiplist.h"
#include <string.h>

typedef struct no_ NO;

struct no_{
    int camada; //numero de camadas que o no está presente
    VERBETE * verbete; //item armazenado
    NO ** proxs; //vetor de ponteiros para os proximos nós de cada camada
};

struct skiplist_{
    int camadas;
    NO * cabeca;
};

NO * novo_no(char * palavra, char * definicao, int camada){
    VERBETE * verbete = verbete_criar(palavra, definicao);
    NO * no = (NO *) malloc(sizeof(NO));
    
    if(no != NULL){
        no -> camada = camada;
        no -> verbete = verbete;
        no -> proxs = (NO **) malloc(sizeof(NO*) * camada);

        if(no -> proxs != NULL)
            for (int i = 0; i < camada; i++)
                no -> proxs[i] = NULL;
    } else {
        verbete_apagar(&verbete);
    }

    return no;
}

void apagar_no(NO ** no){
    if(no == NULL)
        return;

    free((*no) -> proxs);
    free(*no);
    *no = NULL;
}

int nivel_aleatorio(SKIPLIST * skiplist){
    int t = rand(), //numero aleatorio entre 0 e RAND_MAX
        i = 1,
        j = 2; //j = 2^{i+1}
    while(i < CAMADASMAX && t <= RAND_MAX/j){
        j *= 2;
        i ++;
    }

    if(i > skiplist -> camadas)
        skiplist -> camadas = i;

    return i;
}



SKIPLIST * sklist_criar(void){
    SKIPLIST * skiplist = (SKIPLIST *) malloc(sizeof(SKIPLIST));
    if(skiplist != NULL){
        skiplist -> camadas = 0;
        skiplist->cabeca = novo_no(NULL, NULL, CAMADASMAX);
        for (int i = 0; i < CAMADASMAX; i++)
            skiplist->cabeca->proxs[i] = skiplist->cabeca;
           
    }
    return skiplist;
}

VERBETE * busca_camada(NO * no, char * palavra, int camada, NO * cabeca){
    int compara = strcmp(palavra, verbete_get_palavra(no->proxs[camada]->verbete));
    
    if(compara == 0){
    // se o nó achado for o nó cabeça, então o nó não foi encontrado na camada atual
        if(no->proxs[camada] != cabeca)
            return no -> proxs[camada] -> verbete; // nó encontrado
        else
            if(camada != 0)
                return busca_camada(no, palavra, camada - 1, cabeca);
            else
                return NULL;
    }

    if(compara < 0){
        if(camada != 0) return busca_camada(no, palavra, camada - 1, cabeca);
        else return NULL;
    }

    return busca_camada(no->proxs[camada], palavra, camada, cabeca);
}

VERBETE * sklist_busca(SKIPLIST * skiplist, char * palavra){
    if(sklist_vazia(skiplist))
        return NULL;

    verbete_set_palavra(skiplist->cabeca->verbete, palavra);
    VERBETE * aux = busca_camada(skiplist -> cabeca, palavra, (skiplist -> camadas) - 1, skiplist -> cabeca);
    verbete_set_palavra(skiplist->cabeca->verbete, NULL);

    return aux;
}

bool insere_camada(SKIPLIST * skiplist, NO * cabeca, NO * no, int camada){
    int compara = strcmp(verbete_get_palavra(no -> verbete), verbete_get_palavra(cabeca -> proxs[camada] -> verbete));

    if(compara <= 0){
        if(camada < no -> camada){
            no -> proxs[camada] = cabeca -> proxs[camada];
            cabeca -> proxs[camada] = no;
            if(camada == 0)
                return true;
        }

        
        return insere_camada(skiplist, cabeca, no, camada - 1);
        
    }
    else
        return insere_camada(skiplist, cabeca -> proxs[camada], no, camada);

}

bool sklist_insere(SKIPLIST * skiplist, char * palavra, char * definicao){
    if(skiplist != NULL && !sklist_cheia(skiplist) && sklist_busca(skiplist, palavra) == NULL){
        NO * no = novo_no(palavra, definicao, nivel_aleatorio(skiplist)); 
        verbete_set_palavra(skiplist -> cabeca -> verbete, palavra);
        bool inseriu = insere_camada(skiplist, skiplist->cabeca, no, (skiplist -> camadas) - 1);
        verbete_set_palavra(skiplist->cabeca->verbete, NULL);
        return inseriu;
    }
    return false;
}

VERBETE * remove_camada(SKIPLIST * skiplist, NO * anterior, char * palavra, int camada){
    int compara = strcmp(palavra, verbete_get_palavra(anterior -> proxs[camada] -> verbete));

    if(compara == 0){
    // se o nó achado for o nó cabeça, então o nó não foi encontrado na camada atual
        if(anterior -> proxs[camada] != skiplist->cabeca){
            // nó encontrado
            NO * atual = anterior->proxs[camada];
            anterior -> proxs[camada] = atual -> proxs[camada];

            if((anterior == skiplist -> cabeca) && (atual -> proxs[camada] == skiplist -> cabeca)){ // nó a ser removido é o unico presente na camada
                if(skiplist -> camadas != 0) skiplist -> camadas--;
            }

            if(camada == 0){
                VERBETE * tmp = atual -> verbete;
                apagar_no(&atual);
                return tmp;
            }
            return remove_camada(skiplist, anterior, palavra, camada - 1);
        }
    }
    if(compara <= 0){ // nó não encontrado na camada (se camada == 0, então o nó não esta presente na lista)
        if(camada == 0)
            return NULL;
        return remove_camada(skiplist, anterior, palavra, camada - 1);
    }
    return remove_camada(skiplist, anterior-> proxs[camada], palavra, camada);
}

VERBETE * sklist_remover(SKIPLIST * skiplist, char * palavra){
    if(skiplist != NULL && !sklist_vazia(skiplist)){
        verbete_set_palavra(skiplist -> cabeca -> verbete, palavra);
        VERBETE * aux = remove_camada(skiplist, skiplist->cabeca, palavra, (skiplist -> camadas) - 1);
        verbete_set_palavra(skiplist->cabeca->verbete, NULL);
        return aux;
    }
    return NULL;
}

void sklist_apagar(SKIPLIST **skiplist){
    if(*skiplist == NULL)
        return;
    
    NO * cabeca = (*skiplist)->cabeca, * aux;
    while (cabeca->proxs[0] != cabeca){
        aux = cabeca->proxs[0];
        cabeca->proxs[0] = aux->proxs[0];
        verbete_apagar(&(aux->verbete));
        apagar_no(&aux);
    }

    verbete_apagar(&(cabeca->verbete));
    apagar_no(&cabeca);
    free((*skiplist));
    *skiplist = NULL;
}

bool sklist_vazia(SKIPLIST * skiplist){
    return (skiplist -> cabeca -> proxs[0] == skiplist -> cabeca? true : false);
}

bool sklist_cheia(SKIPLIST * skiplist){
    NO * no = novo_no(NULL, NULL, CAMADASMAX);
    if(no != NULL){
        verbete_apagar(&no->verbete);
        apagar_no(&no);
        return false;
    }
    return true;
}

int imprimir(SKIPLIST * skiplist, NO * anterior, int camada, char letra){
    if(anterior -> proxs[camada] != skiplist -> cabeca){ //chegou ao final da camada atual

        char inicial_palavra = verbete_get_palavra(anterior->proxs[camada]->verbete)[0];
        

        if(inicial_palavra == letra){
            /*imprime apenas se estiver na camada mais inferior para garantir que 
            não irá pular nenhuma palavra que comece com o caractere letra*/
            if(camada == 0){
                verbete_imprimir(anterior->proxs[camada]->verbete);
                printf("\n");
                return 1 + imprimir(skiplist, anterior->proxs[camada], camada, letra);
                }

                return imprimir(skiplist, anterior, camada - 1, letra);
        }
        if(inicial_palavra < letra)
            return imprimir(skiplist, anterior->proxs[camada], camada, letra);
        
    }
    if(camada == 0) return 0;//chegou ao fim da lista

    return imprimir(skiplist, anterior, camada - 1, letra);
}

//imprime todas as palavras que começam com o caractere letra e retorna a quantidade de palavras impressas no terminal
void sklist_imprimir(SKIPLIST * skiplist, char letra){
    if(skiplist == NULL || sklist_vazia(skiplist)){
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", letra);
        return;
    }

    //transformando o caractere letra para lower case caso já não esteja

    if(imprimir(skiplist, skiplist->cabeca, (skiplist -> camadas) - 1, letra) == 0)
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", letra);
}