#include "lse.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct ptO PtO;
struct ptO {
    int  numero;
    bool repetido;
    PtO  *prox;
};

PtO *InsereOcorrencia(PtO *lista, int num) {
    PtO *novo;
    PtO *aux = lista;

    novo = (PtO *) malloc(sizeof(PtO));
    novo->numero   = num;
    novo->repetido = false;

    if (lista == NULL) {
        novo->prox = NULL;
        return novo;
    } else {
        for (; aux != NULL && aux->numero != num; aux = aux->prox) {
        }
        if (aux == NULL) {
            novo->prox = lista;
            return novo;
        } else {
            free(novo);
            aux->repetido = true;
            return lista;
        }
    }
}

bool TemOcorrencia(PtO *lista, int num) {
    PtO *aux = lista;

    while (aux != NULL) {
        if (aux->numero == num) return aux->repetido;
        aux = aux->prox;
    }
    return false;
}

ptLSE *RemoveDuplicadas(ptLSE *lista) {
    PtO   *ocorrencias = NULL;
    ptLSE *aux         = lista, *desaloca, *ant = NULL;

    for (ptLSE *pt_aux = lista; pt_aux != NULL; pt_aux = pt_aux->prox) {
        ocorrencias = InsereOcorrencia(ocorrencias, pt_aux->numero);
    }

    while (aux != NULL) {
        if (TemOcorrencia(ocorrencias, aux->numero)) {
            if (ant != NULL) {
                ant->prox = aux->prox;
                desaloca = aux;
                aux      = aux->prox;
                free(desaloca);
            } else {
                lista    = lista->prox;
                desaloca = aux;
                aux      = aux->prox;
                free(desaloca);
            }
        } else {
            ant = aux;
            aux = aux->prox;
        }
    }
    return lista;
}

int main() {
    // Declaração das variáveis
    ptLSE *lista;
    char  entrada;

    lista = CriaLista();

    // Menu das operações da lista
    do {
        printf("Escolha uma acao:\n"
               "S - Sair do programa\n"
               "I - Introduzir um numero\n"
               "E - Exibir a lista\n"
               "D - Destroi a lista\n");
        scanf(" %c", &entrada);

        switch (entrada) {
            case 'I':
            case 'i':InterfaceInsere(&lista);
                break;
            case 'E':
            case 'e':ExibeLista(lista);
                break;
            case 'D':
            case 'd':lista = DestroiLista(lista);
            case 'r':lista = RemoveDuplicadas(lista);
            case 'S':
            case 's':break;
            default: printf("Comando desconhecido.\n");
                break;
        }
    } while (entrada != 'S' && entrada != 's');

    return 0;
}