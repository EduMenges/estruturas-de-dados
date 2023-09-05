#include "ldec.h"
#include <stdio.h>

int main() {
    // Declaração das variáveis
    ptLSE *lista;
    char  entrada;

    lista = CriaLista();

    // Menu das operações da lista
    do {
        printf("Escolha uma acao:\n"
               "S - Sair do programa\n"
               "I - Introduzir um numero\n"
               "E - Exibir a lista\n"
               "C - Consulta um numero\n"
               "D - Destroi a lista\n");
        scanf(" %c", &entrada);

        switch (entrada) {
            case 'I':
            case 'i':lista = InterfaceInsere(lista);
                break;
            case 'E':
            case 'e':ExibeLista(lista);
                break;
            case 'C':
            case 'c':InterfaceConsulta(lista);
                break;
            case 'D':
            case 'd':lista = DestroiLista(lista);
            case 'S':
            case 's':break;
            default: printf("Comando desconhecido.\n");
                break;
        }
    } while (entrada != 'S' && entrada != 's');

    return 0;
}