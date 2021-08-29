#ifndef PROCESSOSIMULADO_H
#define PROCESSOSIMULADO_H

#include "Instrucao.h"

typedef struct {
    int idProcesso;
    int idProcessoPai;
    int contadorPrograma;
    int *buffer;
    int prioridade;
    int estado;
    int tempoIncio;
    int tempoCPU;
    Instrucao* programa;
} ProcessoSimulado;

void InicializaProcessoSimulado(ProcessoSimulado* proc);

void instrucaoA(ProcessoSimulado* proc, Instrucao *ins);

void instrucaoB(ProcessoSimulado* proc);

void instrucaoD(ProcessoSimulado* proc, Instrucao ins);

void instrucaoF(ProcessoSimulado* proc, ProcessoSimulado *procCopia, int n);

int instrucaoN(Instrucao *ins);

void instrucaoR(ProcessoSimulado* proc);

void instrucaoS(ProcessoSimulado* proc, Instrucao ins);

void instrucaoT(ProcessoSimulado* proc);

void instrucaoV(ProcessoSimulado* proc, Instrucao ins);

void finalizarProcesso(ProcessoSimulado* proc);

void mostrarRelatorioProcesso(ProcessoSimulado *proc);

int geraIdProcesso(int *n);
#endif