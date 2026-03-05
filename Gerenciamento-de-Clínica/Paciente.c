#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "Paciente.h"
#include "Auxiliar.h"



void salvarPacientes(Paciente *pacientes, int total, const char *modo) {

    
    FILE *arquivo = fopen("Arquivos/Pacientes.txt", modo);
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    //se for modo write, reescreve o cabeçalho
    if (strcmp(modo, "w") == 0) {
        fprintf(arquivo, "Id,Nome,CPF,Contato\n");
    }

    //escreve os Pacientes
    for (int i = 0; i < total; i++) {
    // Gerar ID se for novo registro
        if (pacientes[i].id == 0) {
            pacientes[i].id = gerarNovoId("Arquivos/Pacientes.txt");
        }
        
        fprintf(arquivo, "%d,%s,%s,%s\n", 
                pacientes[i].id,
                pacientes[i].nome, 
                pacientes[i].cpf, 
                pacientes[i].contato);
    }

    fclose(arquivo);
}



void cadastrarPaciente()
{
    verificarArquivo("Arquivos/Pacientes.txt", "Id,Nome,CPF,Contato\n");

    //alocar memória para o paciente
    Paciente *novo = (Paciente*)malloc(sizeof(Paciente));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }
    printf("\n Novo Paciente \n");
    while (getchar() != '\n');
    novo->id = 0;
    //coletar nome
    receberNome(novo->nome);
    
    //coleta do CPF com validações
    receberCPF(novo->cpf, 0);

    //coleta do contato
    receberContato(novo->contato);

    // exibir os dados coletados
    exibirPaciente(*novo);

    printf("\nDeseja salvar os dados?");
    int opcao;
    do {
        printf("\n1. Salvar\n");
        printf("2. Sair sem salvar\n");
        printf("selecione uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                salvarPacientes(novo, 1, "a");
                printf("Paciente cadastrado com sucesso!\n");
                break;
            case 2:
                printf("Cadastro descartado.\n");
                break;
                
            default:
                printf("Opção inválida!\n");
                continue;
        }
    } while(opcao < 1 || opcao > 2);

    free(novo); 
}








void listarPaciente()
{
   Paciente *pacientes = NULL;
    int total;
    carregarPacientes(&pacientes, &total);   
    FILE *arquivo = fopen("Arquivos/Pacientes.txt", "r");
    if (total == 0) {
        printf("Nenhum paciente cadastrado!\n");
        return;
    }
    
    printf("\nLista de Pacientes:\n"); 
    for(int i = 0; i < total; i++)
    {
        exibirPaciente(pacientes[i]);
    }
    
    free(pacientes); //liberar memória alocada
}


void atualizarPaciente() {

    verificarArquivo("Arquivos/Pacientes.txt", "Id,Nome,CPF,Contato\n");

    Paciente *pacientes = NULL;
    int total = 0;
    carregarPacientes(&pacientes, &total);
    
    while (getchar() != '\n');

    char cpfBusca[12];
    printf("\n--- Atualização de Paciente ---\n");
    printf("Digite o CPF do paciente que deseja atualizar: ");
    receberCPF(cpfBusca, 1);

    int encontrado = -1;
    for(int i = 0; i < total; i++) {
        if(strcmp(pacientes[i].cpf, cpfBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if(encontrado == -1) {
        printf("Paciente não encontrado!\n");
        free(pacientes);
        return;
    }

    Paciente atualizado = pacientes[encontrado];

    //coletar novos dados (mesma sequência do cadastro)
    
    printf("\nAtualizar Dados\n");

    int modificarOutro = 1;
    do {
        printf("\nSelecione o campo para atualizar:\n");
        printf("1. Nome (atual: %s)\n", atualizado.nome);
        printf("2. CPF (atual: %s)\n", atualizado.cpf);
        printf("3. Contato (atual: %s)\n", atualizado.contato);
        printf("4. Finalizar atualização\n");
        printf("Escolha: ");

        int opcaoCampo;
        scanf("%d", &opcaoCampo);
        while(getchar() != '\n'); // Limpar buffer

        switch(opcaoCampo) {
            case 1:
                printf("\nNovo nome: ");
                receberNome(atualizado.nome);
                break;
            case 2:
                printf("\nNovo CPF: ");
                receberCPF(atualizado.cpf, 0);
                break;
            case 3:
                printf("\nNovo contato: ");
                receberContato(atualizado.contato);
                break;
            case 4:
                modificarOutro = 0;
                break;
            default:
                printf("Opção inválida!\n");
        }

        if(opcaoCampo != 4) {
            printf("\nDeseja modificar outro campo? (0-Não /1-Sim): ");
            scanf("%d", &modificarOutro);
            while(getchar() != '\n'); // Limpar buffer
        }
    } while(modificarOutro == 1);

    //substituir no vetor
    pacientes[encontrado] = atualizado;
    
    printf("\nDeseja salvar os dados?");
    int opcao;
            do {
                printf("\n1. Salvar alterações\n");
                printf("2. Cancelar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar(); // limpar buffer

                switch (opcao) {
                    case 1:
                        salvarPacientes(pacientes, total, "w");
                        printf("Paciente atualizado com sucesso!\n");
                        break;
                    case 2:
                        printf("Alterações canceladas.\n");
                        break;
                    default:
                        printf("Opção inválida!\n");
                }
            } while (opcao != 1 && opcao != 2);
            free(pacientes);
}

void removerPaciente()
{   verificarArquivo("Arquivos/Pacientes.txt", "Id,Nome,CPF,Contato\n");

    Paciente *pacientes = NULL;
    int total = 0;
    carregarPacientes(&pacientes, &total);

    if (total == 0) {
        printf("Nenhum paciente cadastrado!\n");
        return;
    }

    while (getchar() != '\n');
    // Obter CPF para remoção
    char cpfBusca[12];
    printf("\n--- Remoção de Paciente ---\n");
    printf("Digite o CPF do paciente (somente números): ");
    receberCPF(cpfBusca, 1);

    int encontrado = -1;
    for(int i = 0; i < total; i++) {
        if(strcmp(pacientes[i].cpf, cpfBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if(encontrado == -1) {
        printf("Paciente não encontrado!\n");
        free(pacientes);
        return;
    }

    //confirmar remoção
    int opcao;
    do {
        printf("\nDeseja realmente remover o paciente %s?\n", pacientes[encontrado].nome);
        printf("1. Confirmar\n");
        printf("2. Cancelar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpar buffer
    } while (opcao < 1 || opcao > 2);

    if (opcao == 2) {
        printf("Operação cancelada.\n");
        free(pacientes);
        return;
    }

    //criar novo vetor sem o paciente
    Paciente *novoVetor = malloc((total - 1) * sizeof(Paciente));
    if (!novoVetor) {
        printf("Erro de memória!\n");
        free(pacientes);
        return;
    }
    int j = 0;
    for (int i = 0; i < total; i++) {
        if (i != encontrado) {
            novoVetor[j++] = pacientes[i];
        }
    }

    //salvar 
    salvarPacientes(novoVetor, total - 1, "w");
    free(pacientes);
    free(novoVetor);

    printf("\nPaciente removido com sucesso!\n");

}

void menuPaciente()
{
    int opcao;
    do
    {
        printf("\nMenu Principal de Pacientes\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Atualizar Paciente\n");
        printf("3. Remover Paciente\n");
        printf("4. Listar Pacientes\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            return;
            break;
        case 1:
            cadastrarPaciente();
            break;
        case 2:
            atualizarPaciente();
            break;
        case 3:
            removerPaciente();
            break;
        case 4: // Remover depois
            listarPaciente();
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);
}