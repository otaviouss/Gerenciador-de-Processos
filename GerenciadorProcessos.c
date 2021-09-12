#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GerenciadorProcessos.h"
#include "ProcessoSimulado.h"
#include "Instrucao.h"
#include "Leitura.h"
#include "CPU.h"

void inicializaGerenciador(GerenciadorProcessos *gProc) {
    gProc->tempo = 0;
    inicializaCPU(&gProc->cpu);
    gProc->tabelaDeProcessos = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado)*100);
    FLVazia(&gProc->estadoPronto);
    FLVazia(&gProc->estadoBloqueado);
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
  
    executarProcessoSimulado(gProc, instPipe);

}

void executarProcessoSimulado(GerenciadorProcessos *gProc, char *instPipe) {
    int i, ind, ret;
    char res;
    ProcessoSimulado p;

    for(i=0; i<strlen(instPipe); i++) {
        printf("%d %c ", i+1, instPipe[i]);
        //printf("Estado Pronto: ");
        //ImprimeIndices(&gProc->estadoPronto);
        //printf("\n");
        //printf("Estado Bloqueado: ");
        //ImprimeIndices(&gProc->estadoBloqueado);
        //printf("\n");
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
                retiraProcessoTabelaProcessos(gProc, gProc->estadoExecucao);
                ret = trocaContexto(gProc);
                if(ret==-1) {
                    gProc->cpu.processo.idProcesso = -1;
                }
            } else if(res=='F') {
                // Cria novo processo
                ++gProc->indice;
                InicializaProcessoSimulado(&gProc->tabelaDeProcessos[gProc->ult], gProc->indice, gProc->tabelaDeProcessos[gProc->estadoExecucao].idProcesso,
                    gProc->cpu.processo.contadorPrograma + 1, gProc->cpu.processo.buffer,
                    gProc->cpu.processo.prioridade, 1, gProc->cpu.unidadeTempo, 0, gProc->cpu.processo.programa);

                alteraContadorPrograma(&gProc->cpu);
                
                InsereIndiceOrdenado(&(gProc->estadoPronto), gProc->ult, gProc->tabelaDeProcessos[gProc->ult].prioridade);

                gProc->ult++;
                escalonarProcessos(gProc);
            } else {
                escalonarProcessos(gProc);
            }
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
    int i, r;

    if(LehVazia(&gProc->estadoBloqueado)) return;

    r = RetiraIndice(&gProc->estadoBloqueado, &i);
   
    if(r == -1) return;
  
    InsereIndiceOrdenado(&gProc->estadoPronto, i, gProc->tabelaDeProcessos[i].prioridade);

}

void comandoB(GerenciadorProcessos *gProc) {
    ProcessoSimulado p;
    int i;
    pararProcessoCPU(&gProc->cpu, &p);
    gProc->tabelaDeProcessos[gProc->estadoExecucao] = p;
    InsereIndiceFIFO(&gProc->estadoBloqueado, gProc->estadoExecucao, gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade);
    gProc->estadoExecucao = -1;
    RetiraIndice(&gProc->estadoPronto, &i);
    insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
    gProc->estadoExecucao = i;
}

/** Troca de contexto envolve copiar o estado do processo simulado, atualmente em execução, 
 * de Cpu para TabelaDeProcessos (a não ser que esse processo tenha completado a sua execução)
 * e copiar o estado do recém escalonado processo simulado de TabelaDeProcessos para Cpu.
*/
int trocaContexto(GerenciadorProcessos *gProc) {
    ProcessoSimulado p;
    int i;

    if(LehVazia(&gProc->estadoPronto)) {
        return -1;
    }

    pararProcessoCPU(&gProc->cpu, &p);
    if(p.idProcesso != -1) {
        gProc->tabelaDeProcessos[gProc->estadoExecucao] = p;
        InsereIndiceOrdenado(&gProc->estadoPronto, gProc->estadoExecucao, gProc->tabelaDeProcessos[gProc->estadoExecucao].prioridade);
    }
    RetiraIndice(&gProc->estadoPronto, &i);
    insereProcessoCPU(&gProc->cpu, gProc->tabelaDeProcessos[i]);
    gProc->estadoExecucao = i;

    return 1;
}

void escalonarProcessos(GerenciadorProcessos *gProc) {
    if(gProc->cpu.processo.prioridade == 0) {
        ++gProc->cpu.processo.prioridade;
        trocaContexto(gProc);
    } else if(gProc->cpu.processo.prioridade == 1 && gProc->cpu.processo.tempoCPU > 1) {
        ++gProc->cpu.processo.prioridade;
        trocaContexto(gProc);
    } else if(gProc->cpu.processo.prioridade == 2 && gProc->cpu.processo.tempoCPU > 3) {
        ++gProc->cpu.processo.prioridade;
        trocaContexto(gProc);
    } else if(gProc->cpu.processo.prioridade == 3 && gProc->cpu.processo.tempoCPU > 7) {
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

    if(gProc->cpu.processo.idProcesso == -1) {
        mostrarProcessoCPU(&gProc->cpu);
    }
}

void retiraProcessoTabelaProcessos(GerenciadorProcessos *gProc, int indice) {
    ProcessoSimulado p;
    while(indice<99) {
        gProc->tabelaDeProcessos[indice] = gProc->tabelaDeProcessos[indice+1];
        indice++;
    }
    gProc->cpu.processo.idProcesso = -1;
    gProc->tabelaDeProcessos[99] = p;
    gProc->ult--;
}