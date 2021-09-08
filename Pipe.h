#ifndef PIPE_H
#define PIPE_H

typedef struct {
    int filedes[2];
} Pipe;

void inicializarPipe(Pipe *p);

void escreverPipe(Pipe *p, char inst);

void lerPipe(Pipe *p, char *inst);

#endif