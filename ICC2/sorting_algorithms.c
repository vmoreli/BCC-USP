#include <stdio.h>
#include <stdlib.h>

// troca a e b de "lugar"
void swap(int * a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

//Ordena um array de inteiros entre o item i-esimo e n-esimo
int bubble_sort(int * lista, int inicial, int final){
    int swapped = 1;
    int aux = final, iteracoes = 0;
    while (swapped == 1){
        swapped = 0;
        for (int i = inicial; i < aux; i++){
            iteracoes ++;
            if(lista[i] > lista[i+1]){
                swap(&lista[i], &lista[i+1]);
                swapped = 1;
            }
        }
        aux -= 1;
    }
    return iteracoes;
}

//Ordena um array de inteiros entre o item i-esimo e n-esimo
void quick_sort(int * lista, int inicio, int fim){
    if(fim <= inicio)
        return;

    int pivo = lista[(inicio + fim)/2], i, j;

    // movendo o pivo para o final da lista.
    swap(&lista[(inicio + fim)/2], &lista[fim]);

    // particionamento do array (metodo de Lomuto).
    for (i = inicio, j = inicio; i < fim; i++){
        if(lista[i] < pivo)
            swap(&lista[i], &lista[j++]);
    }
    swap(&lista[j], &lista[fim]); // j = posicao correta do elemento pivo.

    //recursão
    quick_sort(lista, inicio, j - 1);
    quick_sort(lista, j + 1, fim);
    
}

void ordenacao_por_insercao(int * v, int n){
    int i, j, x;
    for (i = 1; i < n; i++){
        x = v[i];
        j = i-1;
        while(j >= 0 && x < v[j]){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
    }   
}

void shell_sort(int * v, int n){
    int i, j, x, h;

    h = 1;
    while(h < n)
        h = 3*h + 1;
    
    while(h > 0){
        for(i = h; i < n; i++){
            x = v[i]; 
            j = i;
            while(j > h - 1 && x < v[j - h]){
                v[j] = v[j - h];
                j -= h;
            }
            v[j] = x;
        }
        h /= 3;
    }
}

void selecao_direta(int * lista, int n){
    int indice_menor;
    for (int i = 0; i < n - 1; i++){
        indice_menor = i;
        for (int j = i + 1; j < n; j++){
            if(lista[j] < lista[indice_menor])
                indice_menor = j;
        }
        swap(&lista[i], &lista[indice_menor]);
    }
}

void rearranjar_heap(int * heap, int i, int n){
    int esq, dir, maior;
    esq = 2*i + 1;
    dir = 2*i + 2;

    maior = i;
    if(esq < n)
        if(heap[esq] > heap[i])
            maior = esq;

    if(dir < n)
        if(heap[dir] > heap[maior])
            maior = dir;

    if(maior != i){
        swap(&heap[maior], &heap[i]);
        rearranjar_heap(heap, maior, n);
    }
}

void montar_heap(int * heap, int n){
    for (int i = n/2 - 1; i >= 0; i--){
        rearranjar_heap(heap, i, n);
    }
    
}

void heap_sort(int * lista, int n){
    montar_heap(lista, n);

    for (int i = n-1; i > 0; i--){
        swap(&lista[0], &lista[i]);
        rearranjar_heap(lista, 0, i);
    }
    
}

void ordenacao_por_contagem_de_menores(int * v, int n){
    int menores[n], B[n], i, j;
    for (i = 0; i < n; i++)
        menores[i] = 0;
    
    for (i = 0; i < n; i++){
        for (j = i - 1; j >= 0; j--){
            if(v[j] < v[i])
                menores[i] ++;
            else
                menores[j]++;
        }
    }

    for (i = 0; i < n; i++){
        B[menores[i]] = v[i];
    }

    for(i = 0; i < n; i++)
        v[i] = B[i];
}

void ordenacao_por_contagem_de_tipos(int * v, int n){
    int i, j, max;

    max = v[0];
    for(i = 1; i < n; i++){
        if(v[i] > max)
            max = v[i];
    }
    int X[max + 1];

    for (i = 0; i < max+1; i++)
        X[i] = 0;

    for (i = 0; i < max + 1; i++)
        X[v[i]]++;
    
    j = 0;
    for (i = 0; i < max + 1; i++){
        while(X[i] != 0){
            v[j] = i;
            j++;
            X[i]--;
        }
    }  
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

int main(void){
    int * lista, n = 0;
    
    scanf(" %d", &n);
    lista = (int *) malloc(sizeof(int)* n);
    for (int i = 0; i < n; i++){
        scanf(" %d", &lista[i]);
    }

    shell_sort(lista, n);
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", lista[i]);
    }
    printf("\n\n");

}