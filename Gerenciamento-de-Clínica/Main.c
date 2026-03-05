#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "Medico.h"
#include "Paciente.h"
#include "Consulta.h"
#include "Relatorios.h"


int main (){
    int n;

    //Loop para manter o menu em execução.

    do {
        //Recebimento de valor para tomada de decisão
        printf("\nSistema de Gerenciamento Clínico\n.Menus: \n");
        printf("1. Médicos\n2. Pacientes\n3. Relatorios\n4. Consultas\n0. Sair\nEscolha a opção que voce quer acessar: ");
        scanf("%d", &n);

        //Switch case para decidir o menu que será encaminhado
        switch (n)
        {
        case 0:
            printf("Fechando programa\n");
            break;
        case 1:
            menuMedico();
            break;
        case 2:
            menuPaciente();
            break;
        case 3:
            menuRelatorios();
            break;
        case 4:
            menuConsultas();
            break;
        
        default:
            printf("Opção inválida");
            break;
        }
        
    }
    while (n != 0);
    
}



