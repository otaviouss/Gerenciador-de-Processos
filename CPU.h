#ifndef CPU_H
#define CPU_H

#include "ProcessoSimulado.h"

typedef struct {
    ProcessoSimulado* processo;
    int unidadeTempo;
} CPU;

void inicializaCPU(CPU* cpu);

void executaProcesso(CPU* cpu);

#endif