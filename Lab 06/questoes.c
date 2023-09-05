#include <stdlib.h>
#include "abp.h"
#include "questoes.h"

// Questão 1: já está completa.

/* Questão 2: recebe como parâmetro a árvore ABP gerada no exercício 1, um valor e procura o valor num nó da árvore e retorna o fator desse nó. */

int AlturaABP(pNodoABP *a) {
    int alt_esq, alt_dir;

    if (a == NULL)
        return 0;
    else {
        alt_esq = AlturaABP(a->esq);
        alt_dir = AlturaABP(a->dir);
        if (alt_esq > alt_dir)
            return (1 + alt_esq);
        else
            return (1 + alt_dir);
    }
}

int CalculaFator(pNodoABP *arvore, tipoinfo valor_procurado) {
    int retorno = 0;
    int alt_esq, alt_dir;

    pNodoABP *nodo_com_o_valor = consultaABP2(arvore, valor_procurado);

    if (nodo_com_o_valor != NULL) {
        alt_esq = AlturaABP(nodo_com_o_valor->esq);
        alt_dir = AlturaABP(nodo_com_o_valor->dir);

        retorno = alt_esq - alt_dir;
    }

    return retorno;
}

/* Questão 3: função que recebe como parâmetro a árvore gerada no exercício 1 e retorna uma
informação dizendo se a árvore é ou não AVL. */

bool EhAVL(pNodoABP *a) {
    int alt_esq, alt_dir;

    if (a != NULL) {
        alt_esq = AlturaABP(a->esq);
        alt_dir = AlturaABP(a->dir);

        return abs(alt_esq - alt_dir) < 2 && EhAVL(a->esq) && EhAVL(a->dir);
    } else
        return true;
}

/* Questão 4: função que recebe como parâmetro a árvore gerada no exercício 1 e um valor
retorna o valor do nó da árvore que tenha o valor mais próximo do valor procurado. */
pNodoABP *NodoMaisProximo(pNodoABP *arvore, tipoinfo valor_procurado, pNodoABP *antecedente) {
    pNodoABP *mais_proximo = NULL;

    if (arvore == NULL)
        return NULL;

    else if (valor_procurado > arvore->info) {
        mais_proximo = NodoMaisProximo(arvore->dir, valor_procurado, arvore);
    } else {
        mais_proximo = NodoMaisProximo(arvore->esq, valor_procurado, arvore);
    }

    if (mais_proximo == NULL) {
        if (abs(valor_procurado - antecedente->info) < abs(valor_procurado - arvore->info)) {
            return antecedente;
        } else return arvore;
    } else return mais_proximo;
}

int ValorMaisProximo(pNodoABP *arvore, tipoinfo valor_procurado) {
    pNodoABP *nodo_mais_proximo = NodoMaisProximo(arvore, valor_procurado, arvore);
    if (nodo_mais_proximo == NULL) return 0;
    else return nodo_mais_proximo->info;
}