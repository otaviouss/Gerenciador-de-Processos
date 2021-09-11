#include <stdio.h>
#include <stdlib.h>

#include "ListaEncadeada.h"

void FLVazia(Lista* lista) {
    lista->pPrimeiro = (Apontador) malloc(sizeof(Celula));
    lista->pUltimo = lista->pPrimeiro;
    lista->pPrimeiro->pProx = NULL;
}

int LehVazia(Lista* lista) {
    return(lista->pPrimeiro == lista->pUltimo);
}

void InsereIndice(Lista* lista, int indice, int p) {
    Celula *atual, *prox;
    atual = lista->pPrimeiro->pProx; 
    while (atual->pProx->prioridade <= p) {
        atual = atual->pProx;
    }

    if(atual == lista->pUltimo) {
        lista->pUltimo->pProx = (Apontador) malloc(sizeof(Celula));
        lista->pUltimo = lista->pUltimo->pProx;
        lista->pUltimo->indiceProcesso = indice;
        lista->pUltimo->prioridade = p;
        lista->pUltimo->pProx = NULL;
    } else {
        prox = atual->pProx;
        atual->pProx = (Apontador) malloc(sizeof(Celula));
        atual = atual->pProx;
        atual->pProx = prox;
        atual->indiceProcesso = indice;
        atual->prioridade = p;
    }

}

int RetiraIndice(Lista* lista, int* indice) {
    Apontador pAux;
    if(LehVazia(lista)) return 0;

    *indice = lista->pPrimeiro->pProx->indiceProcesso;
    pAux = lista->pPrimeiro;
    lista->pPrimeiro = lista->pPrimeiro->pProx;
    free(pAux);
    return 1;
}

void ImprimeLista(Lista* lista) {
    Apontador pAux;
    pAux = lista->pPrimeiro->pProx;
    while(pAux != NULL) {
        printf("%d ", pAux->indiceProcesso);
        pAux = pAux->pProx;
    }
}