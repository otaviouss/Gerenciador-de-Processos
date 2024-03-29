#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menu.h"
#include "Pipe.h"
#include "GerenciadorProcessos.h"
#include "ProcessoSimulado.h"

int main() {

    Pipe p;
    GerenciadorProcessos gProc;

    menu(&p);
    inicializaGerenciador(&gProc);    
    executaGerenciador(&gProc, &p);

    return 0;
}