#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

pNodoABP *InsereArvore(pNodoABP *a, tipoinfo ch) {
    if (a == NULL) {
        a = (pNodoABP *) malloc(sizeof(pNodoABP));
        a->info = ch;
        a->esq  = NULL;
        a->dir  = NULL;
        return a;
    } else if (ch < a->info)
        a->esq = InsereArvore(a->esq, ch);
    else if (ch > a->info)
        a->dir = InsereArvore(a->dir, ch);
    return a;
}

void preFixadoE(pNodoABP *a) {
    if (a != NULL) {
        printf("%d - ", a->info);
        preFixadoE(a->esq);
        preFixadoE(a->dir);
    }
}

void preFixadoD(pNodoABP *a) {
    if (a != NULL) {
        printf("%d - ", a->info);
        preFixadoD(a->dir);
        preFixadoD(a->esq);
    }
}

void posFixadoE(pNodoABP *a) {
    if (a != NULL) {
        posFixadoE(a->esq);
        posFixadoE(a->dir);
        printf("%d - ", a->info);
    }
}

void posFixadoD(pNodoABP *a) {
    if (a != NULL) {
        posFixadoD(a->dir);
        posFixadoD(a->esq);
        printf("%d - ", a->info);
    }
}

void CentralE(pNodoABP *a) {
    if (a != NULL) {
        CentralE(a->esq);
        printf("%d - ", a->info);
        CentralE(a->dir);
    }
}

void CentralD(pNodoABP *a) {
    if (a != NULL) {
        CentralD(a->dir);
        printf("%d - ", a->info);
        CentralD(a->esq);
    }
}

pNodoABP *consultaABP2(pNodoABP *a, tipoinfo chave) {
    if (a != NULL) {
        if (a->info == chave)
            return a;
        else if (a->info > chave)
            return consultaABP2(a->esq, chave);
        else
            return consultaABP2(a->dir, chave);
    } else return NULL;
}
