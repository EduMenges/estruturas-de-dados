#ifndef ESTRUTURA_DE_DADOS_LAB_06_QUESTOES_H_
#define ESTRUTURA_DE_DADOS_LAB_06_QUESTOES_H_

#include <stdbool.h>
#include "abp.h"

int CalculaFator(pNodoABP *arvore, tipoinfo valor_procurado);

bool EhAVL(pNodoABP *a);

int ValorMaisProximo(pNodoABP *arvore, tipoinfo valor_procurado);

#endif //ESTRUTURA_DE_DADOS_LAB_06_QUESTOES_H_
