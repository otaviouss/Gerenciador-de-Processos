#include <unistd.h>

#include "Pipe.h"

void escreverPipe(Pipe *p, char inst) {
    pipe(p->filedes);
    write(p->filedes[1], &inst, 1);
}

void lerPipe(Pipe *p, char *inst) {
    read ( p->filedes[0], inst, 1 );
}