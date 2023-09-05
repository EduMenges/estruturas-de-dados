#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

NodoABP *InsereArvoreABP(NodoABP *a, InfoNo dado) {
    /* Insere nós de maneira iterativa. */
    NodoABP *aux = a, *ant = a;

    while (aux != NULL) {
        ant = aux;

        if (dado.valor < aux->info.valor)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    aux = malloc(sizeof(NodoABP));
    aux->info = dado;
    aux->esq  = NULL;
    aux->dir  = NULL;

    if (ant == NULL)
        a = aux;
    else if (dado.valor > ant->info.valor)
        ant->dir = aux;
    else
        ant->esq = aux;

    return a;
}

NodoABP *EncontrarNodoEsquerdoABP(NodoABP *arv) {
    /* Encontra o nó inferior esquerdo de uma árvore ABP */
    while (arv->esq != NULL) {
        arv = arv->esq;
    }

    return arv;
}

void ExcluirArvoreABP(NodoABP *arv) {
    /* Este algoritmo transforma a árvore numa lista (estruturalmente falando), e libera os nós
     * conforme eles trocam de posição. */
    NodoABP *no_esquerdo, *no_antigo;

    if (arv != NULL) {
        no_esquerdo = EncontrarNodoEsquerdoABP(arv);
    }

    while (arv != NULL) {
        /* Se houver um ramo direito, este é colocado no fim do lado esquerdo da árvore, e o último nó
         * esquerdo é atualizado. */
        if (arv->dir != NULL) {
            no_esquerdo->esq = arv->dir;
            no_esquerdo = EncontrarNodoEsquerdoABP(no_esquerdo);
        }

        no_antigo = arv;
        arv       = arv->esq;
        free(no_antigo);
    }
}

void PreFixadoE(NodoABP *a) {
    if (a != NULL) {
        printf("%d - ", a->info.valor);
        PreFixadoE(a->esq);
        PreFixadoE(a->dir);
    }
}

void PreFixadoD(NodoABP *a) {
    if (a != NULL) {
        printf("%d - ", a->info.valor);
        PreFixadoD(a->dir);
        PreFixadoD(a->esq);
    }
}

void PosFixadoE(NodoABP *a) {
    if (a != NULL) {
        PosFixadoE(a->esq);
        PosFixadoE(a->dir);
        printf("%d - ", a->info.valor);
    }
}

void PosFixadoD(NodoABP *a) {
    if (a != NULL) {
        PosFixadoD(a->dir);
        PosFixadoD(a->esq);
        printf("%d - ", a->info.valor);
    }
}

void CentralE(NodoABP *a) {
    if (a != NULL) {
        CentralE(a->esq);
        printf("%d - ", a->info.valor);
        CentralE(a->dir);
    }
}

void CentralD(NodoABP *a) {
    if (a != NULL) {
        CentralD(a->dir);
        printf("%d - ", a->info.valor);
        CentralD(a->esq);
    }
}

NodoABP *ConsultaABPECompara(NodoABP *a, InfoNo chave, int *n_comparacoes) {
    // Realiza a consulta de maneira iterativa
    NodoABP *aux = a;
    int comparacoes = 0;

    while (aux != NULL && aux->info.valor != chave.valor) {
        comparacoes += 2;

        if (chave.valor > aux->info.valor) {
            aux = aux->dir;
        } else {
            aux = aux->esq;
        }

        comparacoes++;
    }

    if (aux == NULL)
        comparacoes++;
    else
        comparacoes += 2;

    *n_comparacoes = comparacoes;
    return aux;
}
