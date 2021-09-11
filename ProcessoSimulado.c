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
}

void executaProximaInstrucao(ProcessoSimulado* proc) {
    Instrucao inst = proc->programa[proc->contadorPrograma]; // Pega a próxima instrucao
    printf("Instrução Atual: %c\n", inst.i);
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
        
        ++proc->contadorPrograma;
    } else if(inst.i == 'T') {
        
        ++proc->contadorPrograma;
    } else if(inst.i == 'F') {
        
    } else if(inst.i == 'R') {
        instrucaoR(proc, inst);
    }
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

// Incompleta -> Resulta em troca de contexto
void instrucaoB(ProcessoSimulado* proc){
    //0 - bloqueado
    //1 - pronto
    //2 - em execucao
    //3 - morto
    proc->estado = 0;
}

// Incompleta -> Resulta em troca de contexto
void instrucaoT(ProcessoSimulado* proc){
    proc->estado = 3;
    mostrarRelatorioProcesso(proc);
}

// Incorreta (Usar fork)
void instrucaoF(ProcessoSimulado* proc, ProcessoSimulado *procCopia, int n){
    /*
    procCopia->tempoCPU = proc->tempoCPU;
    procCopia->idProcesso = geraIdProcesso(&n);
    procCopia->estado = proc->estado;
    procCopia->programa = procCopia->programa; //n tenho ctz se funciona
    procCopia->buffer = proc->buffer;
    procCopia->contadorPrograma = proc->contadorPrograma+1; //prox instr do pai
    procCopia->idProcessoPai = proc->idProcesso;
    procCopia->prioridade = proc->prioridade;
    procCopia->tempoIncio = proc->tempoIncio;
    */
}

void instrucaoR(ProcessoSimulado* proc, Instrucao inst){
    free(proc->programa);
    free(proc->buffer);
    lerArquivoPS(proc->programa, inst.arq);
    proc->contadorPrograma = 0;
    // Caso necessário pode executar a primeira instrução aqui chamando executaProximaInstrucao()
}

void mostrarRelatorioProcesso(ProcessoSimulado *proc){
    printf("----- Relatorio Processo -----\n");
    printf("PID: %d\n", proc->idProcesso);
    printf("Tempo em CPU: %d\n", proc->tempoCPU);
    printf("-------------------------------\n\n");
}

void incrementaTempo(ProcessoSimulado *proc) {
    proc->tempoCPU++;
}