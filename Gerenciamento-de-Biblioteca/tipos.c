#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tipos.h"
#include "auxiliar.h"

//--------------------------------------------
//LIVROS


//Função de conversão de enums
const char* generoParaTexto(enum GENERO genero){
    switch(genero) {
        case FICCAO: return "Ficção"; // REMOÇÃO DOS ACENTOS AQUI TAMBÉM ( FOI FEITO DIRETO NA  DEFINIÇÃO DO ENUM LÁ NO "tipos.h")
        case DIDATICO: return "Didático"; // REMOÇÃO DOS ACENTOS AQUI TAMBÉM ( FOI FEITO DIRETO NA  DEFINIÇÃO DO ENUM LÁ NO "tipos.h")
        case BIOGRAFIA: return "Biografia";
        case COMEDIA: return "Comédia";
        case TERROR: return "Terror";
        case ROMANCE: return "Romance";
        default: return "DESCONHECIDO";
    }
}

int receberGenero(enum GENERO * genero){
    for (int i = 0; i < 6; i++){
        printf("%d - %s\n", i, generoParaTexto(i));
    }

    int op;
        do {
        printf("Digite o gênero do livro: ");
        scanf("%d", &op);
        while (getchar() != '\n'); 

        if (op < 0 || op >= 6) {
            printf("Opção inválida. Tente novamente.\n");
        }
        else {
            *genero = (enum GENERO)op;
            break;
        }
    } while (1);

    return 1;
}

//Funções para ISBN
int validarISBN(const char *isbn){
        if (strlen(isbn) != 13) 
    {return 0;}
    for (int i = 0; i < 13; i++) {
        if (!isdigit(isbn[i])) return 0;
    }

    return 1; // isbn válido
}

int receberISBN(char * ISBN){
    int isbnValido = 0;

    do {
        printf("\nDigite o ISBN do livro:\n");
        ler_entrada_limitada(ISBN, 14);
        if(validarISBN(ISBN)){
            isbnValido = 1;
        }
        else{printf("\nErro: ISBN deve conter exatamente 13 números\n");}
    } while(!isbnValido);
}


//Funções para titulo
int validarTitulo(const char *nome) {
    // Verificar tamanho e se contém apenas letras e espaços
    if (strlen(nome) == 0 || strlen(nome) > 199) {
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

    return 1;
}

int receberTitulo(char *nome){
    do {
        printf("Nome (máx 199 caracteres): ");
        ler_entrada_limitada(nome, 200);

        if (!validarTitulo(nome)) {
            printf("Erro: Use apenas letras e espaços no nome e não deixe em branco!\n");
            continue;
        }
        break;
    }
    while (1);

    return 1;
}


void exibirLivro(Livro livro){
    printf("ISBN: %s\n", livro.ISBN);
    printf("Título: %s\n", livro.titulo);
    printf("ISBN: %s\n", livro.autor);
    printf("ISBN: %s\n", generoParaTexto(livro.genero));
}
//--------------------------------------------
//EMPRESTIMOS
//Função de conversão de enums
const char* statusParaTexto(enum STATUS status){
        switch(status) {
        case CANCELADO: return "CANCELADO";
        case ANDAMENTO: return "EM ANDAMENTO";
        case CONCLUIDO: return "CONCLUÍDO";
        default: return "DESCONHECIDO";
    }
}

int receberStatus(enum STATUS * status){
    printf("\nDigite o status:\n");
    for (int i = 0; i < 3; i++){
        printf("%d - %s\n", i, statusParaTexto(i));
    }

    int op;
        do {
        printf("Digite o número do status: ");
        scanf("%d", &op);
        while (getchar() != '\n'); 

        if (op < 0 || op >= 3) {
            printf("Opção inválida. Tente novamente.\n");
        }
        else {
            *status = (enum STATUS )op;
            break;
        }
    } while (1);

    return 1;
}

/*void gerarIdEmprestimo(){
        FILE *arquivo = fopen("arquivos/emprestimos.txt", "r");
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

*/

//--------------------------------------------
//DATA E HORA

int validarHora(int hora, int minuto) {
    if (hora < 0 || hora > 23) return 0;
    if (minuto < 0 || minuto > 59) return 0;
    return 1;
}

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

int receberData(Data *dh) {
    char buffer[100];
    do {
        printf("Data do empréstimo (DD/MM/AAAA): ");
        
        // Lê toda a linha incluindo o '\n'
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro na leitura.\n");
            return 0; // Trata erro de leitura
        }
        
        // Remove o '\n' do final se existir
        char *pos = strchr(buffer, '\n');
        if (pos) *pos = '\0';
        
        int resultado = sscanf(buffer, "%d/%d/%d", 
                               &dh->dia, &dh->mes, &dh->ano);
        
        if (resultado != 3) {
            printf("Erro: Formato inválido! Use DD/MM/AAAA.\n");
            continue;
        }
        
        if (!validarData(dh->dia, dh->mes, dh->ano)) {
            printf("Erro: Data inválida!\n");
            continue;
        }
        
        break;
    } while (1);
    return 1;
}


//-------------------------------------------
//Funções para componentes de ambas as structs: autor, e leitor
int validarNome(const char *nome) {
    // Verificar tamanho e se contém apenas letras e espaços
    if (strlen(nome) == 0 || strlen(nome) > 199) {
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
        printf("(máx 199 caracteres): \n");
        ler_entrada_limitada(nome, 200);

        if (!validarNome(nome)) {
            printf("Erro: Use apenas letras e espaços no nome e não deixe em branco!\n");
            continue;
        }
        break;
    }
    while (1);

    return 1;
}