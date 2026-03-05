#include <stdio.h>

void gnomeSort(int *vetor, int tamanho){
    int pos = 0, aux;
    while(pos < tamanho){
        if (pos == 0 || vetor[pos] >= vetor[pos-1]){
            pos++;
        }
        else{
            aux = vetor[pos];
            vetor[pos] = vetor[pos - 1];
            vetor[pos-1] = aux;
            pos--;
        }
    }

    //Printar
}



void insertionSort(int *vetor, int tamanho){
    int pivo, j;
    for (int i = 1; i<tamanho; i++)
    {
        pivo = vetor[i];
        j = i - 1;

        while(j>= 0 && vetor[j] > pivo){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = pivo;
    }
}


void bubbleSort(int *vetor, int tamanho){
    int aux;
    for (int i = 0; i<tamanho;i++){
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if(vetor[j] > vetor[j+1]){
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}

void quickSort(int * vetor, int left, int right){
    
    
    int i, j, pivo, aux;
    i = left;
    j =  right -1;
    pivo = vetor[(left + right)/2];



    while (i <= j) {

        while (vetor[i] < pivo && i<right){
            i++;
        }

        while (vetor[j] > pivo && j > left){
            j--;
        }

        if (i <= j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }
    if (j> left) {
        quickSort(vetor, left, j+1);
    }
    if (i < right - 1){
        quickSort(vetor, i, right);
    }

}


void merge(int * vetor, int left, int h, int right){
    int i, j, k;
    int n1 = h - left + 1;
    int n2 = right - h;

    int L[n1], R[n2];

    for (i = 0; i < n1; i ++) {
        L[i] = vetor[left + i];
    }

    for (j = 0; j< n2; j++){
        R[j] = vetor[h + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;



    while (i< n1 && j < n2) {
        if (L[i] <= R[j]){
            vetor[k] = L[i];
            i++;
        }
        else{
            vetor[k] = R[j];
            j++;
        }
        k++;
    }
    while( i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        vetor[k] = R[j];
        j++;
        k++;
    }

}

void mergeSort(int * vetor, int left, int right){
    if (left < right) {
        int h = left + (right - left) /2 ;
        mergeSort(vetor, left, h);
        mergeSort(vetor,  h+1, right);
        merge(vetor, left, h, right);
    }
}


