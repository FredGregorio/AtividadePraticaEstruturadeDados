#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tipos.h"
#include "Auxiliar.h"

// cria um arquivo com cabeçalhos se ele não existir
void verificarArquivo(const char *caminho, const char *colunas) {
    FILE *arquivo = fopen(caminho, "r");
    
    if (arquivo == NULL) {
        arquivo = fopen(caminho, "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "%s", colunas); 
            fclose(arquivo);
        } else {
            printf("Erro ao criar o arquivo: %s\n", caminho);
        }
    } else {
        fclose(arquivo); 
    }
}


// lê entrada do usuário com controle de tamanho
int entradaLimitada(char *destino, int tamanho_max) {
    int i = 0, excesso = 0;
    char c;
    
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < tamanho_max - 1) {
            destino[i++] = c;
        }
        else{
            excesso = 1;
        }
    }
    destino[i] = '\0';
    return i; 
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
        // Ignorar cabeçalho
        if (primeiraLinha) {
            primeiraLinha = 0;
            continue;
        }
        
        // Ignorar linhas vazias ou muito curtas
        if (strlen(linha) < 3) continue;
        
        // Extrair ID
        int id;
        if (sscanf(linha, "%d,", &id) == 1) {
            // Filtrar IDs inválidos
            if (id > 0 && id < 1000000000) { // ID entre 1 e 999.999.999
                if (id > maxId) maxId = id;
                idsValidos++;
            }
        }
    }
    
    fclose(arquivo);
    
    // Se não encontrou IDs válidos, começa em 1
    return (idsValidos == 0) ? 1 : maxId + 1;
}

//Funções para Enums

//Converter Especialidade para string
const char* especialidadeParaTexto(enum ESPECIALIDADE esp) {
    switch (esp) {
        case CLINICO: return "CLINICO";
        case PEDIATRA: return "PEDIATRA";
        case CARDIOLOGISTA: return "CARDIOLOGISTA";
        case DERMATOLOGISTA: return "DERMATOLOGISTA";
        case PSIQUIATRA: return "PSIQUIATRA";
        case ORTOPEDISTA: return "ORTOPEDISTA";
        
        default: return "DESCONHECIDO";
    }
}


//Converter status da consulta para texto
const char* statusConsultaParaTexto(enum statusConsulta status) {
    switch(status) {
        case AGENDADA: return "AGENDADA";
        case REALIZADA: return "REALIZADA";
        case CANCELADA: return "CANCELADA";
        default: return "DESCONHECIDO";
    }
}



//Funções de carregamento de arquivos na memória
void carregarMedicos(Medico **medicos, int *total) {
    FILE *arquivo = fopen("Arquivos/Medicos.txt", "r");
    if (!arquivo) {
        *total = 0;
        *medicos = NULL;
        return;
    }

    //pular cabeçalho (primeira linha)
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);

    *total = 0;
    Medico temp;
    int especialidade_tmp;

    //ler cada linha do arquivo
    while (fscanf(arquivo, "%d,%99[^,],%6[^,],%d,%19[^\n]\n", 
                &temp.id,
                temp.nome, 
                temp.crm, 
                &especialidade_tmp, 
                temp.contato) == 5) {

        //converter especialidade
        temp.especialidade = (enum ESPECIALIDADE)especialidade_tmp;

        //alocar espaço para mais um médico e adicionar
        *medicos = realloc(*medicos, (*total + 1) * sizeof(Medico));
        (*medicos)[*total] = temp;
        (*total)++;
    }
    fclose(arquivo);
}

void carregarPacientes(Paciente **pacientes, int *total) {
    FILE *arquivo = fopen("Arquivos/Pacientes.txt", "r");
    if (!arquivo) {
        *total = 0;
        *pacientes = NULL;
        return;
    }

    //pular cabeçalho (primeira linha)
    char buffer[256];
    fgets(buffer, sizeof(buffer), arquivo);

    *total = 0;
    Paciente temp;

    //ler cada linha do arquivo
    while (fscanf(arquivo, "%d,%99[^,],%11[^,],%19[^\n]\n", 
                &temp.id,
                temp.nome, 
                temp.cpf,  
                temp.contato) == 4) {


        //alocar espaço para mais um médico e adicionar
        *pacientes = realloc(*pacientes, (*total + 1) * sizeof(Paciente));
        (*pacientes)[*total] = temp;
        (*total)++;
    }

    fclose(arquivo);
}






//Funções de busca

//buscaPacienteCPF(){} tem que retornar O ID do paciente
int buscaPacienteCPF(const char *cpf) {
    FILE *arquivo = fopen("Arquivos/Pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pacientes.\n");
        return -1; // Erro ao abrir o arquivo
    }

    char nome[100], cpfArquivo[12], contato[20];
    int id = 0;

    // Pular o cabeçalho
    fscanf(arquivo, "%*[^\n]\n");

    while (fscanf(arquivo, "%d,%99[^,],%11[^,],%19[^\n]\n", &id, nome, cpfArquivo, contato) == 4) {
        if (strcmp(cpfArquivo, cpf) == 0) {
            fclose(arquivo);
            return id; // Retorna o ID do paciente
        }
    }

    fclose(arquivo);
    return -1; // CPF não encontrado
}

//buscaPacienteId(){} tem que retornar um paciente com base no ID
Paciente buscaPacienteId(int idBuscado) {
    FILE *arquivo = fopen("Arquivos/Pacientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pacientes.\n");
        return (Paciente){0};
    }

    Paciente paciente = {0};
    char nome[100], cpf[12], contato[20];
    int id;

    // Pular o cabeçalho
    fscanf(arquivo, "%*[^\n]\n");

    while (fscanf(arquivo, "%d,%99[^,],%11[^,],%19[^\n]\n", &id, nome, cpf, contato) == 4) {
        if (id == idBuscado) { // Corrigido: antes estava comparando com id == id
            paciente.id = id;
            strcpy(paciente.nome, nome);
            strcpy(paciente.cpf, cpf);
            strcpy(paciente.contato, contato);
            fclose(arquivo);
            return paciente;
        }
    }

    fclose(arquivo);
    return (Paciente){0};
}



//buscaMedicoCRM(){} tem que retornar o ID do medico
int buscaMedicoCRM(const char *crm) {
    FILE *arquivo = fopen("Arquivos/Medicos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de médicos.\n");
        return -1; // Erro ao abrir o arquivo
    }

    char nome[100], crmArquivo[7], contato[20];
    int id, especialidade;

    // Pular o cabeçalho
    fscanf(arquivo, "%*[^\n]\n");

    while (fscanf(arquivo, "%d,%99[^,],%6[^,],%d,%19[^\n]\n", &id, nome, crmArquivo, &especialidade, contato) == 5) {
        if (strcmp(crmArquivo, crm) == 0) {
            fclose(arquivo);
            return id; // Retorna o ID do médico
        }
    }

    fclose(arquivo);
    return -1; // CRM não encontrado
}

//buscaMedicoId(){} tem que retornar um medico com base no ID
Medico buscaMedicoId(int idBuscado) {
    FILE *arquivo = fopen("Arquivos/Medicos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de médicos.\n");
        return (Medico){0}; // Retorna um médico vazio em caso de erro
    }

    Medico medico = {0};
    char nome[100], crm[7], contato[20];
    int id, especialidade;

    // Pular o cabeçalho
    fscanf(arquivo, "%*[^\n]\n");

    while (fscanf(arquivo, "%d,%99[^,],%6[^,],%d,%19[^\n]\n", 
                 &id, nome, crm, &especialidade, contato) == 5) {
        if (id == idBuscado) {
            medico.id = id;
            strcpy(medico.nome, nome);
            strcpy(medico.crm, crm);
            medico.especialidade = (enum ESPECIALIDADE)especialidade;
            strcpy(medico.contato, contato);
            fclose(arquivo);
            return medico;
        }
                 }

    fclose(arquivo);
    return (Medico){0}; // Retorna um médico vazio se não encontrado
}

//buscaConsultaEspecialidade(){} tem que retornar uma lista de consultas

//buscaConsultaCPF(){} tem que retornar uma lista de consultas

//buscaConsultaCRM(){} tem que retornar uma lista de consultas

//BuscaConsultaId(){} tem que retornar uma só consulta




//-----------------------FUNÇÕES DE EXIBIÇÃO

void exibirMedico(Medico medico){   
    printf("ID: %d\n", medico.id);
    printf("Nome: %s\n", medico.nome);
    printf("CRM: %s\n", medico.crm);
    printf("Especialidade: %s\n", especialidadeParaTexto(medico.especialidade));
    printf("Contato: %s\n", medico.contato);
}

void exibirPaciente(Paciente paciente){
    printf("ID: %d\n", paciente.id);
    printf("Nome: %s\n", paciente.nome);
    printf("CPF: %s\n", paciente.cpf);
    printf("contato: %s\n\n", paciente.contato);
}

void exibirConsulta(Consulta c) {
    printf("\nID: %d", c.id);
    printf("\nPaciente ID: %d", c.pacienteId);
    printf("\nMédico ID: %d", c.medicoId);
    printf("\nData: %02d/%02d/%04d", c.data_hora.dia, c.data_hora.mes, c.data_hora.ano);
    printf("\nHora: %02d:%02d", c.data_hora.hora, c.data_hora.minuto);
    printf("\nStatus: %s", statusConsultaParaTexto(c.status));
    printf("\n---------------------------\n");
}



//--------------------FUNÇÔES DE ENTRADA-----------------------

//Função para receber Especialidade
int receberEspecialidade(enum ESPECIALIDADE *especialidade) {
    printf("Selecione a especialidade:\n");
    for (int i = 0; i < 6; i++) {
        printf("  %d - %s\n", i, especialidadeParaTexto(i));
    }

    int opcao;
    do {
        printf("Digite o número da especialidade: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); 
        
        if (opcao < 0 || opcao >= 6) {
            printf("Opção inválida. Tente novamente.\n");
        }
        else {
            *especialidade = (enum ESPECIALIDADE)opcao;
            break;
        }
    } while (1);
    
    return 1;
}

// Funções relacionadas a entrada CPF

// Valida se o cpf tem 11 dígitos numéricos
int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) 
    {return 0;}
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) return 0;
    }
    
    return 1; // cpf válido
}

// Verifica se um cpf já existe no arquivo
int CPFJaCadastrado(const char *cpf) {
    FILE *arquivo = fopen("Arquivos/Pacientes.txt", "r");
    if (arquivo == NULL) {return -1;}

    char nome[100], cpfArquivo[12], telefone[20];
    int id;
    fscanf(arquivo, "%*[^\n]\n");  // Pular cabeçalho

    while (fscanf(arquivo, "%d,%99[^,],%11[^,],%19[^\n]", 
            &id, nome, cpfArquivo, telefone) == 4) 
    {
        if (strcmp(cpfArquivo, cpf) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

//Receber CPF
int receberCPF(char *cpf, int deveExistir){
    
    int cpfValido = 0;
    do{
        printf("Digite o CPF do paciente (só numeros):\n");
        entradaLimitada(cpf, 12);
        if(!validarCPF(cpf)){
            printf("Erro: CPF deve conter exatamente 11 números!\n");
            continue;
        }
        if (!deveExistir){
            if(CPFJaCadastrado(cpf))
            {
                printf("CPF já cadastrado no sistema!\n");
                continue;
            }
            if (CPFJaCadastrado(cpf) == -1){
            printf("Erro na verificação, tente novamente!\n");
            continue;
            }
        }
        else{
            if(!CPFJaCadastrado(cpf)){
                printf("CPF ainda não cadastrado\n");
                continue;
            }
        }
        
        cpfValido=1;
        
    }while(!cpfValido);
    return 1;
}


//Funções de CRM


// valida se o CRM tem 6 dígitos numéricos

int validarCRM(const char *crm) {
    if (strlen(crm) != 6) return 0;
    for (int i = 0; i < 6; i++) {
        if (!isdigit(crm[i])) return 0;
    }
    
    return 1; // crm válido
}

// Verifica se um CRM já existe no arquivo
int CRMJaCadastrado(const char *crm) {
    FILE *arquivo = fopen("Arquivos/Medicos.txt", "r");
    if (arquivo == NULL) {return -1;}

    char nome[100], crmArquivo[7], especialidade[100], contato[20];
    int id;

    // Pular o cabeçalho
    fscanf(arquivo, "%*[^\n]\n");
    while (fscanf(arquivo, "%d, %99[^,],%6[^,],%99[^,],%19[^\n]\n", &id, nome, crmArquivo, especialidade, contato) == 5) {
        if (strcmp(crmArquivo, crm) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

//Receber CRM
int receberCRM(char *crm, int deveExistir){
    
    int crmValido = 0;
    do{
        printf("Digite O CRM do médico (só numeros):\n");
        entradaLimitada(crm, 7);
        if(!validarCRM(crm)){
            printf("CRM deve conter exatamente 6 números!\n");
            continue;
        }
        if(!deveExistir){
            if (CRMJaCadastrado(crm)){
            printf("CRM já cadastrado no sistema!\n");
            continue;
            }
            if (CRMJaCadastrado(crm)== -1){
                printf("Erro na verificação, tente novamente!\n");
                continue;
            }
        }
        else{
            if(!CRMJaCadastrado(crm)){
                printf("CRM ainda não cadastrado\n");
                continue;
            }
        }
        crmValido=1;
        
    }while(!crmValido);
    return 1;
}



//Funções de Entrada nome


//Validar nome
int validarNome(const char *nome) {
    // Verificar tamanho e se contém apenas letras e espaços
    if (strlen(nome) == 0 || strlen(nome) > 99) {
        return 0;
    }
    
    // Verificar se contém apenas espaços
    int apenasEspacos = 1;
    for (int i = 0; i < strlen(nome); i++) {
        if (!isspace(nome[i])) {
            apenasEspacos = 0;
            break;
        }
    }
    if (apenasEspacos) {
        return 0;
    }

    for (int i = 0; i < strlen(nome); i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0;
        }
    }
    
    return 1;
}


//Receber Nome
int receberNome(char *nome){
    do {
        printf("Nome (máx 99 caracteres): ");
        entradaLimitada(nome, 100);

        if (!validarNome(nome)) {
            printf("Erro: Use apenas letras e espaços no nome e não deixe em branco!\n");
            continue;
        }
        break;
    }
    while (1);

    return 1;
    

}

//Funções de entrada Contato


//Validar contato
int validarContato(const char *contato){
    int len = strlen(contato);
    if (len < 10 || len > 19) return 0;
    
    // Verificar se contém apenas dígitos
    for (int i = 0; i < len; i++) {
        if (!isdigit(contato[i])) {
            return 0;
        }
    }
    return 1;
}

//Receber Contato
int receberContato(char *contato) {
    
    do {
        printf("contato (só numeros): ");
        entradaLimitada(contato, 20);
        if (!validarContato(contato)) {
            printf("Erro: Use apenas números!\n");
            continue;
        }
        break;
        
    } while (strlen(contato) == 0);

    return 1;
}

//Funções para data e hora

int validarHora(int hora, int minuto) {
    if (hora < 0 || hora > 23) return 0;
    if (minuto < 0 || minuto > 59) return 0;
    return 1;
}



// Verifica se a data é válida
int validarData(int dia, int mes, int ano) {
    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1) return 0;

    int diasNoMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // Ano bissexto
    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
        diasNoMes[1] = 29;

    if (dia > diasNoMes[mes - 1]) return 0;

    return 1;
}


int receberDataHora(DataHora *dh) {
    char buffer[100];
    do {
        printf("Data e hora da consulta (DD/MM/AAAA HH:MM): ");
        
        // Lê toda a linha incluindo o '\n'
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro na leitura.\n");
            return 0; // Trata erro de leitura
        }
        
        // Remove o '\n' do final se existir
        char *pos = strchr(buffer, '\n');
        if (pos) *pos = '\0';
        
        int resultado = sscanf(buffer, "%d/%d/%d %d:%d", 
                               &dh->dia, &dh->mes, &dh->ano, 
                               &dh->hora, &dh->minuto);
        
        if (resultado != 5) {
            printf("Erro: Formato inválido! Use DD/MM/AAAA HH:MM.\n");
            continue;
        }
        
        if (!validarData(dh->dia, dh->mes, dh->ano)) {
            printf("Erro: Data inválida!\n");
            continue;
        }
        
        if (!validarHora(dh->hora, dh->minuto)) {
            printf("Erro: Hora inválida!\n");
            continue;
        }
        
        break;
    } while (1);
    return 1;
}
