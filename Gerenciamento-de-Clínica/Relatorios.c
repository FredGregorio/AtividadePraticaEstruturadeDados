#include "Relatorios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "Auxiliar.h"
#include <time.h>


void relatorioConsultaPacientes() {
    char cpfBusca[12];
    printf("\nDigite o CPF do paciente para buscar suas consultas: ");
    setbuf(stdin, NULL);
    
    if (fgets(cpfBusca, sizeof(cpfBusca), stdin) == NULL) {
        printf("Erro ao ler CPF!\n");
        return;
    }
    cpfBusca[strcspn(cpfBusca, "\n")] = 0;

    int idPaciente = buscaPacienteCPF(cpfBusca);
    if (idPaciente == -1) {
        printf("Paciente não encontrado!\n");
        return;
    }

    Paciente paciente = buscaPacienteId(idPaciente);
    if (paciente.cpf[0] == '\0') {
        printf("Erro ao buscar dados do paciente!\n");
        return;
    }

    FILE *arquivo = fopen("Arquivos/Consultas.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de consultas!\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    printf("\n--- Consultas do Paciente ---\n");
    printf("Nome: %s\n", paciente.nome);
    printf("CPF: %s\n", paciente.cpf);
    printf("Contato: %s\n", paciente.contato);
    printf("--------------------------------\n");

    int id, idMed, idPac, dia, mes, ano, hora, min, status;
    int encontrouConsulta = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d,%d,%d,%d/%d/%d %d:%d,%d",
            &id, &idPac, &idMed, &dia, &mes, &ano, &hora, &min, &status) == 9) {
            if (idPac == idPaciente) {
                encontrouConsulta = 1;
                Medico medico = buscaMedicoId(idMed);
                
                printf("\nConsulta ID: %d\n", id);
                printf("Médico: %s (CRM: %s)\n", medico.nome, medico.crm);
                printf("Especialidade: %s\n", especialidadeParaTexto(medico.especialidade));
                printf("Data: %02d/%02d/%04d\n", dia, mes, ano);
                printf("Hora: %02d:%02d\n", hora, min);
                printf("Status: %s\n", statusConsultaParaTexto(status));
                printf("--------------------------------\n");
            }
        }
    }

    if (!encontrouConsulta) {
        printf("Nenhuma consulta encontrada para este paciente.\n");
    }
    fclose(arquivo);
}

void relatorioConsultaMedicos() {
    char crmBusca[12];
    printf("\nDigite o CRM do médico para buscar suas consultas: ");
    setbuf(stdin, NULL);
    
    if (fgets(crmBusca, sizeof(crmBusca), stdin) == NULL) {
        printf("Erro ao ler CRM!\n");
        return;
    }
    crmBusca[strcspn(crmBusca, "\n")] = 0;

    int idMedico = buscaMedicoCRM(crmBusca);
    if (idMedico == -1) {
        printf("Médico não encontrado!\n");
        return;
    }

    Medico medico = buscaMedicoId(idMedico);
    if (medico.crm[0] == '\0') {
        printf("Erro ao buscar dados do médico!\n");
        return;
    }

    FILE *arquivo = fopen("Arquivos/Consultas.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de consultas!\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); 

    printf("\n=== Consultas do Médico ===\n");
    printf("Nome: %s\n", medico.nome);
    printf("CRM: %s\n", medico.crm);
    printf("Especialidade: %s\n", especialidadeParaTexto(medico.especialidade));
    printf("--------------------------------\n");

    int id, idMed, idPac, dia, mes, ano, hora, min, status;
    int encontrouConsulta = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d,%d,%d,%d/%d/%d %d:%d,%d",
            &id, &idPac, &idMed, &dia, &mes, &ano, &hora, &min, &status) == 9) {
            if (idMed == idMedico) {
                encontrouConsulta = 1;
                Paciente paciente = buscaPacienteId(idPac);
                
                printf("\nConsulta ID: %d\n", id);
                printf("Paciente: %s (CPF: %s)\n", paciente.nome, paciente.cpf);
                printf("Contato: %s\n", paciente.contato);
                printf("Data: %02d/%02d/%04d\n", dia, mes, ano);
                printf("Hora: %02d:%02d\n", hora, min);
                printf("Status: %s\n", statusConsultaParaTexto(status));
                printf("--------------------------------\n");
            }
        }
    }

    if (!encontrouConsulta) {
        printf("Nenhuma consulta encontrada para este médico.\n");
    }
    fclose(arquivo);
}

void relatorioConsultaPorEspecialidae() {
    // Array para armazenar contagem por especialidade
    int contagem[6] = {0}; // 6 é o número de especialidades

    FILE *arquivo = fopen("Arquivos/Consultas.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de consultas!\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    // Variáveis para ler cada linha
    int id, idMed, idPac, dia, mes, ano, hora, min, status;
    int totalConsultas = 0;

    // Lê cada consulta
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d,%d,%d,%d/%d/%d %d:%d,%d",
            &id, &idPac, &idMed, &dia, &mes, &ano, &hora, &min, &status) == 9) {
            
            // Busca o médico para saber sua especialidade
            Medico medico = buscaMedicoId(idMed);
            if (medico.crm[0] != '\0') {
                contagem[medico.especialidade]++;
                totalConsultas++;
            }
        }
    }
    fclose(arquivo);

    // Cria arquivo de relatório
    FILE *relatorio = fopen("Arquivos/Relatorios/Relatorio_Especialidades.txt", "w");
    if (!relatorio) {
        printf("Erro ao criar arquivo de relatório!\n");
        return;
    }

    // Obter data e hora atual
    time_t t = time(NULL);
    struct tm* data_atual = localtime(&t);
    char data_str[32];
    strftime(data_str, sizeof(data_str), "%d/%m/%Y %H:%M:%S", data_atual);

    // Escreve cabeçalho com data atual
    fprintf(relatorio, "=== Relatório de Consultas por Especialidade ===\n");
    fprintf(relatorio, "Data do relatório: %s\n\n", data_str);

    // Imprime na tela e escreve no arquivo
    printf("\n=== Relatório de Consultas por Especialidade ===\n");
    printf("Data do relatório: %s\n\n", data_str);

    for (int i = 0; i < 6; i++) {
        const char *especialidade = especialidadeParaTexto(i);

        // Escreve no arquivo
        fprintf(relatorio, "%-20s: %d consultas\n",
                especialidade, contagem[i]);

        // Imprime na tela
        printf("%-20s: %d consultas\n",
               especialidade, contagem[i]);
    }

    // Adiciona total
    fprintf(relatorio, "\nTotal de consultas: %d\n", totalConsultas);
    printf("\nTotal de consultas: %d\n", totalConsultas);

    fclose(relatorio);
    printf("\nRelatório salvo em 'Arquivos/Relatorios/Relatorio_Especialidades.txt'\n");
}

void relatorioConsultaDiaAtual() {
    // Obter data atual
    time_t t = time(NULL);
    struct tm* data_atual = localtime(&t);
    int dia_atual = data_atual->tm_mday;
    int mes_atual = data_atual->tm_mon + 1;
    int ano_atual = data_atual->tm_year + 1900;

    printf("\n=== Consultas do Dia %02d/%02d/%04d ===\n", 
           dia_atual, mes_atual, ano_atual);

    FILE *arquivo = fopen("Arquivos/Consultas.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de consultas!\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    int id, idMed, idPac, dia, mes, ano, hora, min, status;
    int encontrouConsulta = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d,%d,%d,%d/%d/%d %d:%d,%d",
            &id, &idPac, &idMed, &dia, &mes, &ano, &hora, &min, &status) == 9) {
            
            // Verifica se a consulta é do dia atual
            if (dia == dia_atual && mes == mes_atual && ano == ano_atual) {
                encontrouConsulta = 1;
                
                // Busca informações do paciente e médico
                Paciente paciente = buscaPacienteId(idPac);
                Medico medico = buscaMedicoId(idMed);
                
                printf("\nConsulta ID: %d\n", id);
                printf("Horário: %02d:%02d\n", hora, min);
                printf("Paciente: %s (CPF: %s)\n", paciente.nome, paciente.cpf);
                printf("Médico: %s (CRM: %s)\n", medico.nome, medico.crm);
                printf("Especialidade: %s\n", especialidadeParaTexto(medico.especialidade));
                printf("Status: %s\n", statusConsultaParaTexto(status));
                printf("--------------------------------\n");
            }
        }
    }

    if (!encontrouConsulta) {
        printf("\nNenhuma consulta agendada para hoje.\n");
    }

    fclose(arquivo);
}

   
void menuRelatorios() {
    int opcao = -1;
    char input[10];
    do {
        printf("\nMenu Relatórios\n");
        printf("1. Relatório de Consultas (Pacientes)\n");
        printf("2. Relatório de Consultas (Médicos)\n");
        printf("3. Relatório de Consulta (Especialidade)\n");
        printf("4. Relatório de Consulta Dia Atual\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        
        setbuf(stdin, NULL);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Erro ao ler opção!\n");
            continue;
        }
        
        opcao = atoi(input);

        switch (opcao) {
            case 0:
                printf("Voltando...\n");
                break;
            case 1:
                relatorioConsultaPacientes();
                break;
            case 2:
                relatorioConsultaMedicos();
                break;
            case 3:
                relatorioConsultaPorEspecialidae();
                break;
            case 4:
                relatorioConsultaDiaAtual();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

