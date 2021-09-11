#include "CPU.h"
#include "GerenciadorProcessos.h"

void inicializaCPU(CPU *cpu) {
    cpu->unidadeTempo = 0;
}

void insereProcessoCPU(CPU *cpu, ProcessoSimulado p) {
    cpu->processo = p;
}

/** Chamada pelo comando U 
 * Executa próxima instrução do processo simulado
*/
void executaProcessoCPU(CPU *cpu) {
    executaProximaInstrucao(&cpu->processo);
    incrementaTempo(&cpu->processo);
    cpu->unidadeTempo++;
}

void pararProcessoCPU(CPU *cpu, ProcessoSimulado *p) {
    *p = cpu->processo;
}