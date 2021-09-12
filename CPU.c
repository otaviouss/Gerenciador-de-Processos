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
    incrementaTempo(&cpu->processo);
    if(ret != ' ') {
        return ret;
    }
    return ' ';
}

void pararProcessoCPU(CPU *cpu, ProcessoSimulado *p) {
    cpu->processo.tempoCPU += cpu->processo.tempoAtualCPU;
    cpu->processo.tempoAtualCPU = 0;
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
    printf("Prioridade: %d\n", cpu->processo.prioridade);
    printf("ID Processo pai: %d\n", cpu->processo.idProcessoPai);
    printf("Contador de programa: %d\n", cpu->processo.contadorPrograma);

    //0 - bloqueado
    //1 - pronto
    //2 - em execucao
    //3 - morto

    printf("Estado: ");
    switch (cpu->processo.estado){
        case 0:{
            printf("Bloqueado\n");
            break;
        }

        case 1:{
            printf("Pronto\n");
            break;
        }

        case 2:{
            printf("Em execução\n");
            break;
        }

        case 3:{
            printf("Morto\n");
            break;
        }
    }
    printf("Tempo de inicio: %d\n", cpu->processo.tempoIncio);
    printf("Tempo em CPU: %d\n", cpu->processo.tempoCPU + cpu->processo.tempoAtualCPU);
    printf("-----------------------------------------------------\n\n");
    printf("Tempo Total: %d\n\n", cpu->unidadeTempo);
}

void alteraContadorPrograma(CPU *cpu) {
    cpu->processo.contadorPrograma += cpu->processo.programa[cpu->processo.contadorPrograma].n1 + 1;
}