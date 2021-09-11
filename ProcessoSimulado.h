#ifndef PROCESSOSIMULADO_H
#define PROCESSOSIMULADO_H

#include "Instrucao.h"

typedef struct {
    int idProcesso;
    int idProcessoPai;
    int contadorPrograma; // Próxima instrucao a ser executada
    int *buffer; // Memória
    int prioridade;
    int estado;
    int tempoIncio;
    int tempoCPU;
    Instrucao* programa; // Instruções a serem executadas
} ProcessoSimulado;

void InicializaProcessoSimulado(ProcessoSimulado* proc, int idProcesso, int idProcessoPai,
    int contadorPrograma, int *buffer, int prioridade, int estado, 
    int tempoIncio, int tempoCPU, Instrucao* programa);

char executaProximaInstrucao(ProcessoSimulado* proc);

void instrucaoA(ProcessoSimulado* proc, Instrucao inst);

void instrucaoB(ProcessoSimulado* proc);

void instrucaoD(ProcessoSimulado* proc, Instrucao inst);

void instrucaoF(ProcessoSimulado* proc, ProcessoSimulado *procCopia, int n);

void instrucaoN(ProcessoSimulado* proc, Instrucao inst);

void instrucaoR(ProcessoSimulado* proc, Instrucao inst);

void instrucaoS(ProcessoSimulado* proc, Instrucao inst);

void instrucaoT(ProcessoSimulado* proc);

void instrucaoV(ProcessoSimulado* proc, Instrucao inst);

void finalizarProcesso(ProcessoSimulado* proc);

void mostrarRelatorioProcesso(ProcessoSimulado *proc);

void incrementaTempo(ProcessoSimulado *proc);

#endif