#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menu.h"
#include "Pipe.h"
#include "GerenciadorProcessos.h"
#include "ProcessoSimulado.h"

int main() {
   /*
    Pipe p;
    GerenciadorProcessos gProc;

    menu(&p);
    inicializaGerenciador(&gProc);    
    executaGerenciador(&gProc, &p);
*/



    Instrucao *ins = leArquivoDeInstrucoesPS();

    for(int j = 0; j < 10; j++){
        printf("%c %d\n", ins->i, ins->n1);
    }

    return 0;
}