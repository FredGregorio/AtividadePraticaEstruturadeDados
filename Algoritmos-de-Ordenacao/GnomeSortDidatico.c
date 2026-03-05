#include <stdio.h>
#include "sort.h"


//Funções para ensino didático: escreverVetor, stupidSort, e Exemplo1
void escreverVetor(int * vetor, int tamanho, int pos){
    FILE * arquivo = fopen("GnomeSort.txt", "a");
    fprintf(arquivo, "Posição nessa iteração: %d.    Vetor: ", pos);
     for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d ", vetor[i]);
    }
    fprintf(arquivo, "\n"); 
    
    fclose(arquivo);

}

void stupidSort(int * vetor, int tamanho){
    //Declara posição e auxiliar
    int pos = 0, aux;
    //loop que atualiza posição e faz troca se necessário
    while(pos < tamanho){
        escreverVetor(vetor, tamanho, pos);
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
    
}


int main(){
    //Criação do arquivo
    FILE * arquivo = fopen("GnomeSort.txt", "w");
    if (arquivo == NULL){
        printf("\nNão foi possível criar arquivo\n");
        return 1;
    }

    //int vetor[] = {3,7,6,4,8,5,9,2}; //Caso aleatório
    //int vetor[] = {2,3,4,5,6,7,8,9}; //Melhor cenário
    int vetor[] = {9,7,6,5,4,3,2}; //Pior cenário

    int tamanho = sizeof(vetor)/sizeof(int);

    stupidSort(vetor, tamanho);
    fclose(arquivo);
    return 0;
}

