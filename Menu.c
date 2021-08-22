
#include <stdio.h>
#include <stdlib.h>

#include "Menu.h"
#include "Leitura.h"

void menu(Pipe *p) {
    int op = -1;
    
    while(op != 0) {
        printf("\n\n   -- Menu --       \n");
        printf("1. Entrada Padrao       \n");
        printf("2. Arquivo              \n");
        printf("0. Sair                 \n");
        printf("Opcao Escolhida: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                lerTerminal(p);
                break;
            case 2:
                lerArquivo();
                break;
            case 0:
                break;
            default:
                break;
        }
    }

}