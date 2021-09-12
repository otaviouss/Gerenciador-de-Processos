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
int lerArquivo(Pipe *p) {
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
        return -1;
    }

    while(!feof(arq)){
        fscanf(arq, "%c", &c); // Lê linha
        escreverPipe(p, c);
        c = fgetc(arq); // Pega quebra de linha
    }
    return 1;

}

/** Lê instruções de um processo simulado
 * por meio de arquivo
 */
int lerArquivoDeInstrucoesPS(Instrucao **instrucoes) {
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
        return -1;
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
    return 1;
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