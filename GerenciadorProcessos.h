#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include "ListaEncadeada.h"
#include "CPU.h"
#include "ProcessoSimulado.h"

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

void comandoL(GerenciadorProcessos *gProc);

void trocaContexto(GerenciadorProcessos *gProc);

#endif