#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

typedef struct Celula* Apontador;

typedef struct Celula {
    int indiceProcesso;
    int prioridade;
    struct Celula* pProx;
} Celula;

typedef struct {
    Apontador pPrimeiro;
    Apontador pUltimo;
} Lista;

void FLVazia(Lista* lista);

int LehVazia(Lista* lista);

void InsereIndiceOrdenado(Lista *lista, int indice, int p);

void InsereIndiceFIFO(Lista* lista, int indice, int p);

int RetiraIndice(Lista* lista, int* indice);

void ImprimeIndices(Lista* lista);

void AtualizaIndices(Lista *lista, int indice);

#endif