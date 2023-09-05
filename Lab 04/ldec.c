#include "ldec.h"
#include <stdio.h>

static char *const kMensagemVazia = "A lista esta vazia.\n";

ptLSE *CriaLista(void) {
    return NULL;
}

ptLSE *DestroiLista(ptLSE *lista) {
    ptLSE *pt_aux, *parada = lista;

    // Percorre a lista e desaloca os elementos, na ordem do primeiro ao último elo.

    if (lista == NULL) puts(kMensagemVazia);
    else {
        do {
            lista  = lista->prox;
            pt_aux = lista->ant;
            free(pt_aux);
        } while (lista->prox != parada);
        free(lista);
        puts("Lista destruida.\n");
    }

    return NULL;
}

/*Dada uma lista, retorna um ponteiro que está uma posição anterior ao elemento central da lista. */
ptLSE *EncontraMeio(ptLSE *lista) {
    ptLSE        *pt_meio = lista, *parada = lista;
    unsigned int aux      = 0;

    /* Se o próximo vetor da lista não é a parada, pula para ele, assim economizando uma checagem,
     * e permitindo o encontro correto do vetor central anterior no caso de uma lista com elementos ímpares. */
    if (lista->prox != parada) {
        lista = lista->prox;
    }

    while (lista->prox != parada) {
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

/*Insere um dado número na lista, seguindo o critério de se o número:
 * — for positivo e par, insere no começo da lista;
 * — for positivo e ímpar, insere no fim da lista;
 * — for negativo, insere no meio da lista.*/
ptLSE *InsereNumero(ptLSE *pt_lista, int numero) {
    ptLSE *pt_aux, *novo;

    // Aloca um ponteiro novo para integrar à lista.
    novo = (ptLSE *) malloc(sizeof(ptLSE));
    novo->numero = numero;

    // Se a lista for vazia, torna-a este novo ponteiro.
    if (pt_lista == NULL) {
        novo->prox = novo;
        novo->ant  = novo;
        pt_lista = novo;
    } else {
        // Do contrário, se positivo:
        if (numero > 0) {
            // Liga o anterior do novo ao anterior da lista.
            novo->ant           = pt_lista->ant;
            // Liga o próximo do novo à lista.
            novo->prox          = pt_lista;
            // Liga o próximo do anterior da lista ao novo.
            pt_lista->ant->prox = novo;
            // Liga o anterior da lista ao novo.
            pt_lista->ant       = novo;

            /* Se par, atualiza o novo ponteiro para que seu próximo elo seja a lista, e o elo anterior da lista seja
             * o novo, e o torna a própria lista.*/
            if (numero % 2 == 0)
                pt_lista = novo;
            // Se ímpar, não executar a mudança, pois a inserção ocorre no final da lista.

        } else { // Se negativo, encontra o ponteiro do meio,
            pt_aux = EncontraMeio(pt_lista);
            // E atualiza os elos dele e do próximo ligando ao novo.
            novo->prox        = pt_aux->prox;
            novo->ant         = pt_aux;
            pt_aux->prox->ant = novo;
            pt_aux->prox      = novo;
        }
    }

    return pt_lista;
}

ptLSE *InterfaceInsere(ptLSE *pt_lista) {
    int entrada;

    printf("Informe os valores inteiros (0 sai do programa):\n");
    scanf("%d", &entrada);

    while (entrada != 0) {
        pt_lista = InsereNumero(pt_lista, entrada);
        scanf("%d", &entrada);
    }

    return pt_lista;
}

void ExibeLista(ptLSE *lista) {
    ptLSE *parada = lista;
    int   i       = 1;

    if (lista == NULL) {
        puts(kMensagemVazia);
    } else {
        do {
            printf("%d - %d\n", i, lista->numero);
            lista = lista->prox;
            i++;
        } while (lista != parada);
    }
}

void InterfaceConsulta(ptLSE *lista) {
    int numero;

    if (lista == NULL) {
        puts(kMensagemVazia);
    } else {
        puts("Informe o numero que deseja procurar:");
        scanf(" %d", &numero);
        ConsultaValor(lista, numero);
    }
}

void ConsultaValor(ptLSE *lista, int numero) {
    ptLSE        *pt_numero = lista, *pt_aux;
    unsigned int i          = 1;

    // Encontra o número da lista, percorrendo-a ou até encontrá-lo, ou até voltar ao começo da lista.
    while (pt_numero->numero != numero && pt_numero->prox != lista) {
        pt_numero = pt_numero->prox;
    }

    // Se o número não foi encontrado, mostrar a mensagem de que não foi encontrado.
    if (pt_numero->numero != numero) {
        puts("O numero nao foi encontrado.\n");
    } else {
        // Do contrário, exibe os demais números da lista a partir desse ponto.

        puts("Demais numeros em direcao ao fim da lista:");
        pt_aux = pt_numero;
        do {
            pt_aux = pt_aux->prox;
            printf("%d - %d\n", i, pt_aux->numero);
            i++;
        } while (pt_aux->prox != lista);

        puts("\nDemais numeros em direcao ao comeco da lista:");
        i      = 1;
        pt_aux = pt_numero;
        do {
            pt_aux = pt_aux->ant;
            printf("%d - %d\n", i, pt_aux->numero);
            i++;
        } while (pt_aux != lista);

        puts("");
    }
}
