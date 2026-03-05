#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "Relatorios.h"
#include "Consulta.h"
#include "Auxiliar.h"




void carregarConsultas(Consulta **consultas, int *total)
{
    FILE *arquivo = fopen("Arquivos/Consultas.txt", "r");
    if(!arquivo) 
    {
        *total = 0;
        *consultas = NULL;
        return;
    }
    //pular cabeçalho (primeira linha)
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);

    *total = 0;
    Consulta temp;
    int status_temp;

    //ler cada linha do arquivo
    while(fscanf(arquivo, "%d,%d,%d,%d/%d/%d %d:%d,%d\n",
        &temp.id,
        &temp.pacienteId,
        &temp.medicoId,
        &temp.data_hora.dia,
        &temp.data_hora.mes,
        &temp.data_hora.ano,
        &temp.data_hora.hora,
        &temp.data_hora.minuto,
        &status_temp) == 9) 

        {
            //alocar espaço para mais um médico e adicionar
            *consultas = realloc(*consultas, (*total + 1) * sizeof(Consulta));
            (*consultas)[*total] = temp;
            (*total)++;
    }
    fclose(arquivo);
}

void salvarConsultas(Consulta *consultas, int total, const char *modo) { 
    
    FILE *arquivo = fopen("Arquivos/Consultas.txt", modo);
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    //se for modo write, reescreve o cabeçalho
    if (strcmp(modo, "w") == 0) {
        fprintf(arquivo, "ID,PacienteId,MedicoId,Data Hora,Status\n");
    }

    //escreve as consultas
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%d,%d,%d,%02d/%02d/%04d %02d:%02d,%d\n", 
                consultas[i].id, 
                consultas[i].pacienteId,
                consultas[i].medicoId, 
                consultas[i].data_hora.dia,
                consultas[i].data_hora.mes,
                consultas[i].data_hora.ano,
                consultas[i].data_hora.hora,
                consultas[i].data_hora.minuto,     
                consultas[i].status);
    }

    fclose(arquivo);
}


void alterarStatusConsulta(enum statusConsulta novoStatus){
    int id, total;
    printf("\nDigite o id da consulta que voce quer alterar: ");
    scanf("%d",&id);

    //Verificar se id está cadastrada.
    Consulta *consultas = NULL;
    carregarConsultas(&consultas, &total);
    int encontrado = -1;
    for (int i = 0; i < total; i++){
        if(consultas[i].id == id) 
        {
            exibirConsulta(consultas[i]);
            encontrado = i;
            break;
        }
    }
    //Salvamento da alteraçao
    if (encontrado != -1){
        //Confirmar alteração
        printf("\nDeseja alterar o status para %s?", statusConsultaParaTexto(novoStatus));
        int opcao;
        do {
            printf("\n1. Salvar\n");
            printf("2. Sair sem salvar\n");
            printf("selecione uma opção: ");
            scanf("%d", &opcao);
            getchar(); 

            switch(opcao) {
                case 1:
                consultas[encontrado].status = novoStatus;
                salvarConsultas(consultas, total,"w");
                printf("Status atualizado!\n");
                break;
                case 2:
                    printf("Atualização de status descartada.\n");
                    break;
                    
                default:
                    printf("Opção inválida!\n");
                    continue;
            }
        } while(opcao < 1 || opcao > 2);
    }
    else {
        printf("Consulta não encontrada");
    }
    free(consultas);

    }

void listarConsultas(){
    Consulta *consultas = NULL;
    int total;
    carregarConsultas(&consultas, &total);

    printf("\nLista de Consultas:\n");
    for (int i = 0; i < total; i++)
    {
        exibirConsulta(consultas[i]);
    }

    free(consultas);

}

void agendarConsulta() {
    verificarArquivo("Arquivos/Consultas.txt", "Id,PacienteId,MedicoId,Data Hora,Status\n");

    Consulta nova = {0}; // Inicializa a consulta
    char cpf[12], crm[7];
    int pacienteId, medicoId;

    // Receber CPF do paciente
    printf("\n--- Dados do Paciente ---\n");
    while (getchar() != '\n');
    receberCPF(cpf, 1); // deveExistir=1 (paciente deve existir)
    pacienteId = buscaPacienteCPF(cpf);
    
    if(pacienteId == -1) {
        printf("Erro: Paciente não encontrado!\n");
        return;
    }

    // Receber CRM do médico
    printf("\n--- Dados do Médico ---\n");
    receberCRM(crm, 1); // deveExistir=1 (médico deve existir)
    medicoId = buscaMedicoCRM(crm);
    
    if(medicoId == -1) {
        printf("Erro: Médico não encontrado!\n");
        return;
    }

    // Atribuir IDs encontrados
    nova.pacienteId = pacienteId;
    nova.medicoId = medicoId;
    nova.status = AGENDADA; // Status inicial

    // Coletar data e hora
    printf("\n--- Data e Hora da Consulta ---\n");
    receberDataHora(&nova.data_hora);

    // Confirmar dados
    printf("\n--- Resumo da Consulta ---\n");
    
    // Buscar e mostrar dados do paciente
    Paciente paciente = buscaPacienteId(nova.pacienteId);
    printf("Paciente:\n");
    printf("  Nome: %s\n", paciente.nome);
    printf("  CPF: %s\n", paciente.cpf);
    printf("  Contato: %s\n", paciente.contato);

    // Buscar e mostrar dados do médico
    Medico medico = buscaMedicoId(nova.medicoId);
    printf("\nMédico:\n");
    exibirMedico(medico);

    printf("\nData e Hora:\n");
    printf("  Data: %02d/%02d/%04d\n", nova.data_hora.dia, nova.data_hora.mes, nova.data_hora.ano);
    printf("  Hora: %02d:%02d\n", nova.data_hora.hora, nova.data_hora.minuto);
    printf("--------------------------------\n");

    // Confirmar salvamento
    int opcao;
    do {
        printf("\n1. Confirmar agendamento\n");
        printf("2. Cancelar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                // GERAR ID USANDO SUA FUNÇÃO
                nova.id = gerarNovoId("Arquivos/Consultas.txt");
                
                // Salvar a nova consulta
                salvarConsultas(&nova, 1, "a");
                printf("\nConsulta agendada com sucesso! ID: %d\n", nova.id);
                break;
            case 2:
                printf("Agendamento cancelado.\n");
                break;
            default:
                printf("Opção inválida!\n");
                continue;
        }
    } while(opcao != 1 && opcao != 2);
}




void menuConsultas(){
    int opcao;
    do
    {
        printf("\nMenu Principal de Consultas\n");
        printf("1. Agendar Consulta\n");
        printf("2. Cancelar Consulta\n");
        printf("3. Registrar Consulta\n");
        printf("4. Listar Consultas Por Paciente\n");
        printf("5. Listar Consultas Por Medico\n");        
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {   case 0:
                return;
                break;
            case 1:
                agendarConsulta();
                break;
            case 2:
                printf("\nCancelamento de consulta!\n");
                alterarStatusConsulta(CANCELADA);
                break;
            case 3:
                printf("\nRegistro de consulta!\n");
                alterarStatusConsulta(REALIZADA);
                break;
            case 4: 
                relatorioConsultaPacientes();
                break;
            case 5:
                relatorioConsultaMedicos();
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }  
    } while (opcao != 5);

}