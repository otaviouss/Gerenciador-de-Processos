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
    int indice; // ultimo indice utilizado
} GerenciadorProcessos;

void inicializaGerenciador(GerenciadorProcessos *gProc);

void executaGerenciador(GerenciadorProcessos *gProc, Pipe *p);

void executarProcessoSimulado(GerenciadorProcessos *gProc, char *instPipe);

void comandoL(GerenciadorProcessos *gProc);

void comandoB(GerenciadorProcessos *gProc);

int trocaContexto(GerenciadorProcessos *gProc);

void escalonarProcessos(GerenciadorProcessos *gProc);

void processoImpressao(GerenciadorProcessos *gProc);

void insereProgramaNoProcessoSimulado(Instrucao *instProcess, Instrucao *ins);

void retiraProcessoTabelaProcessos(GerenciadorProcessos *gProc, int indice);

#endif