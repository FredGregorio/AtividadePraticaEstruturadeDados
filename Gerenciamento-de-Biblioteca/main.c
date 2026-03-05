#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include "tipos.h"
#include "livros.h"
#include "emprestimos.h"
#include "relatorios.h"
#include "auxiliar.h"

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252"); // formatação dos acentos na hora de imprimir para o usuário

    int op;
    do {
        printf("Sistema de Gerenciamento de uma biblioteca\n");
        printf("Escolha a opção que você quer acessar:\n0.Sair\n1.Livros\n2.Empréstimos\n3.Relatórios\n");
        scanf("%d", &op);
        switch (op)
        {
            case 0:
                printf("Fechando programa\n");
                break;
            case 1:
                MenuLivros();
                break;
            case 2:
                MenuEmprestimos();
                break;
            case 3:
            MenuRelatorios();
        default:
            break;
        }
    }while(op != 0);
    return 0;
}