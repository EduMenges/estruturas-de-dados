#include <stdio.h>
#include "abp.h"
#include "questoes.h"

int main() {
    pNodoABP* arvore = NULL;
    int fator_de_balanceamento;
    bool eh_avl;

    arvore = InsereArvore(arvore, 35);
    arvore = InsereArvore(arvore, 02);
    arvore = InsereArvore(arvore, 06);
    arvore = InsereArvore(arvore, 28);
    arvore = InsereArvore(arvore, 71);
    arvore = InsereArvore(arvore, 73);
    arvore = InsereArvore(arvore, 49);
    arvore = InsereArvore(arvore, 44);
    arvore = InsereArvore(arvore, 50);

    fator_de_balanceamento = CalculaFator(arvore, 02);
    printf("O fator de 02 e: %d \n", fator_de_balanceamento);

    eh_avl = EhAVL(arvore);
    printf("A arvore e avl? %i \n", eh_avl);

    printf("O valor mais proximo de 44 na arvore e: %i \n", ValorMaisProximo(arvore, 44));
    printf("O valor mais proximo de 3 na arvore e: %i \n", ValorMaisProximo(arvore, 3));
    printf("O valor mais proximo de 100 na arvore e: %i \n", ValorMaisProximo(arvore, 100));
}
