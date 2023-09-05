#ifndef ESTRUTURA_DE_DADOS_LAB_04_LDEC_H_
#define ESTRUTURA_DE_DADOS_LAB_04_LDEC_H_

#include <stdlib.h>

typedef struct tipoNo ptLSE;
struct tipoNo {
    int   numero;
    ptLSE *ant;
    ptLSE *prox;
};

// Cria uma lista com um ponteiro nulo.
ptLSE *CriaLista(void);

// Desaloca da memória todos os elementos de uma lista, e torna seu ponteiro para nulo.
ptLSE *DestroiLista(ptLSE *lista);

// Interface para inserir valores na lista.
ptLSE *InterfaceInsere(ptLSE *pt_lista);

// Exibe os elementos da lista por ordem de inserção.
void ExibeLista(ptLSE *lista);

// Interface para consultar os valores.
void InterfaceConsulta(ptLSE *lista);

// Localiza um número na lista, e exibe os demais números em direção ao fim, e em direção ao começo.
void ConsultaValor(ptLSE *lista, int numero);

#endif //ESTRUTURA_DE_DADOS_LAB_04_LDEC_H_
