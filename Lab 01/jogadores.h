#include <stdbool.h>

#ifndef ESTRUTURA_DE_DADOS_LAB_01_JOGADORES_H_
#define ESTRUTURA_DE_DADOS_LAB_01_JOGADORES_H_
#define NUM_DADOS 5
#define TAM_STRING 100

typedef struct Jogadores {
    char nome[TAM_STRING];
    unsigned short int idade;
    unsigned short int num_gols;
    unsigned short int num_faltas;
    unsigned short int num_passes_errados;
    unsigned short int num_passes_corretos;
} jogadores;

/*Dado um jogador, atribui os dados providos aos seus campos da estrutura.
 * O vetor de n�meros segue o formato:
 * {idade, num_gols, num_faltas, num_passes_errados, num_passes_corretos}.*/
void atribui_dados(jogadores *jogador, char nome[], const unsigned short int numeros[]);

/*Imprime na tela as estat�sticas de um dado jogador, incluindo:
 * nome, n�mero de gols, n�mero de faltas, passes errados, e passes certos.*/
void exibe_estatistica(jogadores jogador);

/*Informe se jogador � o bom.
 * O crit�rio de profici�ncia depende da quantidade de passes, se a raz�o entre os passes corretos e os errados for maior ou igual a 10, ele � bom.*/
bool eh_o_bom(jogadores jogador);

#endif //ESTRUTURA_DE_DADOS_LAB_01_JOGADORES_H_