#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ProcessoSimulado.h"
#include "Leitura.h"

void InicializaProcessoSimulado(ProcessoSimulado* proc, int idProcesso, int idProcessoPai,
    int contadorPrograma, int *buffer, int prioridade, int estado, 
    int tempoIncio, int tempoCPU, Instrucao* programa) {
        proc->buffer = buffer;
        proc->contadorPrograma = contadorPrograma;
        proc->estado = estado;
        proc->idProcesso = idProcesso;
        proc->idProcessoPai = idProcessoPai;
        proc->prioridade = prioridade;
        proc->programa = programa;
        proc->tempoCPU = tempoCPU;
        proc->tempoIncio = tempoIncio;
        proc->tempoAtualCPU = 0;
}

char executaProximaInstrucao(ProcessoSimulado* proc) {
    Instrucao inst = proc->programa[proc->contadorPrograma]; // Pega a próxima instrucao
    printf("%d %d Instrução Atual: %c\n", proc->idProcesso, proc->prioridade, inst.i);
    if(inst.i == 'N') {
        instrucaoN(proc, inst);
        ++proc->contadorPrograma;
    } else if(inst.i == 'D') {
        instrucaoD(proc, inst);
        ++proc->contadorPrograma;
    } else if(inst.i == 'V') {
        instrucaoV(proc, inst);        
        ++proc->contadorPrograma;
    } else if(inst.i == 'A') {
        instrucaoA(proc, inst);        
        ++proc->contadorPrograma;
    } else if(inst.i == 'S') {
        instrucaoS(proc, inst);        
        ++proc->contadorPrograma;
    } else if(inst.i == 'B') {
        instrucaoB(proc);
        ++proc->contadorPrograma;
        return 'B';
    } else if(inst.i == 'T') {
        instrucaoT(proc);
        ++proc->contadorPrograma;
        return 'T';
    } else if(inst.i == 'F') {
        return 'F';
    } else if(inst.i == 'R') {
        instrucaoR(proc, inst);
    }
    return ' ';
}

void instrucaoN(ProcessoSimulado* proc, Instrucao inst) {
    proc->buffer = (int*) malloc(sizeof(int) * inst.n1);
}

void instrucaoD(ProcessoSimulado* proc, Instrucao inst){
    proc->buffer[inst.n1] = 0;
}

void instrucaoV(ProcessoSimulado* proc, Instrucao inst){
    proc->buffer[inst.n1] = inst.n2;
}

void instrucaoA(ProcessoSimulado* proc, Instrucao inst){
    proc->buffer[inst.n1] += inst.n2;
}

void instrucaoS(ProcessoSimulado* proc, Instrucao inst){
    proc->buffer[inst.n1] -= inst.n2;
}

void instrucaoB(ProcessoSimulado* proc){
    //0 - bloqueado
    //1 - pronto
    //2 - em execucao
    //3 - morto
    proc->estado = 0;
}

void instrucaoT(ProcessoSimulado* proc){
    proc->estado = 3;
    mostrarRelatorioProcesso(proc);
}

void instrucaoR(ProcessoSimulado* proc, Instrucao inst){
    free(proc->programa);
    lerArquivoPS(proc->programa, inst.arq);
    proc->contadorPrograma = 0;
    // Caso necessário pode executar a primeira instrução aqui chamando executaProximaInstrucao()
}

void mostrarRelatorioProcesso(ProcessoSimulado *proc){
    printf("----- Relatorio Processo -----\n");
    printf("PID: %d\n", proc->idProcesso);
    printf("Prioridade: %d\n", proc->prioridade);
    printf("ID Processo pai: %d\n", proc->idProcessoPai);
    printf("Contador de programa: %d\n", proc->contadorPrograma);

    //0 - bloqueado
    //1 - pronto
    //2 - em execucao
    //3 - morto

    printf("Estado: ");
    switch (proc->estado){
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
    printf("Tempo de inicio: %d\n", proc->tempoIncio);
    printf("Tempo em proc: %d\n", proc->tempoCPU + proc->tempoAtualCPU);
    printf("-------------------------------\n\n");
}

void incrementaTempo(ProcessoSimulado *proc) {
    proc->tempoAtualCPU++;
}