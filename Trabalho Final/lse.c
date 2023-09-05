#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "lse.h"

Lista *CriaLista(void) {
    return NULL;
}

/* Insere no começo da lista. */
Lista *Push(Lista *l, InfoNo dados) {
    Lista *novo;

    novo = (Lista *) malloc(sizeof(Lista));
    novo->info = dados;
    novo->prox = l;

    return novo;
}

Lista *InsereOrd(Lista *l, InfoNo dados) {
    Lista *novo;
    Lista *ant    = NULL;
    Lista *pt_aux = l; //ponteiro auxiliar para percorrer a lista

    /* Aloca um novo nodo */
    novo = (Lista *) malloc(sizeof(Lista));

    /* Insere a informação no novo nodo */
    novo->info = dados;

    /* procurando a posição de inserção */
    while (pt_aux != NULL) {
        ant    = pt_aux;
        pt_aux = pt_aux->prox;
    }

    /* encadeia o elemento */
    if (ant == NULL) /* o anterior não existe, logo o elemento será inserido na primeira posição */
    {
        novo->prox = l;
        l = novo;
    } else /* elemento inserido no meio da lista */
    {
        novo->prox = ant->prox;
        ant->prox  = novo;
    }

    return l;
}

void Imprime(Lista *l) {
    Lista *pt_aux;
    int   posicao;

    if (l == NULL)
        puts("Lista vazia.");
    else
        for (pt_aux = l, posicao = 0; pt_aux != NULL; pt_aux = pt_aux->prox, posicao++)
            printf("%d -> %d\n", posicao, pt_aux->info.valor);
}

Lista *Remover(Lista *l, int valor) {
    Lista *anterior = NULL;
    Lista *pt_aux   = l;

    /*procura o elemento na lista*/
    while (pt_aux != NULL && pt_aux->info.valor != valor) {
        anterior = pt_aux;
        pt_aux   = pt_aux->prox;
    }

    /*verifica se achou*/
    if (pt_aux == NULL)
        return l; /*retorna a lista original*/

    if (anterior == NULL) /*vai remover o primeiro elemento*/
        l = pt_aux->prox;
    else /*vai remover do meio ou do final*/
        anterior->prox = pt_aux->prox;

    free(pt_aux); /*libera a memória alocada*/

    return l;
}

Lista *Destroi(Lista *l) {
    Lista *ptaux; //ponteiro auxiliar para percorrer a lista
    while (l != NULL) {
        ptaux = l;
        l     = l->prox;
        free(ptaux);
    }
    free(l);
    return NULL;
}

InfoNo PopListaPos(Lista **l, int posicao) {
    /* Procura um nodo na posição da lista, remove-o, e o retorna.*/
    int    contador = 0;
    Lista  *aux     = *l, *ant = *l;
    InfoNo retorno  = {.valor = 0};

    while (aux != NULL & contador != posicao) {
        ant = aux;
        aux = aux->prox;
        ++contador;
    }

    if (aux != NULL) {
        retorno = aux->info;

        if (ant != aux)
            ant->prox = aux->prox;
        else
            *l = (*l)->prox;

        free(aux);
    }

    return retorno;
}
