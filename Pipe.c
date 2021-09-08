#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pipe.h"

void escreverPipe(Pipe *p, char inst) {
    pipe(p->filedes);
    write(p->filedes[1], &inst, 1);
}

void lerPipe(Pipe *p, char *inst) {
    int n;
    char buffer[1025];
    
    if ((n = read ( p->filedes[0], buffer, 1024 ) ) >= 0) {
        inst = (char*) malloc(sizeof(char)*n);
        buffer[n] = 0;
        inst = buffer;
        printf("read %d bytes from the pipe: %s\n", n, inst);
    } else {
        *inst = '0';
        perror("read");
    }
}