#ifndef TIPOS_H
#define TIPOS_H


// TIPOS E ENUMS
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;
enum GENERO {FICCAO, DIDATICO, BIOGRAFIA, COMEDIA, TERROR, ROMANCE}; // REMOÇÃO DOS ACENTOS NOS enums

typedef struct {
    int id;
    char titulo[200];
    char autor[200];
    char ISBN[14];
    enum GENERO genero;
} Livro;

enum STATUS {CONCLUIDO, ANDAMENTO, CANCELADO};

typedef struct {
    unsigned int id;
    char leitor[200];
    char ISBN[14]; // alteração realizada (28/06/2025) -- O tamanho é 14 para comportar 13 números + o terminador nulo '\0'
    Data DataDoEmprestimo;
    enum STATUS status;
} Emprestimos;

//-------------------------------------------
//LIVROS
//Função de conversão de enums
const char* generoParaTexto(enum GENERO genero);
int receberGenero(enum GENERO * genero);

int validarISBN(const char *isbn);
int receberISBN(char * ISBN);

int validarTitulo(const char *nome);
int receberTitulo(char *nome);


void exibirLivro(Livro livro);

//-------------------------------------------
//EMPRESTIMOS
//Função de conversão de enums
const char* statusParaTexto(enum STATUS status);
int receberStatus(enum STATUS * status);

//void gerarIdEmprestimo();

//--------------------------------------------
//DATA E HORA
int receberData(Data *dh);
int validarData(int dia, int mes, int ano);


//-------------------------------------------
//Funções para  conponentes de ambas as structs: titulo, autor, e leitor
int validarNome(const char *nome);
int receberNome(char *nome);


#endif