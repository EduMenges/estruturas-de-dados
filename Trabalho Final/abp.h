#ifndef ESTRUTURA_DE_DADOS_TRABALHO_FINAL_ABP_H_
#define ESTRUTURA_DE_DADOS_TRABALHO_FINAL_ABP_H_

#include "dados.h"

struct TNodoABP {
    InfoNo          info;
    struct TNodoABP *esq;
    struct TNodoABP *dir;
};

typedef struct TNodoABP NodoABP;

NodoABP *InsereArvoreABP(NodoABP *a, InfoNo dado);

void ExcluirArvoreABP(NodoABP *a);

void PreFixadoE(NodoABP *a);

void PreFixadoD(NodoABP *a);

void PosFixadoE(NodoABP *a);

void PosFixadoD(NodoABP *a);

void CentralE(NodoABP *a);

void CentralD(NodoABP *a);

NodoABP *ConsultaABPECompara(NodoABP *a, InfoNo chave, int *n_comparacoes);

#endif