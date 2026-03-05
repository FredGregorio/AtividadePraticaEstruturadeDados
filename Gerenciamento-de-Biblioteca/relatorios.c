#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "auxiliar.h"
#include "relatorios.h"

void listarLivrosPorGenero() {
    Livro *livros = NULL;
    int total_livros = 0;
    carregarLivros(&livros, &total_livros);

    if (total_livros == 0) {
        printf("\nNenhum livro cadastrado para gerar relatório.\n");
        return;
    }

    printf("\n--- Relatório: Listar Livros por Gênero ---\n");
    enum GENERO genero_busca;
    receberGenero(&genero_busca); // Reutiliza a função de receber gênero

    printf("\nExibindo livros do gênero '%s':\n", generoParaTexto(genero_busca));
    
    int encontrados = 0;
    for (int i = 0; i < total_livros; i++) {
        if (livros[i].genero == genero_busca) {
            printf("----------------------------------------\n");
            exibirLivro(livros[i]); // Reutiliza a função de exibir livro
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum livro encontrado para este gênero.\n");
    } else {
        printf("----------------------------------------\n");
        printf("Total de livros encontrados: %d\n", encontrados);
    }

    free(livros); // Libera a memória alocada
}

void listarLivrosPorStatus() {
    // Este relatório irá mostrar todos os livros e seu status de disponibilidade (Disponível ou Emprestado)
    Livro *livros = NULL;
    int total_livros = 0;
    carregarLivros(&livros, &total_livros);

    if (total_livros == 0) {
        printf("\nNenhum livro cadastrado para gerar relatório.\n");
        return;
    }

    Emprestimos *emprestimos = NULL;
    int total_emprestimos = 0;
    carregarEmprestimos(&emprestimos, &total_emprestimos);

    printf("\n--- Relatório: Status de Disponibilidade dos Livros ---\n");

    // Para cada livro, vamos verificar se ele está em algum empréstimo ativo
    for (int i = 0; i < total_livros; i++) {
        int emprestado = 0; // Começamos assumindo que o livro está disponível
        for (int j = 0; j < total_emprestimos; j++) {
            // Se o ISBN do livro for igual ao ISBN de um empréstimo E o status do empréstimo for "ANDAMENTO"
            if (strcmp(livros[i].ISBN, emprestimos[j].ISBN) == 0 && emprestimos[j].status == ANDAMENTO) {
                emprestado = 1; // Marca como emprestado
                break; // Não precisa procurar mais, já achamos um empréstimo ativo para este livro
            }
        }
        
        printf("Título: %-30s | ISBN: %-15s | Status: %s\n", 
               livros[i].titulo, 
               livros[i].ISBN, 
               emprestado ? "Emprestado" : "Disponível");
    }

    // Libera a memória alocada para os dois vetores
    free(livros);
    if (emprestimos != NULL) {
        free(emprestimos);
    }
}

void MenuRelatorios() {
    int op;
    do {
        printf("\n--- Módulo de Relatórios ---\n");
        printf("Escolha a opção que você quer acessar:\n");
        printf("1. Listar Livros por Gênero\n");
        printf("2. Listar Disponibilidade dos Livros\n");
        printf("0. Voltar\n");
        printf("Opção: ");
        scanf("%d", &op);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (op) {
            case 1:
                listarLivrosPorGenero();
                break;
            case 2:
                listarLivrosPorStatus();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }
    } while (op != 0);
}