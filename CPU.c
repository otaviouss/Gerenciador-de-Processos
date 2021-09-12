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
    cpu->unidadeTempo++;
    if(cpu->processo.idProcesso == -1) return ' ';

    char ret;
    ret = executaProximaInstrucao(&cpu->processo);
    if(ret != ' ') {
        return ret;
    }
    incrementaTempo(&cpu->processo);
    return ' ';
}

void pararProcessoCPU(CPU *cpu, ProcessoSimulado *p) {
    *p = cpu->processo;
    cpu->processo.idProcesso = -1;
}

void mostrarProcessoCPU(CPU *cpu) {
    if(cpu->processo.idProcesso == -1) {
        printf("\n--- CPU vazia! --- \n");
        printf("Tempo Total: %d\n", cpu->unidadeTempo);
        return;
    }
    printf("----- Relatorio Processo atualmente em execução -----\n");
    printf("PID: %d\n", cpu->processo.idProcesso);
    printf("Tempo em CPU: %d\n", cpu->processo.tempoCPU);
    printf("Prioridade: %d\n", cpu->processo.prioridade);
    printf("-----------------------------------------------------\n\n");
    printf("Tempo Total: %d\n\n", cpu->unidadeTempo);
}

void alteraContadorPrograma(CPU *cpu) {
    cpu->processo.contadorPrograma += cpu->processo.programa[cpu->processo.contadorPrograma].n1 + 1;
}