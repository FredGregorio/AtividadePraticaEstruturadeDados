// ------Funções de mcriações de arquivos/carregamento de dados e verificação de existência/Buscas nos arquivos-------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

// cria um arquivo com cabeçalhos se ele não existir
/*void criarArquivos(const char *caminho, const char *colunas) {
    FILE *arquivo =fopen(caminho, "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "%s", colunas); 
            fclose(arquivo);
        } else {
            printf("Erro ao criar o arquivo: %s\n", caminho);
        }
        fclose(arquivo);
}*/

int ler_entrada_limitada(char *buffer, size_t tamanho_max) {
    if (fgets(buffer, tamanho_max, stdin) == NULL) {
        return 0; // Erro ou EOF
    }
    
    size_t len = strlen(buffer);
    
    // Se a entrada for muito longa (sem \n no final)
    if (len == tamanho_max - 1 && buffer[len - 1] != '\n') {
        // Limpar o buffer de entrada
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    
    // Remover \n se existir
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    return 1;
}

int gerarNovoId(const char *arquivoPath) {
    FILE *arquivo = fopen(arquivoPath, "r");
    if (!arquivo) {
        return 1; // Primeiro ID se arquivo não existir
    }
    
    int maxId = 0;
    char linha[256];
    int primeiraLinha = 1;
    int idsValidos = 0;
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        //ignorar cabeçalho
        if (primeiraLinha) {
            primeiraLinha = 0;
            continue;
        }
    
        //extrair ID
        int id;
        if (sscanf(linha, "%d,", &id) == 1) {
            //filtrar IDs inválidos
            if (id > 0 && id < 1000000000) {
                if (id > maxId) maxId = id;
                idsValidos++;
            }
        }
    }
    fclose(arquivo);
    return (idsValidos == 0) ? 1 : maxId + 1;
}



//Carregar arquivos
void carregarLivros(Livro ** livros, int * total){
    FILE *arquivo = fopen("arquivos/livros.txt", "r");
    * total = 0;
    if (!arquivo) {
        
        *livros = NULL;
        return;
    }

    //pular cabeçalho (primeira linha)
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);

    Livro temp;
    int genero_tmp;

    //ler cada linha do arquivo
    while (fscanf(arquivo, "%d,%13[^,], %199[^,],%199[^,],%d\n", 
                &temp.id,
                temp.ISBN,
                temp.titulo, 
                temp.autor, 
                &genero_tmp) == 5) {

        //converter genero
        temp.genero = (enum GENERO)genero_tmp;

        //alocar espaço para mais um médico e adicionar
        *livros = realloc(*livros, (*total + 1) * sizeof(Livro));
        (*livros)[*total] = temp;
        (*total)++;
    }
    fclose(arquivo);
}


//Busca ISBN em livros e retorna id
int buscarLivroPorISBN(Livro * livros, int total, const char * isbnBusca){
    for(int i = 0; i < total; i++) {
        if(strcmp(livros[i].ISBN, isbnBusca) == 0) {
            return i;
            break;
        }
    }
    return -1;
}

// FUN ADICIONADA HOJE (28/06/2025)

void carregarEmprestimos(Emprestimos **emprestimos, int *total) {
    FILE *arquivo = fopen("arquivos/emprestimos.txt", "r");
    *total = 0;
    if (!arquivo) {
        *emprestimos = NULL;
        return; // Arquivo ainda não existe, não há o que carregar.
    }

    // Pular cabeçalho 
    char buffer[512];
    fgets(buffer, sizeof(buffer), arquivo);

    Emprestimos temp;
    int status_temp;

    // Ler cada linha do arquivo
    while (fscanf(arquivo, "%u,%199[^,],%13[^,],%d,%d,%d,%d\n", 
                  &temp.id,
                  temp.leitor,
                  temp.ISBN,
                  &temp.DataDoEmprestimo.dia,
                  &temp.DataDoEmprestimo.mes,
                  &temp.DataDoEmprestimo.ano,
                  &status_temp) == 7) {
        
        // Atribuir o status convertido à struct temporária
        temp.status = (enum STATUS)status_temp;

        // Alocar/Realocar memória para o vetor
        *emprestimos = realloc(*emprestimos, (*total + 1) * sizeof(Emprestimos));
        (*emprestimos)[*total] = temp;
        (*total)++;
    }
    fclose(arquivo);
}      
