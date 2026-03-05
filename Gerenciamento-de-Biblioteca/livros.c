#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "auxiliar.h"


void salvarTodosLivros(Livro *livros, int total) {
    FILE *arquivo = fopen("arquivos/livros.txt", "w"); 
    
    //cabeçalho
    fprintf(arquivo, "id,ISBN,titulo,autor,genero\n");
    
    //escreve odos os registros
    for(int i = 0; i < total; i++) {
        fprintf(arquivo, "%d,%s,%s,%s,%d\n", 
        livros[i].id,
            livros[i].ISBN, 
            livros[i].titulo, 
            livros[i].autor, 
            livros[i].genero);
    }
    fclose(arquivo);
}


void salvarNovoLivro(Livro * livro){
        FILE *arquivo = fopen("arquivos/livros.txt","a");
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    //escreve os livros
    livro->id = gerarNovoId("arquivos/livros.txt");


    fprintf(arquivo, "%d,%s,%s,%s,%d\n",
            livro->id,
            livro->ISBN, 
            livro->titulo, 
            livro->autor, 
            livro->genero);
    

    fclose(arquivo);
}

void cadastrarLivro(){
// alocar memória para o Livro novo
    Livro *novo = (Livro*)malloc(sizeof(Livro));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    
    // coletar dados usando ponteiros
    printf("\n Novo Livros \n");
    while (getchar() != '\n');

    novo->id = 0;

    // coleta do ISBN com validações
    Livro *livros = NULL;
    int total = 0;
    carregarLivros(&livros, &total);


    // coleta do ISBN com validações e verificação de unicidade
    receberISBN(novo->ISBN);
    if(buscarLivroPorISBN(livros, total, novo->ISBN) != -1) 
    {
        printf("ISBN ja cadastrado.");
        free(novo); 
        free(livros);
        return;
    }
       

    // coleta do titulo
    printf("\nTítulo do livro ");
    receberTitulo(novo->titulo);

    // coleta do ISBN com validações
    printf("\nAutor do livro ");
    receberNome(novo->autor);

    // coleta do genero
    receberGenero(&novo->genero);

    // exibir os dados coletados
    exibirLivro(*novo);

    // perguntar se deseja salvar ou sair sem salvar
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
                salvarNovoLivro(novo); 
                printf("Livro cadastrado com sucesso!\n");
                break;
            case 2:
                printf("Cadastro descartado.\n");
                break;
            default:
                printf("Opção inválida!\n");
                continue;
        }
    } while(opcao < 1 || opcao > 2);

    free(livros);
    free(novo); 
}


    


void atualizarLivro(){
    Livro *livros = NULL;
    int total = 0;
    carregarLivros(&livros, &total);
    

    //Buscar livro
     printf("\n--- Atualização de Livro ---\n");
    char isbnBusca[14];
    while (getchar() != '\n');
    receberISBN(isbnBusca);
    
    int encontrado = buscarLivroPorISBN(livros, total, isbnBusca);

    if(encontrado == -1) {
        printf("livro não encontrado!\n");
        free(livros);
        return;
    }
    Livro atualizado = livros[encontrado];

   int modificarOutro = 1;
    do {
        printf("\nSelecione o campo para atualizar:\n");
        printf("1. ISBN (atual: %s)\n", atualizado.ISBN);
        printf("2. Titulo (atual: %s)\n", atualizado.titulo);
        printf("3. Autor (atual: %s)\n", atualizado.autor);
        printf("4. Gênero (atual: %s)\n", generoParaTexto(atualizado.genero));
        printf("5. Finalizar atualização\n");
        printf("Escolha: ");

        int opcaoCampo;
        if(scanf("%d", &opcaoCampo) != 1) {
            while(getchar() != '\n');  // Limpa input inválido
            printf("Entrada inválida!\n");
            continue;
        }
        while(getchar() != '\n');  // Limpa buffer do teclado

        switch(opcaoCampo) {
            case 1:

                receberISBN(atualizado.ISBN);
                if(buscarLivroPorISBN(livros, total, atualizado.ISBN) != -1) 
                {
                    printf("ISBN ja cadastrado.");
                    free(livros);
                    return;
                }
                
                break;
            case 2:
                printf("\nTítulo do livro ");
                receberTitulo(atualizado.titulo);
                break;
                
            case 3:
                printf("\nAutor do livro ");
                receberNome(atualizado.autor);
                break;
                
            case 4:
                printf("\nNovo genero:\n");
                receberGenero(&atualizado.genero);
                break;
                
            case 5:
                modificarOutro = 0;
                break;
                
            default:
                printf("Opção inválida!\n");
        }

        // Só pergunta se deseja modificar outro campo se não foi a opção de saída
        if(opcaoCampo != 5) {
            printf("\nDeseja modificar outro campo? (0-Não /1-Sim): ");
            if(scanf("%d", &modificarOutro) != 1) {
                modificarOutro = 0;  //força saída em caso de erro
            }
            while(getchar() != '\n');  //limpa buffer
        }
    } while(modificarOutro == 1);

    //substituir no vetor
    livros[encontrado] = atualizado;

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
                salvarTodosLivros(livros, total);
                printf("\nDados atualizados com sucesso\n");
                break;
            case 2:
                printf("Atualização descartada\n");
                break;
                
            default:
                printf("Opção inválida\n");
                continue;
        }
    } while(opcao < 1 || opcao > 2);
    if(livros) {free(livros);}
    
}


void removerLivro(){
    Livro *livros = NULL;
    int total = 0;
    carregarLivros(&livros, &total);
    

    //Buscar médico pelo crm
     printf("\n--- Atualização de Livro ---\n");
    char isbnBusca[14];
    while (getchar() != '\n');
    receberISBN(isbnBusca);
    
    int encontrado = buscarLivroPorISBN(livros, total, isbnBusca);

    if(encontrado == -1) {
        printf("livro não encontrado!\n");
        free(livros);
        return;
    }

    
    int opcao;
    do {
        printf("\nDeseja realmente remover o livro?\n");
        exibirLivro(livros[encontrado]);

        printf("1. Confirmar\n");
        printf("2. Cancelar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar(); 

        if(opcao < 1 || opcao > 2){
            printf("Opção inválida\n");
        }
        else{break;}
    } while(1);

     if(opcao == 2) {
        printf("Operação cancelada.\n");
        free(livros);
        return;
    }

    Livro * novoVetor = malloc((total - 1) * sizeof(Livro));
    if(!novoVetor) {
        printf("Erro de memória!\n");
        free(livros);
        return;
    }
    int j = 0;
    for(int i = 0; i < total; i++) {
        if(i != encontrado) {
            novoVetor[j] = livros[i];
            j++;
        }
    }

    salvarTodosLivros(novoVetor, total-1);


    free(novoVetor);
    if(livros) {free(livros);}
    printf("\nRemoção realizada com sucesso\n");
    return;
}


void MenuLivros(){

    int op;
    do {
        printf("\nLIVROS\n");
        printf("Escolha a opção que você quer acessar:\n0.Voltar\n1.Cadastrar Livro\n2. Remover Livro\n3.Atualizar Livro\n");
        scanf("%d", &op);
        switch (op)
        {
            case 0:
                return;
                break;
            case 1:
                cadastrarLivro();
                break;
            case 2:
                removerLivro();
                break;
            case 3:
                atualizarLivro();
            default:
                break;
        }
    }while(op != 0);
}