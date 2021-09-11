#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"

void inicializaCPU(CPU *cpu) {
    cpu->unidadeTempo = 0;
}

void insereProcessoCPU(CPU *cpu, ProcessoSimulado p) {
    cpu->processo = p;
}

/** Chamada pelo comando U 
 * Executa próxima instrução do processo simulado
*/
char executaProcessoCPU(CPU *cpu) {
    char ret;
    ret = executaProximaInstrucao(&cpu->processo);
    if(ret != ' ') {
        return ret;
    }
    incrementaTempo(&cpu->processo);
    cpu->unidadeTempo++;
    return ' ';
}

void pararProcessoCPU(CPU *cpu, ProcessoSimulado *p) {
    p = &cpu->processo;
}