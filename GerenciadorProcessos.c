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
}

void executaGerenciador(GerenciadorProcessos *gProc, Pipe *p) {
    ProcessoSimulado processo;
    Instrucao *inst;
    int *buffer;
    CPU cpu;
    char *instPipe;

    printf("\nCriando Processo Simulado...\n");

    lerArquivoDeInstrucoesPS(&inst);

    InicializaProcessoSimulado(&processo, 0, -1, 0, buffer, 0, 2, 0, 0, inst);
    gProc->tabelaDeProcessos[gProc->ult] = processo;
    gProc->ult++;
    inicializaCPU(&cpu);
    insereProcessoCPU(&cpu, processo);
    gProc->estadoExecucao = 0;

    lerPipe(p, &instPipe);
  
    executarProcessoSimulado(gProc, instPipe, 0, &cpu);

}

void executarProcessoSimulado(GerenciadorProcessos *gProc, char *instPipe, int indiceInst, CPU *cpu) {
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
            res = executaProcessoCPU(cpu);

            if(res=='B') {
                comandoB(gProc);
                continue;
            } else if(res=='T') {
                pararProcessoCPU(cpu, &p);
                retiraProcessoTabelaProcessos(gProc, gProc->estadoExecucao);
                RetiraIndice(&gProc->estadoPronto, &ind);
                insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
                gProc->estadoExecucao = ind;
            } else {
                escalonarProcessos(gProc);
            }
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
    InsereIndice(&gProc->estadoPronto, i, gProc->tabelaDeProcessos[i].prioridade);
}

void comandoB(GerenciadorProcessos *gProc) {
    ProcessoSimulado *p;
    int i;
    pararProcessoCPU(&gProc->cpu, p);
    if(p != NULL) {
        gProc->tabelaDeProcessos[gProc->estadoExecucao] = *p;
        InsereIndice(&gProc->estadoBloqueado, gProc->estadoExecucao, gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade);
        gProc->estadoExecucao = -1;
    }
    RetiraIndice(&gProc->estadoPronto, &i);
    insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
    gProc->estadoExecucao = i;
}

/** Troca de contexto envolve copiar o estado do processo simulado, atualmente em execução, 
 * de Cpu para TabelaDeProcessos (a não ser que esse processo tenha completado a sua execução)
 * e copiar o estado do recém escalonado processo simulado de TabelaDeProcessos para Cpu.
*/
void trocaContexto(GerenciadorProcessos *gProc) {
    
}

void escalonarProcessos(GerenciadorProcessos *gProc) {
    int i;
    if(gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade == 0) {
        gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade = 1;
        trocaContexto(gProc);
    } else if(gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade == 1 && gProc->tabelaDeProcessos[gProc->estadoExecucao].tempoCPU == 3) {
        gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade = 2;
        trocaContexto(gProc);
    } else if(gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade == 2 && gProc->tabelaDeProcessos[gProc->estadoExecucao].tempoCPU == 7) {
        gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade = 3;
        trocaContexto(gProc);
    } else if(gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade == 3) {
        trocaContexto(gProc);
    }
}

/** Inicia o processo impressão do máximo de informações possível
*/
void processoImpressao(GerenciadorProcessos *gProc) {
    
}

void retiraProcessoTabelaProcessos(GerenciadorProcessos *gProc, int indice) {
    ProcessoSimulado p;
    while(indice<99) {
        gProc->tabelaDeProcessos[indice] = gProc->tabelaDeProcessos[indice+1];
        indice++;
    }
    gProc->tabelaDeProcessos[99] = p;
}