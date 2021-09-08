#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "ListaEncadeada.h"
#include "CPU.h"
#include "ProcessoSimulado.h"
#include "Pipe.h"

typedef struct {
    int tempo;
    CPU cpu;
    ProcessoSimulado *tabelaDeProcessos;
    Lista estadoPronto;
    Lista estadoBloqueado;
    int estadoExecucao;
    int ult; // marca a posição seguinte à última posição preenchida do vetor tabelaDeProcessos
} GerenciadorProcessos;

void inicializaGerenciador(GerenciadorProcessos *gProc);

void executaGerenciador(GerenciadorProcessos *gProc, Pipe *p);

void comandoL(GerenciadorProcessos *gProc);

void trocaContexto(GerenciadorProcessos *gProc);

void escalonarProcessos(GerenciadorProcessos *gProc);

void substituirImagem(GerenciadorProcessos *gProc, ProcessoSimulado *proc);

void processoImpressao(GerenciadorProcessos *gProc);

#endif