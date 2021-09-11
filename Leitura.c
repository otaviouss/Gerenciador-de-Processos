#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Leitura.h"
#include "Instrucao.h"

/** Lê instruções do processo controle para gerenciador de processos
 * por meio do terminal
 */
void lerTerminal(Pipe *p) {
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

    printf("\nNome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    nomeDoArquivo[strlen(nomeDoArquivo)] = '\0';

    arq = fopen(nomeDoArquivo, "r");
    if(arq == NULL) {
        printf("Arquivo não encontrado.\n");
        return;
    }

    while(1){
        c = fgetc(arq);

        if (c == '\n') { //Se for quebra de linha, lê a proxima instrucao
            c = fgetc(arq);
        } else if(c == EOF){
            break;
        }

        escreverPipe(p, c);
    }

}

/** Lê instruções de um processo simulado
 * por meio de arquivo
 */
void lerArquivoDeInstrucoesPS(Instrucao *instrucoes) {
    FILE *arq;
    char c;
    instrucoes = (Instrucao*)malloc(1000* sizeof(Instrucao)); //Maximo de 1000 instrucoes pra reduzir trabalho
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
        return;
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

}

void lerArquivoPS(Instrucao *instrucoes, char nomeDoArquivo[50]) {
    FILE *arq;
    char c;
    instrucoes = (Instrucao*)malloc(1000* sizeof(Instrucao)); //Maximo de 1000 instrucoes pra reduzir trabalho
    int posInstr = 0;          //Qual a linha da instrucao (Max 100 linhas);

    /*Qual o parametro que e: V(0) 0(1) 1000(2)
     * 0 - i
     * 1 - n1
     * 2 - n2
    */
    int numeroParametro = 0;

    nomeDoArquivo[strlen(nomeDoArquivo)] = '\0';

    arq = fopen(nomeDoArquivo, "r");
    if(arq == NULL){
        printf("Arquivo não encontrado.\n");
        return;
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

}