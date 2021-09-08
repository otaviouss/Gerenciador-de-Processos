#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Leitura.h"

void lerTerminal(Pipe *p) {
    inicializarPipe(p);
    char c=' ';
    while(c != 'M') {
        scanf(" %c", &c);
        escreverPipe(p, c);
    }
    char *buffer;
}

void lerArquivo() {

}