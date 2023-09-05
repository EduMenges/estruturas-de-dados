#ifndef ESTRUTURA_DE_DADOS_TRABALHO_FINAL_AVL_H_
#define ESTRUTURA_DE_DADOS_TRABALHO_FINAL_AVL_H_

#include "dados.h"

typedef struct TNodoAVL {
    InfoNo          info;
    int             fb;
    struct TNodoAVL *esq;
    struct TNodoAVL *dir;
} NodoAVL;

int Altura(NodoAVL *a);

int CalculaFb(NodoAVL *a);

void Desenha(NodoAVL *a, int nivel);

int IsAvl(NodoAVL *a);

NodoAVL *RotacaoDireita(NodoAVL *arvore);

NodoAVL *RotacaoEsquerda(NodoAVL *arvore);

NodoAVL *RotacaoDuplaDireita(NodoAVL *arvore);

NodoAVL *RotacaoDuplaEsquerda(NodoAVL *arvore);

NodoAVL *Caso1(NodoAVL *a, int *ok);

NodoAVL *Caso2(NodoAVL *a, int *ok);

NodoAVL *InsereAVL(NodoAVL *arv, InfoNo dado, int *ok);

NodoAVL *ConsultaAVLECompara(NodoAVL *a, InfoNo chave, int *n_comparacoes);

void ExcluirArvoreAVL(NodoAVL *arv);

#endif