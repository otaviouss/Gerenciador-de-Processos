#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Leitura.h"

void lerTerminal(Pipe *p) {
    char c=' ';
    while(c != 'M') {
        scanf(" %c", &c);
        escreverPipe(p, c);
    }
    char *buffer;
    lerPipe(p, buffer);
}

void lerArquivo() {

}