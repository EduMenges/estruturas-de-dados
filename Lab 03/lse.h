#ifndef ESTRUTURA_DE_DADOS_LAB_03_LSE_H_
#define ESTRUTURA_DE_DADOS_LAB_03_LSE_H_

#include <stdlib.h>

typedef struct tipoNo ptLSE;
struct tipoNo {
    int   numero;
    ptLSE *prox;
};

// Cria uma lista com um ponteiro nulo.
ptLSE *CriaLista(void);

// Desaloca da memória todos os elementos de uma lista, e torna seu ponteiro para nulo.
ptLSE *DestroiLista(ptLSE *lista);

// Interface para inserir valores na lista.
void InterfaceInsere(ptLSE **pt_lista);

// Exibe os elementos da lista por ordem de inserção.
void ExibeLista(ptLSE *lista);

#endif //ESTRUTURA_DE_DADOS_LAB_03_LSE_H_
