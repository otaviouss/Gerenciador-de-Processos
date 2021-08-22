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

void instrucaoA(ProcessoSimulado* proc);

void instrucaoB(ProcessoSimulado* proc);

void instrucaoD(ProcessoSimulado* proc);

void instrucaoF(ProcessoSimulado* proc);

void instrucaoN(ProcessoSimulado* proc);

void instrucaoR(ProcessoSimulado* proc);

void instrucaoS(ProcessoSimulado* proc);

void instrucaoT(ProcessoSimulado* proc);

void instrucaoV(ProcessoSimulado* proc);

void finalizarProcesso(ProcessoSimulado* proc);

#endif