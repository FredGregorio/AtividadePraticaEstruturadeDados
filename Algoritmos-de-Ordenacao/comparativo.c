#include <stdio.h>
#include <time.h>
#include "sort.h"
#include <stdlib.h>


void preencherVetor(int * vetor, int tamanho) {
    for(int i = 0; i < tamanho; i++){
        vetor[i] = rand() % 1000;
    }
}

void copiarVetor(int *origem, int * destino, int tamanho){
    for (int i = 0; i< tamanho; i++){
        destino[i] = origem[i];
    }
}

void imprimirVetor(int * vetor, int tamanho) {
    for (int i = 0; i< tamanho; i++) {
        printf("%d", vetor[i]);
    }
    printf("\n");
}

int main(){
    clock_t inicio, fim;
    double tempo_gasto;

    int tamanho = 50000;

    int * vetor_original = (int *) malloc(tamanho * sizeof(int));
        int * vetor = (int *)malloc(tamanho*sizeof(int));

        if(vetor_original == NULL || vetor == NULL) {
            printf("Erro ao alocar memória!\n");
            return 1;
        }

        preencherVetor(vetor_original, tamanho);
        

        


        //Gnome Sort
        copiarVetor(vetor_original, vetor, tamanho);
        inicio = clock();
        gnomeSort(vetor, tamanho);
        fim = clock();
        tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        printf("Gnome Sort: %f segundos\n", tempo_gasto);

        //Quick sort
        copiarVetor(vetor_original, vetor, tamanho);
        inicio = clock();
        quickSort(vetor, 0, tamanho);
        fim = clock();
        tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        printf("Quick sort: %f segundos\n", tempo_gasto);


        //Merge sort
        copiarVetor(vetor_original, vetor, tamanho);
        inicio = clock();
        mergeSort(vetor, 0, tamanho-1);
        fim = clock();
        tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        printf("Merge sort: %f segundos\n", tempo_gasto);
  
        //Insertion Sort
        copiarVetor(vetor_original, vetor, tamanho);
        inicio = clock();
        insertionSort(vetor, tamanho);
        fim = clock();
        tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        printf("Insertion sort: %f segundos\n", tempo_gasto);

         // Buble sort
        copiarVetor(vetor_original, vetor, tamanho);
        inicio = clock();
        bubbleSort(vetor, tamanho);
        fim = clock();
        tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
        printf("Buble sort: %f segundos\n", tempo_gasto);


        free(vetor);
        free(vetor_original);
    


    return 0;
}

