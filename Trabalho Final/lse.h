#ifndef ESTRUTURA_DE_DADOS_TRABALHO_FINAL_LSE_H_
#define ESTRUTURA_DE_DADOS_TRABALHO_FINAL_LSE_H_

#include "dados.h"

typedef struct TipoPtNo Lista;

struct TipoPtNo {
    InfoNo info;
    Lista  *prox;
};

Lista *CriaLista(void);

Lista *Push(Lista *l, InfoNo dados);

Lista *InsereOrd(Lista *l, InfoNo dados);

void Imprime(Lista *l);

Lista *Remover(Lista *l, int valor);

Lista *Destroi(Lista *l);

InfoNo PopListaPos(Lista **l, int posicao);

#endif