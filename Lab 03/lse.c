#include "lse.h"
#include <stdio.h>

static char *const kMensagemVazia = "A lista esta vazia.\n";

ptLSE *CriaLista(void) {
    return NULL;
}

ptLSE *DestroiLista(ptLSE *lista) {
    ptLSE *pt_aux;

    // Percorre a lista e desaloca os elementos, na ordem do primeiro ao último elo.
    while (lista != NULL) {
        pt_aux = lista;
        lista  = lista->prox;
        free(pt_aux);
    }

    free(lista);
    puts("Lista destruida.\n");

    return NULL;
}

/*Dada uma lista, retorna um ponteiro que está uma posição anterior ao elemento central da lista. */
ptLSE *EncontraMeio(ptLSE *lista) {
    ptLSE              *pt_meio = lista;
    unsigned short int aux      = 0;

    /* Se o próximo vetor da lista não é nulo, pula para ele, assim economizando uma checagem,
     * e permitindo o encontro correto do vetor central anterior no caso de uma lista com elementos ímpares. */
    if (lista->prox != NULL) {
        lista = lista->prox;
    }

    while (lista->prox != NULL) {
        aux++;
        if (aux % 2 == 0) {
            // Atualiza o vetor do meio somente a cada duas iterações de busca.
            pt_meio = pt_meio->prox;
            aux     = 0;
        }
        lista = lista->prox;
    }

    return pt_meio;
}

/*Retorna o último elemento de uma lista.*/
ptLSE *UltimoElemento(ptLSE *lista) {
    ptLSE *pt_aux = lista;

    while (pt_aux->prox != NULL) {
        pt_aux = pt_aux->prox;
    }

    return pt_aux;
}

/*Insere um dado número na lista, seguindo o critério de se o número:
 * — for positivo e par, insere no começo da lista;
 * — for positivo e ímpar, insere no fim da lista;
 * — for negativo, insere no meio da lista.*/
void InsereNumero(ptLSE **pt_lista, int numero) {
    ptLSE *pt_aux, *novo;

    // Aloca um ponteiro novo para integrar à lista.
    novo = (ptLSE *) malloc(sizeof(ptLSE));
    novo->numero = numero;
    novo->prox   = NULL;

    // Se a lista for vazia, torna-a este novo ponteiro.
    if (*pt_lista == NULL) {
        novo->numero = numero;
        *pt_lista = novo;
    } else {
        // Do contrário, se positivo:
        if (numero > 0) {
            // Se par, atualiza o novo ponteiro para que seu próximo elo seja a lista, e o torna a própria lista.
            if (numero % 2 == 0) {
                novo->prox = *pt_lista;
                *pt_lista = novo;
            } else { // Se ímpar, liga o último elemento da lista ao novo ponteiro.
                pt_aux = UltimoElemento(*pt_lista);
                pt_aux->prox = novo;
            }
        } else { // Se negativo, encontra o ponteiro do meio, e o liga ao novo ponteiro
            pt_aux = EncontraMeio(*pt_lista);
            novo->prox   = pt_aux->prox;
            pt_aux->prox = novo;
        }
    }
}

void InterfaceInsere(ptLSE **pt_lista) {
    int entrada;

    printf("Informe os valores inteiros (0 sai do programa):\n");
    scanf("%d", &entrada);

    while (entrada != 0) {
        InsereNumero(pt_lista, entrada);
        scanf("%d", &entrada);
    }
    puts("");
}

void ExibeLista(ptLSE *lista) {
    int i = 1;

    if (lista == NULL) {
        puts(kMensagemVazia);
    } else {
        while (lista != NULL) {
            printf("%d - %d\n", i, lista->numero);
            lista = lista->prox;
            i++;
        }
        puts("");
    }
}