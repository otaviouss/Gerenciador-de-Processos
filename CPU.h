#ifndef CPU_H
#define CPU_H

#include "ProcessoSimulado.h"

typedef struct {
    ProcessoSimulado processo;
    int unidadeTempo;
} CPU;

void inicializaCPU(CPU *cpu);

void insereProcessoCPU(CPU *cpu, ProcessoSimulado p); 

void executaProcessoCPU(CPU *cpu);

void pararProcessoCPU(CPU *cpu, ProcessoSimulado *p);

void comandoU(CPU *cpu);

#endif