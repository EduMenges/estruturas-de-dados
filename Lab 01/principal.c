#include "jogadores.h"

int main() {
    unsigned short int dados_neymar[NUM_DADOS] = {29, 450, 891, 10, 4127};
    jogadores neymar;

    atribui_dados(&neymar, "Neymar", dados_neymar);
    exibe_estatistica(neymar);
    eh_o_bom(neymar);

    return 0;
}
