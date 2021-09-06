#include <stdio.h>
#include <stdlib.h>

#include "GerenciadorProcessos.h"
#include "ProcessoSimulado.h"

void inicializaGerenciador(GerenciadorProcessos *gProc) {
    ProcessoSimulado *processos, p;
    CPU cpu;
    Lista listaPronto, listaBloqueado;

    processos = malloc(sizeof(ProcessoSimulado)*100);
    
    InicializaProcessoSimulado(&p, 0, NULL, 0, 0, 0, 0, 0, 0, 0);
    inicializaCPU(&cpu);
    FLVazia(&listaPronto);
    FLVazia(&listaBloqueado);

    processos[0] = p;

    gProc->tempo = 0;
    gProc->cpu = cpu;
    gProc->tabelaDeProcessos = processos;
    gProc->estadoPronto = listaPronto;
    gProc->estadoBloqueado = listaBloqueado;
    gProc->estadoExecucao = NULL;
    gProc->ult = 1;
}

/** Ao receber um comando L, gerenciador de processos move o primeiro
 * processo simulado da fila bloqueada para a fila de estado pronto para executar.
 */
void comandoL(GerenciadorProcessos *gProc) {
    int i;
    RetiraIndice(&gProc->estadoBloqueado, i);
    InsereIndice(&gProc->estadoPronto, i);
}

/** Troca de contexto envolve copiar o estado do processo simulado, atualmente em execução, 
 * de Cpu para TabelaDeProcessos (a não ser que esse processo tenha completado a sua execução)
 *  e copiar o estado do recém escalonado processo simulado de TabelaDeProcessos para Cpu.
 */
void trocaContexto(GerenciadorProcessos *gProc) {
    ProcessoSimulado *p;
    int i;
    pararProcessoCPU(&gProc->cpu, p);
    if(p != NULL) {
        gProc->tabelaDeProcessos[gProc->ult] = *p;
        gProc->ult++;
    }
    RetiraIndice(&gProc->estadoPronto, &i);
    insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
}