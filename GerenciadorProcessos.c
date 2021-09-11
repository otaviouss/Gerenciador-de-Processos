#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GerenciadorProcessos.h"
#include "ProcessoSimulado.h"
#include "Instrucao.h"

void inicializaGerenciador(GerenciadorProcessos *gProc) {
    ProcessoSimulado *processos, p;
    CPU cpu;
    Lista listaPronto, listaBloqueado;

    processos = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado)*100);

    inicializaCPU(&cpu);
    FLVazia(&listaPronto);
    FLVazia(&listaBloqueado);

    gProc->tempo = 0;
    gProc->cpu = cpu;
    gProc->tabelaDeProcessos = processos;
    gProc->estadoPronto = listaPronto;
    gProc->estadoBloqueado = listaBloqueado;
    gProc->estadoExecucao = -1;
    gProc->ult = 1;
}

void executaGerenciador(GerenciadorProcessos *gProc, Pipe *p) {
    ProcessoSimulado processo; //colocar as intruções aqui
    Instrucao *inst; //duplicar as instruições aqui
    char *instPipe;
    int *buffer, tam, i;

    // inst é o vetor que deve armazenar as instruções do processo simulado

    buffer = (int*) malloc(sizeof(int)*100);
    InicializaProcessoSimulado(&processo, 0, -1, 0, buffer, 0, 2, 0, 0, inst);
    gProc->tabelaDeProcessos[0] = processo;

    lerPipe(p, instPipe);

    tam = strlen(instPipe);
    for(i=0; i<tam; i++) {
        if(instPipe[i]=='U') {
            /* Ao receber um comando U, o gerenciador
                executa a próxima instrução do processo
                simulado atualmente em execução, incrementa
                o valor do contador de programa (exceto para
                instruções F ou R), incrementa Tempo e depois
                faz o escalonamento. O escalonamento pode
                envolver troca de contexto
            */
        } else if(instPipe[i]=='L') {
            // Executa comando L
            comandoL(gProc);
        } else if(instPipe[i]=='I') {
            // Executa processo Impressão
            processoImpressao(gProc);
        } else if(instPipe[i]=='M') {
            // Executa impressão e termina
            processoImpressao(gProc);
            return;
        }
    }
    
    
}

/** Ao receber um comando L, gerenciador de processos move o primeiro
 * processo simulado da fila bloqueada para a fila de estado pronto para executar.
 */
void comandoL(GerenciadorProcessos *gProc) {
    int i;
    RetiraIndice(&gProc->estadoBloqueado, &i);
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

void escalonarProcessos(GerenciadorProcessos *gProc) {

}

/** Chama comando R do processo simulado
 */
void substituirImagem(GerenciadorProcessos *gProc, ProcessoSimulado *proc) {

}

/** Inicia o processo impressão do máximo de informações possível
 */
void processoImpressao(GerenciadorProcessos *gProc) {

}