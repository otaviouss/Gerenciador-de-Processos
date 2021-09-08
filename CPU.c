#include "CPU.h"

void inicializaCPU(CPU* cpu) {
    cpu->unidadeTempo = 0;
}

void insereProcessoCPU(CPU* cpu, ProcessoSimulado p) {
    cpu->processo = p;
}

/**Chamada pelo comando U */
void executaProcessoCPU(CPU* cpu) {
    cpu->unidadeTempo++;
    // Deve executar a próxima instrução do processo
}

void pararProcessoCPU(CPU* cpu, ProcessoSimulado* p) {
    *p = cpu->processo;
}