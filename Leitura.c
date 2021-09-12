#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Leitura.h"
#include "Instrucao.h"

/** Lê instruções do processo controle para gerenciador de processos
 * por meio do terminal
 */
void lerTerminal(Pipe *p) {
    printf("\nInstruções PIPE");
    inicializarPipe(p);
    char c=' ';
    while(c != 'M') {
        scanf(" %c", &c);
        escreverPipe(p, c);
    }
}

/** Lê instruções do processo controle para gerenciador de processos
 * por meio de arquivo
 */
void lerArquivo(Pipe *p) {
    FILE *arq;
    char c;
    char nomeDoArquivo[50];

    inicializarPipe(p);

    printf("\nInstruções PIPE");
    printf("\nNome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    nomeDoArquivo[strlen(nomeDoArquivo)] = '\0';

    arq = fopen(nomeDoArquivo, "r");
    if(arq == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    while(!feof(arq)){
        fscanf(arq, "%c", &c); // Lê linha
        escreverPipe(p, c);
        c = fgetc(arq); // Pega quebra de linha
    }

}

/** Lê instruções de um processo simulado
 * por meio de arquivo
 */
void lerArquivoDeInstrucoesPS(Instrucao **instrucoes) {
    FILE *arq;
    char c;
    (*instrucoes) = (Instrucao*)malloc(1000* sizeof(Instrucao)); //Maximo de 1000 instrucoes pra reduzir trabalho
    int posInstr = 0;          //Qual a linha da instrucao (Max 1000 linhas);

    char nomeDoArquivo[50];

    printf("\nInstruções Processo Simulado");
    printf("\nNome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    nomeDoArquivo[strlen(nomeDoArquivo)] = '\0';

    arq = fopen(nomeDoArquivo, "r");
    if(arq == NULL){
        printf("Arquivo não encontrado.\n");
        return;
    }

    while(!feof(arq)){
        c = fgetc(arq);
        (*instrucoes)[posInstr].i = c;
        if(c=='N' || c=='D' || c=='F') {
            fscanf(arq, "%d", &(*instrucoes)[posInstr].n1);
        } else if(c=='V' || c=='A' || c=='S') {
            fscanf(arq, "%d %d", &(*instrucoes)[posInstr].n1, &(*instrucoes)[posInstr].n2);
        } else if(c=='R') {
            fscanf(arq, "%s", (*instrucoes)[posInstr].arq);
        }
        ++posInstr;
        c = fgetc(arq);
    }
    /*
    int i;
    for(i=0;i<30;i++) {
        printf("Instrucao %d\n", i);
        printf("Char i: %c\n", instrucoes[i].i);
        printf("Integer 1: %d\n", instrucoes[i].n1);
        printf("Integer 2: %d\n", instrucoes[i].n2);
        printf("Num: %d\n", instrucoes[i].num);
        printf("Arquivo: %s\n\n", instrucoes[i].arq);
    }*/
}

void lerArquivoPS(Instrucao *instrucoes, char nomeDoArquivo[50]) {
    FILE *arq;
    char c;
    instrucoes = (Instrucao*)malloc(1000* sizeof(Instrucao)); //Maximo de 1000 instrucoes pra reduzir trabalho
    int posInstr = 0;          //Qual a linha da instrucao (Max 1000 linhas);

    nomeDoArquivo[strlen(nomeDoArquivo)] = '\0';

    arq = fopen(nomeDoArquivo, "r");
    if(arq == NULL){
        printf("Arquivo não encontrado.\n");
        return;
    }

    while(!feof(arq)){
        c = fgetc(arq);
        instrucoes[posInstr].i = c;
        if(c=='N' || c=='D' || c=='F') {
            fscanf(arq, "%d", &instrucoes[posInstr].n1);
        } else if(c=='V' || c=='A' || c=='S') {
            fscanf(arq, "%d %d", &instrucoes[posInstr].n1, &instrucoes[posInstr].n2);
        } else if(c=='R') {
            fscanf(arq, "%s", instrucoes[posInstr].arq);
        }
        ++posInstr;
        c = fgetc(arq);
    }

}