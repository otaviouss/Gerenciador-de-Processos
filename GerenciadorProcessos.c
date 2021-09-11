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
    char *instPipe;
    int *buffer, i;
    size_t tam;
    CPU cpu;

    printf("Criando Processo Simulado...");

    lerArquivoDeInstrucoesPS(&inst);

    InicializaProcessoSimulado(&processo, 0, -1, 0, buffer, 0, 2, 0, 0, inst);
    gProc->tabelaDeProcessos[gProc->ult] = processo;
    gProc->ult++;
    inicializaCPU(&cpu);
    insereProcessoCPU(&cpu, processo);
    gProc->estadoExecucao = 0;

    lerPipe(p, &instPipe);

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
           executaProcessoCPU(&cpu);
           escalonarProcessos(gProc);
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

/** Inicia o processo impressão do máximo de informações possível
*/
void processoImpressao(GerenciadorProcessos *gProc) {
    
}