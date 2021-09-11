#include "ProcessoSimulado.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void InicializaProcessoSimulado(ProcessoSimulado* proc, int idProcesso, int idProcessoPai,
    int contadorPrograma, int *buffer, int prioridade, int estado, 
    int tempoIncio, int tempoCPU, Instrucao* programa) {
        proc->buffer = buffer;
        proc->contadorPrograma = contadorPrograma;
        proc->estado = estado;
        proc->idProcesso = idProcesso;
        proc->idProcessoPai = idProcessoPai;
        proc->prioridade = prioridade;
        proc->programa = programa;
        proc->tempoCPU = tempoCPU;
        proc->tempoIncio = tempoIncio;
}

void executaProximaInstrucao(ProcessoSimulado* proc) {
    
}

void instrucaoA(ProcessoSimulado* proc, Instrucao *ins){
    proc->programa->n1 += ins->n1;
}

void instrucaoB(ProcessoSimulado* proc){
    //0 - bloqueado
    //1 - pronto
    //2 - em execucao
    //3 - morto
    proc->estado = 0;
}

void instrucaoD(ProcessoSimulado* proc, Instrucao ins){
    proc->buffer = (int*) malloc(ins.n1*sizeof(int));
}

void instrucaoF(ProcessoSimulado* proc, ProcessoSimulado *procCopia, int n){
    procCopia->tempoCPU = proc->tempoCPU;
    procCopia->idProcesso = geraIdProcesso(&n);
    procCopia->estado = proc->estado;
    procCopia->programa = procCopia->programa; //n tenho ctz se funciona
    procCopia->buffer = proc->buffer;
    procCopia->contadorPrograma = proc->contadorPrograma+1; //prox instr do pai
    procCopia->idProcessoPai = proc->idProcesso;
    procCopia->prioridade = proc->prioridade;
    procCopia->tempoIncio = proc->tempoIncio;

}

int instrucaoN(Instrucao *ins){
    return ins->n1;
}

void instrucaoR(ProcessoSimulado* proc, Instrucao instr){
    proc->programa->num = instr.num;
    proc->programa->n1 = instr.n1;
    strcpy(proc->programa->arq, instr.arq);
    proc->programa->i = instr.i;
    proc->programa->n2 = instr.n2;
}

void instrucaoS(ProcessoSimulado* proc, Instrucao ins){
    proc->programa->n1 -= ins.n1;
}

void instrucaoT(ProcessoSimulado* proc){
    proc->estado = 3;
    mostrarRelatorioProcesso(proc);
}

void instrucaoV(ProcessoSimulado* proc, Instrucao ins){
    proc->programa->n1 = ins.n1;
}

void mostrarRelatorioProcesso(ProcessoSimulado *proc){
    printf("----- Processo Finalizado -----\n");
    printf("PID: %d\n", proc->idProcesso);
    printf("Tempo em CPU: %d\n", proc->tempoCPU);
    printf("-------------------------------\n\n");
}

int geraIdProcesso(int *n){
    return *n++;
}

Instrucao* leArquivoDeInstrucoesPS(){
    FILE *arq;
    char c;
    Instrucao *instrucoes = (Instrucao*)malloc(100* sizeof(Instrucao)); //Maximo de 100 instrucoes pra reduzir trabalho
    int posInstr = 0;          //Qual a linha da instrucao (Max 100 linhas);


    /*Qual o parametro que e: V(0) 0(1) 1000(2)
     * 0 - i
     * 1 - n1
     * 2 - n2
    */
    int numeroParametro = 0;

    char nomeDoArquivo[50];

    printf("\nNome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    nomeDoArquivo[strlen(nomeDoArquivo)] = '\0';

    arq = fopen(nomeDoArquivo, "r");
    if(arq == NULL){
        printf("Arquivo não encontrado.\n");
        return NULL;
    }

    while(1){
        c = fgetc(arq);

        if(c == 32) { //Se for espaco, e o pro proximo parametro
            numeroParametro++;
            c = fgetc(arq);

        }else if (c == '\n') { //Se for quebra de linha, e a proxima instrucao
            posInstr++;
            numeroParametro = 0;
            c = fgetc(arq);

        }else if(c == EOF){
            break;
        }

        switch (numeroParametro){

            case 0:{
                instrucoes[posInstr].i = c;
                break;
            }

            case 1:{

                if(instrucoes[posInstr].i != 'R'){
                    instrucoes[posInstr].n1 = c;

                }else{ //Se a instrucao for R entao tem que ler o nome do arquivo

                    int cont = 0; //posicao de cada caracter
                    while(1){
                        c = fgetc(arq);
                        if(c == '\n' || c == EOF){
                            break;
                        }
                        instrucoes[posInstr].arq[cont] = c;
                        cont++;
                    }
                }

                break;
            }

            case 2:{
                instrucoes[posInstr].n2 = (int)c;
                break;
            }

        }
    }

    return instrucoes;

}

