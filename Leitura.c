#include <stdlib.h>
#include <stdio.h>

#include <Leitura.h>

void lerTerminal(Pipe *p) {
    char c=' ';
    while(c != 'M') {
        scanf(" %c", &c);
        escreverPipe(p, c);
    }
}

void lerArquivo() {

}