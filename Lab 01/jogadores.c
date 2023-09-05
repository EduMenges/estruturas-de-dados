#include "jogadores.h"
#include <stdio.h>
#include <string.h>

void atribui_dados(jogadores *jogador, char nome[], const unsigned short int numeros[]) {
    strcpy(jogador->nome, nome);
    jogador->idade = numeros[0];
    jogador->num_gols = numeros[1];
    jogador->num_faltas = numeros[2];
    jogador->num_passes_errados = numeros[3];
    jogador->num_passes_corretos = numeros[4];
}

void exibe_estatistica(jogadores jogador) {
    printf("Nome:\t\t\t %s\n", jogador.nome);
    printf("Numero de gols:\t\t %4d\n", jogador.num_gols);
    printf("Numero de faltas:\t %4d\n", jogador.num_faltas);
    printf("Numero de passes errados: %4d\n", jogador.num_passes_errados);
    printf("Numero de corretos:\t %4d\n", jogador.num_passes_corretos);
}

bool eh_o_bom(jogadores jogador) {
    bool eh_bom = false;
    char mensagem[TAM_STRING];

    if (jogador.num_passes_corretos / jogador.num_passes_errados >= 10) {
        eh_bom = true;
        strcpy(mensagem, "eh o bom!");
    } else {
        strcpy(mensagem, "nao eh o bom :(");
    }

    printf("O jogador %s %s", jogador.nome, mensagem);

    return eh_bom;
}