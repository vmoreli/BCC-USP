#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pilha.h"

bool balanceada(char *sequencia){
    PILHA * pilha = pilha_criar();
    ITEM * item;

    for (int i = 0; *(sequencia + i) != '\0'; i++)
    {
        if(*(sequencia + i) == '(' || *(sequencia + i) == '[' || *(sequencia + i) == '{'){
            //Se o elemento da sequência for de abertura, é adicionado a pilha
            item = item_criar(*(sequencia + i));
            if(!pilha_cheia(pilha)) pilha_empilhar(pilha, item);
            else return 0; //Pilha cheia
        } else {
            //Se o elemento da sequência for de fechamento, é desempilhado um elemento da pilha e comparado com ele
            if(!pilha_vazia(pilha)){
                switch(*(sequencia + i)){
                    case ')':
                        if(item_get_chave(pilha_desempilhar(pilha)) != '('){
                            pilha_apagar(&pilha);
                            return 0;
                        } 
                        else break;
                    case ']':
                        if(item_get_chave(pilha_desempilhar(pilha)) != '['){
                            pilha_apagar(&pilha);
                            return 0;
                        }
                        else break;
                    case '}':
                        if(item_get_chave(pilha_desempilhar(pilha)) != '{'){
                            pilha_apagar(&pilha);
                            return 0;
                        }
                        else break;
                }
            } else return 0; //Tentativa de fechar o que ainda não foi aberto (pilha vazia)
        }
    }
    
    if(pilha_vazia(pilha)){
        //Pilha vazia, todos os elementos adicionados foram retirados corretamente, caracterizando uma seq balanceada
        pilha_apagar(&pilha);
        return 1;
    } else {
        //Ainda há elementos na pilha, não foram fechados corretamente na seq
        pilha_apagar(&pilha);
        return 0;
    }

}
