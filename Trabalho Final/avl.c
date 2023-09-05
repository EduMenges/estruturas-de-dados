#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int Altura(NodoAVL *a) {
    int alt_esq, alt_dir;

    if (a == NULL)
        return 0;
    else {
        alt_esq = Altura(a->esq);
        alt_dir = Altura(a->dir);

        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}

int CalculaFb(NodoAVL *a) {
    return (Altura(a->esq) - Altura(a->dir));
}

void Desenha(NodoAVL *a, int nivel) {
    int x;

    if (a != NULL) {
        for (x = 1; x <= nivel; x++)
            printf("=");
        printf("%d FB= %d\n", a->info.valor, CalculaFb(a));

        if (a->esq != NULL) Desenha(a->esq, (nivel + 1));
        if (a->dir != NULL) Desenha(a->dir, (nivel + 1));
    }
}

int IsAvl(NodoAVL *a) {
    int alt_esq, alt_dir;

    if (a != NULL) {
        alt_esq = Altura(a->esq);
        alt_dir = Altura(a->dir);
        return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) && (IsAvl(a->esq)) && (IsAvl(a->dir)));
    } else
        return 1;
}

NodoAVL *RotacaoDireita(NodoAVL *arvore) {
    NodoAVL *ptu;

    ptu = arvore->esq;
    arvore->esq = ptu->dir;
    ptu->dir    = arvore;
    arvore->fb  = 0;
    arvore = ptu;

    return arvore;
}

NodoAVL *RotacaoEsquerda(NodoAVL *arvore) {
    NodoAVL *ptu;

    ptu = arvore->dir;
    arvore->dir = ptu->esq;
    ptu->esq    = arvore;
    arvore->fb  = 0;
    arvore = ptu;

    return arvore;
}

NodoAVL *RotacaoDuplaDireita(NodoAVL *arvore) {
    NodoAVL *ptu, *ptv;

    ptu = arvore->esq;
    ptv = ptu->dir;
    ptu->dir    = ptv->esq;
    ptv->esq    = ptu;
    arvore->esq = ptv->dir;
    ptv->dir    = arvore;

    if (ptv->fb == 1) arvore->fb = -1;
    else arvore->fb = 0;
    if (ptv->fb == -1) ptu->fb = 1;
    else ptu->fb = 0;
    arvore = ptv;

    return arvore;
}

NodoAVL *RotacaoDuplaEsquerda(NodoAVL *arvore) {
    NodoAVL *ptu, *ptv;

    ptu = arvore->dir;
    ptv = ptu->esq;
    ptu->esq    = ptv->dir;
    ptv->dir    = ptu;
    arvore->dir = ptv->esq;
    ptv->esq    = arvore;

    if (ptv->fb == -1) arvore->fb = 1;
    else arvore->fb = 0;
    if (ptv->fb == 1) ptu->fb = -1;
    else ptu->fb = 0;
    arvore = ptv;
    return arvore;
}

NodoAVL *Caso1(NodoAVL *a, int *ok) {
    NodoAVL *ptu;

    ptu = a->esq;

    if (ptu->fb == 1) {
        a = RotacaoDireita(a);
    } else {
        a = RotacaoDuplaDireita(a);
    }

    a->fb = 0;
    *ok = 0;

    return a;
}

NodoAVL *Caso2(NodoAVL *a, int *ok) {
    NodoAVL *ptu;

    ptu = a->dir;

    if (ptu->fb == -1) {
        a = RotacaoEsquerda(a);
    } else {
        a = RotacaoDuplaEsquerda(a);
    }

    a->fb = 0;
    *ok = 0;

    return a;
}

NodoAVL *InsereAVL(NodoAVL *arv, InfoNo dado, int *ok) {
    if (arv == NULL) {
        arv = (NodoAVL *) malloc(sizeof(NodoAVL));

        arv->info = dado;
        arv->esq  = NULL;
        arv->dir  = NULL;
        arv->fb   = 0;

        *ok = 1;
    } else if (dado.valor < arv->info.valor) {
        arv->esq = InsereAVL(arv->esq, dado, ok);
        if (*ok) {
            switch (arv->fb) {
                case -1: arv->fb = 0;
                    *ok = 0;
                    break;
                case 0: arv->fb = 1;
                    break;
                case 1: arv = Caso1(arv, ok);
                    break;
            }
        }
    } else {
        arv->dir = InsereAVL(arv->dir, dado, ok);
        if (*ok) {
            switch (arv->fb) {
                case 1: arv->fb = 0;
                    *ok = 0;
                    break;
                case 0: arv->fb = -1;
                    break;
                case -1: arv = Caso2(arv, ok);
                    break;
            }
        }
    }
    return arv;
}

NodoAVL *ConsultaAVLECompara(NodoAVL *a, InfoNo chave, int *n_comparacoes) {
    // Realiza a consulta de maneira iterativa
    NodoAVL *aux        = a;
    int     comparacoes = 0;

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

NodoAVL *EncontrarNodoEsquerdoAVL(NodoAVL *arv) {
    /* Encontra o nó inferior esquerdo de uma árvore ABP */
    while (arv->esq != NULL) {
        arv = arv->esq;
    }

    return arv;
}

void ExcluirArvoreAVL(NodoAVL *arv) {
    /* Este algoritmo transforma a árvore numa lista (estruturalmente falando), e libera os nós
     * conforme eles trocam de posição. */
    NodoAVL *no_esquerdo, *no_antigo;

    if (arv != NULL) {
        no_esquerdo = EncontrarNodoEsquerdoAVL(arv);
    }

    while (arv != NULL) {
        /* Se houver um ramo direito, este é colocado no fim do lado esquerdo da árvore, e o último nó
         * esquerdo é atualizado. */
        if (arv->dir != NULL) {
            no_esquerdo->esq = arv->dir;
            no_esquerdo = EncontrarNodoEsquerdoAVL(no_esquerdo);
        }

        no_antigo = arv;
        arv       = arv->esq;
        free(no_antigo);
    }
}
