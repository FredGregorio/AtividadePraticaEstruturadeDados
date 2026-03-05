#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "tipos.h"
#include "auxiliar.h"
#include "emprestimos.h"

// --- Funções Auxiliares (locais a este arquivo) ---

// Salva todos os empréstimos no arquivo (sobrescrevendo)
void salvarTodosEmprestimos(Emprestimos *emprestimos, int total) {
    FILE *arquivo = fopen("arquivos/emprestimos.txt", "w");
    if (!arquivo) {
        printf("Erro fatal ao abrir arquivo de empréstimos!\n");
        return;
    }
    // Cabeçalho
    fprintf(arquivo, "id,leitor,isbn,dia,mes,ano,status\n");

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%u,%s,%s,%d,%d,%d,%d\n",
                emprestimos[i].id,
                emprestimos[i].leitor,
                emprestimos[i].ISBN,
                emprestimos[i].DataDoEmprestimo.dia,
                emprestimos[i].DataDoEmprestimo.mes,
                emprestimos[i].DataDoEmprestimo.ano,
                emprestimos[i].status);
    }
    fclose(arquivo);
}

// Salva um único novo empréstimo no final do arquivo
void salvarNovoEmprestimo(Emprestimos *emprestimo) {
    FILE *arquivo = fopen("arquivos/emprestimos.txt", "a");
    if (arquivo == NULL) {
        // Se o arquivo não existir, cria um novo com cabeçalho
        arquivo = fopen("arquivos/emprestimos.txt", "w");
        if(arquivo == NULL){
            printf("Erro fatal: não foi possível criar o arquivo de empréstimos!\n");
            return;
        }
        fprintf(arquivo, "id,leitor,isbn,dia,mes,ano,status\n");
        fclose(arquivo);
        arquivo = fopen("arquivos/emprestimos.txt", "a");
    }
    
    fprintf(arquivo, "%u,%s,%s,%d,%d,%d,%d\n",
            emprestimo->id,
            emprestimo->leitor,
            emprestimo->ISBN,
            emprestimo->DataDoEmprestimo.dia,
            emprestimo->DataDoEmprestimo.mes,
            emprestimo->DataDoEmprestimo.ano,
            emprestimo->status);
    
    fclose(arquivo);
}

// Verifica se um livro já possui um empréstimo em andamento
int livroJaEmprestado(const char* isbn) {
    Emprestimos *emprestimos = NULL;
    int total = 0;
    carregarEmprestimos(&emprestimos, &total);

    for (int i = 0; i < total; i++) {
        if (strcmp(emprestimos[i].ISBN, isbn) == 0 && emprestimos[i].status == ANDAMENTO) {
            free(emprestimos);
            return 1; // Encontrou um empréstimo em andamento para este ISBN
        }
    }
    if (emprestimos != NULL) {
        free(emprestimos);
    }
    return 0; // Não encontrou
}


// --- Funções do Menu ---

void cadastrarEmprestimo() {
    Emprestimos *novo_emprestimo = (Emprestimos*)malloc(sizeof(Emprestimos));
    if (!novo_emprestimo) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    Livro *livros = NULL;
    int total_livros = 0;
    carregarLivros(&livros, &total_livros);

    if (total_livros == 0) {
        printf("\nNenhum livro cadastrado no sistema. Impossível realizar empréstimo.\n");
        free(novo_emprestimo);
        return;
    }

    char isbn_busca[15]; // Aumentado para segurança
    int livro_idx;

    // PASSO 1: PEGAR O ISBN
    while (1) {
        printf("\nDigite o ISBN do livro a ser emprestado (ou digite '0' para voltar): ");
        ler_entrada_limitada(isbn_busca, 15);

        if (strcmp(isbn_busca, "0") == 0) {
            printf("\nOperação cancelada.\n");
            free(livros);
            free(novo_emprestimo);
            return; // Volta para o menu de empréstimos
        }

        if(!validarISBN(isbn_busca)){
            printf("Erro: Formato de ISBN inválido. Deve conter 13 números.\n");
            continue;
        }

        livro_idx = buscarLivroPorISBN(livros, total_livros, isbn_busca);

        if (livro_idx == -1) {
            printf("Erro: Livro com este ISBN não encontrado.\n");
            continue;
        }
        if (livroJaEmprestado(isbn_busca)) {
            printf("Erro: Este livro já possui um empréstimo em andamento.\n");
            continue;
        }
        
        printf("Livro encontrado: %s\n", livros[livro_idx].titulo);
        strcpy(novo_emprestimo->ISBN, isbn_busca);
        break; // Sai do loop se tudo estiver ok
    }
    
    // PASSO 2: PEGAR NOME E DATA
    printf("\nDigite o nome do leitor: ");
    receberNome(novo_emprestimo->leitor);

    printf("\nDigite a data do empréstimo.\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    int data_valida = 0;
    while (!data_valida) {
        receberData(&novo_emprestimo->DataDoEmprestimo);
        if (novo_emprestimo->DataDoEmprestimo.ano < tm.tm_year + 1900 ||
           (novo_emprestimo->DataDoEmprestimo.ano == tm.tm_year + 1900 && novo_emprestimo->DataDoEmprestimo.mes < tm.tm_mon + 1) ||
           (novo_emprestimo->DataDoEmprestimo.ano == tm.tm_year + 1900 && novo_emprestimo->DataDoEmprestimo.mes == tm.tm_mon + 1 && novo_emprestimo->DataDoEmprestimo.dia < tm.tm_mday)) {
            printf("Erro: A data do empréstimo não pode ser no passado. Tente novamente.\n");
        } else {
            data_valida = 1;
        }
    }

    // PASSO 3: CONFIRMAÇÃO FINAL
    printf("\n--- Revise os Dados do Empréstimo ---\n");
    printf("Leitor: %s\n", novo_emprestimo->leitor);
    printf("Livro: %s (ISBN: %s)\n", livros[livro_idx].titulo, novo_emprestimo->ISBN);
    printf("Data: %02d/%02d/%d\n", novo_emprestimo->DataDoEmprestimo.dia, novo_emprestimo->DataDoEmprestimo.mes, novo_emprestimo->DataDoEmprestimo.ano);
    
    int confirmacao = 0;
    printf("\nDeseja confirmar e salvar este empréstimo? (1-Sim / Outro número-Não): ");
    scanf("%d", &confirmacao);
    while(getchar() != '\n');

    if (confirmacao == 1) {
        novo_emprestimo->id = gerarNovoId("arquivos/emprestimos.txt");
        novo_emprestimo->status = ANDAMENTO;
        salvarNovoEmprestimo(novo_emprestimo);
        printf("\nEmpréstimo cadastrado com sucesso!\n");
    } else {
        printf("\nOperação cancelada pelo usuário.\n");
    }

    free(livros);
    free(novo_emprestimo);
}

void registrarDevol() {
    Emprestimos *emprestimos = NULL;
    int total = 0;
    carregarEmprestimos(&emprestimos, &total);

    if (total == 0) {
        printf("\nNenhum empréstimo cadastrado para registrar devolução.\n");
        return;
    }

    // Mostra todos os empréstimos em andamento
    printf("\n--- Empréstimos em Andamento ---\n");
    int algum = 0;
    for (int i = 0; i < total; i++) {
        if (emprestimos[i].status == ANDAMENTO) {
            printf("ID: %u | Leitor: %s | ISBN do Livro: %s | Data: %02d/%02d/%d\n",
                   emprestimos[i].id,
                   emprestimos[i].leitor,
                   emprestimos[i].ISBN,
                   emprestimos[i].DataDoEmprestimo.dia,
                   emprestimos[i].DataDoEmprestimo.mes,
                   emprestimos[i].DataDoEmprestimo.ano);
            algum = 1;
        }
    }
    if (!algum) {
        printf("Nenhum empréstimo em andamento para devolução.\n");
        free(emprestimos);
        return;
    }

    printf("\n--- Registrar Devolução ---\n");
    unsigned int id_busca;
    printf("Digite o ID do empréstimo para devolver (ou 0 para cancelar): ");
    scanf("%u", &id_busca);
    while (getchar() != '\n');

    if (id_busca == 0) {
        printf("Operação cancelada.\n");
        free(emprestimos);
        return;
    }

    int encontrado = -1;
    for (int i = 0; i < total; i++) {
        if (emprestimos[i].id == id_busca) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Erro: Empréstimo com ID %u não encontrado.\n", id_busca);
    } else if (emprestimos[encontrado].status != ANDAMENTO) {
        printf("Aviso: Este empréstimo não está 'Em Andamento'. Status atual: %s\n", statusParaTexto(emprestimos[encontrado].status));
    } else {
        printf("\n--- Empréstimo Encontrado ---\n");
        printf("Leitor: %s\n", emprestimos[encontrado].leitor);
        printf("ISBN do Livro: %s\n", emprestimos[encontrado].ISBN);

        int confirmacao = 0;
        printf("\nConfirmar devolução deste item? (1-Sim / Outro número-Não): ");
        scanf("%d", &confirmacao);
        while(getchar() != '\n');

        if(confirmacao == 1){
            emprestimos[encontrado].status = CONCLUIDO;
            salvarTodosEmprestimos(emprestimos, total);
            printf("Devolução do empréstimo ID %u registrada com sucesso!\n", id_busca);
        } else {
            printf("Devolução cancelada.\n");
        }
    }

    if (emprestimos != NULL) {
        free(emprestimos);
    }
}

void listarEmprestimoPorStatus() {
    Emprestimos *emprestimos = NULL;
    int total = 0;
    carregarEmprestimos(&emprestimos, &total);

    if (total == 0) {
        printf("\nNenhum empréstimo cadastrado para listar.\n");
        return;
    }

    printf("\n--- Listar Empréstimos por Status ---\n");
    enum STATUS status_busca;
    receberStatus(&status_busca);

    int contador = 0;
    printf("\n--- Empréstimos com status '%s' ---\n", statusParaTexto(status_busca));
    for(int i = 0; i < total; i++) {
        if (emprestimos[i].status == status_busca) {
            printf("ID: %u | Leitor: %s | ISBN do Livro: %s | Data: %02d/%02d/%d\n",
                   emprestimos[i].id,
                   emprestimos[i].leitor,
                   emprestimos[i].ISBN,
                   emprestimos[i].DataDoEmprestimo.dia,
                   emprestimos[i].DataDoEmprestimo.mes,
                   emprestimos[i].DataDoEmprestimo.ano);
            contador++;
        }
    }

    if (contador == 0) {
        printf("Nenhum empréstimo encontrado com este status.\n");
    }

    if (emprestimos != NULL) {
        free(emprestimos);
    }
}

void MenuEmprestimos() {
    int op;
    do {
        printf("\n--- Módulo de Empréstimos ---\n");
        printf("1. Cadastrar Empréstimo\n");
        printf("2. Registrar Devolução\n");
        printf("3. Listar Empréstimos por Status\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 

        switch (op) {
            case 1:
                cadastrarEmprestimo();
                break;
            case 2:
                registrarDevol();
                break;
            case 3:
                listarEmprestimoPorStatus();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (op != 0);
}