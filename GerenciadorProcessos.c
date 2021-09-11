#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GerenciadorProcessos.h"
#include "ProcessoSimulado.h"
#include "Instrucao.h"
#include "Leitura.h"
#include "CPU.h"

void inicializaGerenciador(GerenciadorProcessos *gProc) {
    CPU cpu;
    Lista listaPronto, listaBloqueado;

    inicializaCPU(&cpu);
    FLVazia(&listaPronto);
    FLVazia(&listaBloqueado);

    gProc->tempo = 0;
    gProc->cpu = cpu;
    gProc->tabelaDeProcessos = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado)*100);
    gProc->estadoPronto = listaPronto;
    gProc->estadoBloqueado = listaBloqueado;
    gProc->estadoExecucao = -1;
    gProc->ult = 0;
    gProc->indice = 0;
}

void executaGerenciador(GerenciadorProcessos *gProc, Pipe *p) {
    ProcessoSimulado processo;
    Instrucao *inst;
    int *buffer;
    char *instPipe;

    printf("\nCriando Processo Simulado...\n");

    lerArquivoDeInstrucoesPS(&inst);

    InicializaProcessoSimulado(&processo, 0, -1, 0, buffer, 0, 2, 0, 0, inst);
    gProc->tabelaDeProcessos[gProc->ult] = processo;
    gProc->ult++;
    inicializaCPU(&gProc->cpu);
    insereProcessoCPU(&gProc->cpu, processo);
    gProc->estadoExecucao = 0;

    lerPipe(p, &instPipe);
  
    executarProcessoSimulado(gProc, instPipe, 0);

}

void executarProcessoSimulado(GerenciadorProcessos *gProc, char *instPipe, int indiceInst) {
    int i, ind;
    size_t tam;
    char res;
    ProcessoSimulado p;

    tam = strlen(instPipe);
    for(i=indiceInst; i<tam; i++) {
        if(instPipe[i]=='U') {
            /* Ao receber um comando U, o gerenciador
                executa a próxima instrução do processo
                simulado atualmente em execução, incrementa
                o valor do contador de programa (exceto para
                instruções F ou R), incrementa Tempo e depois
                faz o escalonamento. O escalonamento pode
                envolver troca de contexto
            */
            res = executaProcessoCPU(&gProc->cpu);

            if(res=='B') {
                comandoB(gProc);
                continue;
            } else if(res=='T') {
                pararProcessoCPU(&gProc->cpu, &p);
                retiraProcessoTabelaProcessos(gProc, gProc->estadoExecucao);
                RetiraIndice(&gProc->estadoPronto, &ind);
                insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
                gProc->estadoExecucao = ind;
            } else if(res=='F') {
                // Cria novo processo
                ++gProc->indice;
                InicializaProcessoSimulado(&gProc->tabelaDeProcessos[gProc->ult], gProc->indice, gProc->tabelaDeProcessos[gProc->estadoExecucao].idProcesso,
                    gProc->cpu.processo.contadorPrograma + 1, gProc->tabelaDeProcessos[gProc->estadoExecucao].buffer,
                    gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade, 1, gProc->cpu.unidadeTempo, 0, gProc->tabelaDeProcessos[gProc->estadoExecucao].programa);

                gProc->cpu.processo.contadorPrograma += gProc->cpu.processo.programa[gProc->cpu.processo.contadorPrograma].n1 + 1;

                InsereIndice(&gProc->estadoPronto, gProc->ult, gProc->tabelaDeProcessos[gProc->ult].prioridade);
                gProc->ult++;
            }
            escalonarProcessos(gProc);
        } else if(instPipe[i]=='L') {
            // Executa comando L
            comandoL(gProc);
        } else if(instPipe[i]=='I') {
            // Executa processo Impressão
            printf("\nComando I\n");
            processoImpressao(gProc);
        } else if(instPipe[i]=='M') {
            // Executa impressão e termina
            printf("\nComando M\n");
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

    if(LehVazia(&gProc->estadoBloqueado)) return;

    RetiraIndice(&gProc->estadoBloqueado, &i);
    InsereIndice(&gProc->estadoPronto, i, gProc->tabelaDeProcessos[i].prioridade);
}

void comandoB(GerenciadorProcessos *gProc) {
    ProcessoSimulado p;
    int i;
    pararProcessoCPU(&gProc->cpu, &p);
    gProc->tabelaDeProcessos[gProc->estadoExecucao] = p;
    InsereIndice(&gProc->estadoBloqueado, gProc->estadoExecucao, gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade);
    gProc->estadoExecucao = -1;
    RetiraIndice(&gProc->estadoPronto, &i);
    insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
    gProc->estadoExecucao = i;
}

/** Troca de contexto envolve copiar o estado do processo simulado, atualmente em execução, 
 * de Cpu para TabelaDeProcessos (a não ser que esse processo tenha completado a sua execução)
 * e copiar o estado do recém escalonado processo simulado de TabelaDeProcessos para Cpu.
*/
void trocaContexto(GerenciadorProcessos *gProc) {
    ProcessoSimulado p;
    int i;

    if(LehVazia(&gProc->estadoPronto)) return;

    pararProcessoCPU(&gProc->cpu, &p);
    gProc->tabelaDeProcessos[gProc->estadoExecucao] = p;
    InsereIndice(&gProc->estadoBloqueado, gProc->estadoExecucao, gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade);
    RetiraIndice(&gProc->estadoPronto, &i);
    insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
    gProc->estadoExecucao = i;
}

void escalonarProcessos(GerenciadorProcessos *gProc) {
    if(gProc->cpu.processo.prioridade == 0) {
        ++gProc->cpu.processo.prioridade;
        trocaContexto(gProc);
    } else if(gProc->cpu.processo.prioridade == 1 && gProc->cpu.processo.tempoCPU == 3) {
        ++gProc->cpu.processo.prioridade;
        trocaContexto(gProc);
    } else if(gProc->cpu.processo.prioridade == 2 && gProc->cpu.processo.tempoCPU == 7) {
        ++gProc->cpu.processo.prioridade;
        trocaContexto(gProc);
    } else if(gProc->cpu.processo.prioridade == 3) {
        trocaContexto(gProc);
    }
}

/** Inicia o processo impressão do máximo de informações possível
*/
void processoImpressao(GerenciadorProcessos *gProc) {
    int i;
    for(i=0;i<gProc->ult;i++) {
        if(i==gProc->estadoExecucao) {
            mostrarProcessoCPU(&gProc->cpu);
        } else {
            mostrarRelatorioProcesso(&gProc->tabelaDeProcessos[i]);
        }
    }
}

void retiraProcessoTabelaProcessos(GerenciadorProcessos *gProc, int indice) {
    ProcessoSimulado p;
    while(indice<99) {
        gProc->tabelaDeProcessos[indice] = gProc->tabelaDeProcessos[indice+1];
        indice++;
    }
    gProc->tabelaDeProcessos[99] = p;
    gProc->ult--;
}