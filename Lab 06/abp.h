#ifndef ESTRUTURA_DE_DADOS_LAB_06_ABP_H_
#define ESTRUTURA_DE_DADOS_LAB_06_ABP_H_

typedef int tipoinfo;

struct TNodoABP {
    tipoinfo        info;
    struct TNodoABP *esq;
    struct TNodoABP *dir;
};

typedef struct TNodoABP pNodoABP;

pNodoABP *InsereArvore(pNodoABP *a, tipoinfo ch);

void preFixadoE(pNodoABP *a);

void preFixadoD(pNodoABP *a);

void posFixadoE(pNodoABP *a);

void posFixadoD(pNodoABP *a);

void CentralE(pNodoABP *a);

void CentralD(pNodoABP *a);

pNodoABP *consultaABP2(pNodoABP *a, tipoinfo chave);

#endif