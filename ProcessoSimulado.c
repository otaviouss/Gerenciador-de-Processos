#include "ProcessoSimulado.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    
}

void instrucaoA(ProcessoSimulado* proc, Instrucao *ins){
    proc->programa->n1 += ins->n1;
}

void instrucaoB(ProcessoSimulado* proc){
    //0 - bloqueado
    //1 - pronto
    //2 - em execucao
    //3 - morto
    proc->estado = 0;
}

void instrucaoD(ProcessoSimulado* proc, Instrucao ins){
    proc->buffer = (int*) malloc(ins.n1*sizeof(int));
}

void instrucaoF(ProcessoSimulado* proc, ProcessoSimulado *procCopia, int n){
    procCopia->tempoCPU = proc->tempoCPU;
    procCopia->idProcesso = geraIdProcesso(&n);
    procCopia->estado = proc->estado;
    procCopia->programa = procCopia->programa; //n tenho ctz se funciona
    procCopia->buffer = proc->buffer;
    procCopia->contadorPrograma = proc->contadorPrograma+1; //prox instr do pai
    procCopia->idProcessoPai = proc->idProcesso;
    procCopia->prioridade = proc->prioridade;
    procCopia->tempoIncio = proc->tempoIncio;

}

int instrucaoN(Instrucao *ins){
    return ins->n1;
}

void instrucaoR(ProcessoSimulado* proc, Instrucao instr){
    proc->programa->num = instr.num;
    proc->programa->n1 = instr.n1;
    strcpy(proc->programa->arq, instr.arq);
    proc->programa->i = instr.i;
    proc->programa->n2 = instr.n2;
}

void instrucaoS(ProcessoSimulado* proc, Instrucao ins){
    proc->programa->n1 -= ins.n1;
}

void instrucaoT(ProcessoSimulado* proc){
    proc->estado = 3;
    mostrarRelatorioProcesso(proc);
}

void instrucaoV(ProcessoSimulado* proc, Instrucao ins){
    proc->programa->n1 = ins.n1;
}

void mostrarRelatorioProcesso(ProcessoSimulado *proc){
    printf("----- Processo Finalizado -----\n");
    printf("PID: &d\n", proc->idProcesso);
    printf("Tempo em CPU: &d\n", proc->tempoCPU);
    printf("-------------------------------\n\n");
}

int geraIdProcesso(int *n){
    return *n++;
}

