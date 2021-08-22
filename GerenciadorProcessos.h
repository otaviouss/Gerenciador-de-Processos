#include <ListaEncadeada.h>
#include <CPU.h>
#include <ProcessoSimulado.h>

typedef struct {
    int tempo;
    CPU cpu;
    ProcessoSimulado* tabelaDeProcessos;
    Lista estadoPronto;
    Lista estadoBloqueado;
    int estadoExecucao;
} GerenciadorProcessos;

void inicializaGerenciador(GerenciadorProcessos *gProc);

void comandoL();

void trocaContexto(GerenciadorProcessos *gProc);
