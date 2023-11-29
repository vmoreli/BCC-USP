#include "item.h"
#include "ab.h"

int ab_soma(NO * no){

    if(no == NULL)
        return 0;

    return(item_get_chave(no -> item) + ab_soma(no -> esq) + ab_soma(no -> dir));
}

int soma(AB * T){

    if(T != NULL){
        return ab_soma(T -> raiz);
    }

}