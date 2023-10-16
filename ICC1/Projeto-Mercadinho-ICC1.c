/******************************************************************************
 *     O objetivo deste programa é simular um sistema de estoque de um mercado,
 * com comandos para inserir um novo produto no estoque, aumentar o estoque de 
 * um produto já existente, modificar o preço de um produto,realizar uma venda,
 * consultar o estoque dos produtos e consultar o saldo do caixa.
 *     Cada item do estoque possui um codigo na forma de um número inteiro que
 * será atribuído sequencialmente a cada produto inserido.
 * 
 * Autores: Giordano Santorum Lorenzeto e Victor Moreli dos Santos (2023)
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Struct produto que representa um produto do mercado com três informações: um nome, uma quantidade e um preço.
Definição do tipo Produto baseado nessa struct.
*/
struct PRODUTO {
    char *nome;
    int quantidade;
    double preco;
};
typedef struct PRODUTO Produto;

/*
Struct que representa um mercado, guarda um vetor de produtos (tipo definido acima), o número de produtos e o saldo.
Definição do tipo Mercado baseado nessa struct.
*/
struct MERCADO {
    Produto *estoque;
    int num_produtos;
    double saldo;    
};
typedef struct MERCADO Mercado;

/*
Função que inicia o dia no mercado, checando se existe um arquivo com o nome fornecido, atualizando as informações 
do estoque e saldo se existir. Se não existir, o estoque e o saldo são lidos na entrada padrão.
Parâmetros de entrada: fnome - nome do arquivo onde serão guardadas as informações.
Parâmetros de saída: mercadinho - estrutura que contém o vetor de Produtos a ser alterado.
*/
Mercado iniciar(char *fnome);

/*
Função que lê o comando inserido pelo usuario e chama as funções correspondentes:
    - IP = inserir_produto(), AE = aumentar_estoque(), MP = modificar_preco(), VE = vender(),
      CE = consultar_estoque(), CS = consultar_saldo(), FE = retorna para a main().
Parametro de entrada: Comando inserido pelo usuário no terminal,
                      mercadinho - estrutura que será passada como parâmetro para as outras funções.
*/
void ler_comando(Mercado *mercadinho);

/*
Função que insere um produto no estoque de uma struct MERCADO.
Parametros de entrada:  nome, quantidade e preço, inseridos pelo usuário no terminal na forma:"<nome> <quantidade> <preço>".
Parametros de saída: mercadinho - estrutura que contém o vetor de Produtos a ser alterado.
*/
void inserir_produto(Mercado *mercadinho);

/*
Função que aumenta a quantidade de um produto no estoque de uma struct MERCADO.
Parametros de entrada:  código do produto e a quantidade a adicionar no estoque, inseridos pelo usuário no terminal 
                        na forma:"<codigo> <quantidade>".
Parametros de saída: mercadinho - estrutura que contém o vetor com o Produto a ser alterado.
*/
void aumentar_estoque(Mercado *mercadinho);

/*
Função que altera o preço de um produto no estoque de uma struct MERCADO.
Parametros de entrada:  código do produto e o novo preço inseridos pelo usuário no terminal
                        na forma:"<codigo> <quantidade>".
Parametros de saída: mercadinho - estrutura que contém o vetor com o Produto a ser alterado.
*/
void modificar_preco(Mercado *mercadinho);

/*
Função que realiza a venda de uma lista de produtos de uma struct MERCADO.
Parametros de entrada:  códigos dos produtos e -1 (fim da lista), inseridos pelo usuário no terminal
                        na forma:"<codigo> <codigo> <codigo> ... <-1>".
Parametros de saída: Lista dos produtos vendidos e preço total da venda apresentados no terminal.
                     mercadinho - estrutura que terá o estoque e saldo alterados.

*/
void vender(Mercado *mercadinho);

/*
Função que lista código, nome e quantidade no estoque de todos os produtos do no estoque de uma struct MERCADO.
Parametros de entrada: mercadinho - estrutura que contém a lista de produtos.
Parametros de saída: Lista dos codigos, nomes e quantidades dos produtos do mercado apresentados no terminal.
*/
void consultar_estoque(Mercado mercadinho);

/*
Função que escreve o saldo de uma struct MERCADO no terminal.
Parametros de entrada: mercadinho - estrutura a ter o saldo consultado. 
Parametros de saída: Saldo do mercado apresentado no terminal.
*/
void consultar_saldo(Mercado mercadinho);

/*
Função que encerra a execução do código, salvando as informações do estoque, saldo e todos os produtos em um arquivo.
Parametros de entrada: mercadinho - estrutura que contém a lista de produtos, e fnome - nome do arquivo
                        onde serão guardadas as informações.
*/
void finalizar(Mercado mercadinho, char * fnome);


/*
Função que aloca dinamicamente uma string e faz a sua leitura. É utilizada para ler o nome do produto a ser inserido
no mercadinho.
*/
char * reads();

char * reads(){
    char * str = (char *) malloc(10 * sizeof(char)), //string que será lida
         aux;
    int tam = 0; //tamanho da string
    aux = getchar();
    while (aux != ' ')
    {
        if(tam > 8)
            str = (char *) realloc(str, (tam + 2)*sizeof(char));
        str[tam] = aux;
        tam++;
        aux = getchar();
    }
    if(tam == 0){
        free(str);
        return reads();
    }
    str[tam] = '\0';
    return str;
}

Mercado iniciar(char *fnome){
    FILE *fp;
    Mercado mercadinho;
    if((fp = fopen(fnome, "rb")) == NULL){
        scanf(" %d %lf", &mercadinho.num_produtos, &mercadinho.saldo);
        mercadinho.num_produtos = 0;
    }else{
        int aux; // variável auxiliar para alocação dinâmica do nome dos produtos
        fscanf(fp, " %d %lf", &mercadinho.num_produtos, &mercadinho.saldo);
        mercadinho.estoque = (Produto *) malloc(mercadinho.num_produtos*sizeof(Produto));
        for (int i = 0; i < mercadinho.num_produtos; i++)
        {
            fscanf(fp, " %d", &aux);
            mercadinho.estoque[i].nome = (char *) malloc((aux + 1) * sizeof(char));
            fscanf(fp, " %s %d %lf", mercadinho.estoque[i].nome, &mercadinho.estoque[i].quantidade, &mercadinho.estoque[i].preco);
        }
        fclose(fp);
    }


    return mercadinho;

}

void ler_comando(Mercado *mercadinho){
    char comando[3];
    scanf(" %s", comando);
    if(!strcmp(comando, "IP"))
        inserir_produto(mercadinho);
    else if(!strcmp(comando, "AE"))
        aumentar_estoque(mercadinho);
    else if(!strcmp(comando, "MP"))
        modificar_preco(mercadinho);
    else if(!strcmp(comando, "VE"))
        vender(mercadinho);
    else if(!strcmp(comando, "CE"))
        consultar_estoque(*mercadinho);
    else if(!strcmp(comando, "CS"))
        consultar_saldo(*mercadinho);
    else if(!strcmp(comando, "FE"))
        return;

    ler_comando(mercadinho); // recursão
}

void inserir_produto(Mercado *mercadinho){
    Produto aux;
    aux.nome = reads();
    scanf(" %d %lf", &aux.quantidade, & aux.preco);
    if(mercadinho -> num_produtos == 0)
        mercadinho -> estoque = (Produto *) malloc((++mercadinho -> num_produtos)*sizeof(Produto));
    else 
        mercadinho -> estoque = (Produto *) realloc(mercadinho -> estoque, (++mercadinho -> num_produtos)*sizeof(Produto));
    mercadinho -> estoque[mercadinho -> num_produtos - 1] = aux;
}

void aumentar_estoque(Mercado *mercadinho){
    int codigo, acrescimo;
    scanf(" %d %d", &codigo, &acrescimo);

    mercadinho -> estoque[codigo].quantidade += acrescimo;
}

void modificar_preco(Mercado * mercadinho){
    int codigo;
    double novo_preco;

    scanf(" %d %lf", &codigo, &novo_preco);

    mercadinho -> estoque[codigo].preco = novo_preco;
}

void vender(Mercado * mercadinho){
    int codigo;
    Produto aux;
    double preco_total = 0;

    scanf(" %d", &codigo);

    while(codigo != -1){
        aux = mercadinho -> estoque[codigo];

        if(aux.quantidade > 0){
            aux.quantidade--;
            mercadinho -> saldo += aux.preco;
            preco_total += aux.preco;

            mercadinho -> estoque[codigo] = aux;

            printf("%s %.2lf\n", aux.nome, aux.preco);
        } 

        scanf(" %d", &codigo);
    }

    printf("Total: %.2lf\n", preco_total);
    printf("--------------------------------------------------\n");
}

void consultar_estoque(Mercado mercadinho){
    for (int i = 0; i < mercadinho.num_produtos; i++)
    {
        printf("%d %s %d\n", i, mercadinho.estoque[i].nome, mercadinho.estoque[i].quantidade);
    }
    printf("--------------------------------------------------\n");
}

void consultar_saldo(Mercado mercadinho){
    printf("Saldo: %.2lf\n", mercadinho.saldo);
    printf("--------------------------------------------------\n");
}

void finalizar(Mercado mercadinho, char * fnome){
    FILE * fp;

    if((fp = fopen(fnome, "wb")) == NULL){
        exit(1);
    }

    fprintf(fp, "%d\n%lf\n", mercadinho.num_produtos, mercadinho.saldo);

    for (int i = 0; i < mercadinho.num_produtos; i++)
    {
        fprintf(fp, "%d %s %d %lf\n", (int) strlen(mercadinho.estoque[i].nome), mercadinho.estoque[i].nome, mercadinho.estoque[i].quantidade, mercadinho.estoque[i].preco);
        free(mercadinho.estoque[i].nome);
    }
    free(mercadinho.estoque);
    fclose(fp);

}

int main(int argc, char **argv){
    if(argc != 2){
        exit(1);
    }
    Mercado mercadinho = iniciar(argv[1]);
    ler_comando(&mercadinho);
    finalizar(mercadinho, argv[1]);

    return 0;
}