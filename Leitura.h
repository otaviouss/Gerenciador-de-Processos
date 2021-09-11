#ifndef LEITURA_H
#define LEITURA_H

#include "Pipe.h"
#include "Instrucao.h"

void lerTerminal(Pipe *p);

void lerArquivo(Pipe *p);

void lerArquivoDeInstrucoesPS(Instrucao *inst);

void lerArquivoPS(Instrucao *instrucoes, char nomeDoArquivo[50]); // Ler arquivo passando nome

#endif