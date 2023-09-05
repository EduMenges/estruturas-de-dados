#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dados.h"
#include "abp.h"
#include "avl.h"
#include "lse.h"
#include <string.h>

#define Q_TESTES 4
#define Q_TESTES_ORDENADOS 3
#define Q_TESTES_ALEATORIOS 10
#define AMOSTRAS 3

typedef struct ResultadoS {
    struct timespec tempo;
    int             comparacoes;
} Resultado;

/* Gera os valores para serem consultados nos testes ordenados. */
InfoNo *ConsultaOrdenada(const int limite) {
    static InfoNo consultas[Q_TESTES_ORDENADOS] = {{0}};

    consultas[1].valor = limite / 2 - 1;
    consultas[2].valor = limite - 1;

    return consultas;
}

int GeradorAleatorio(int limite) {
    double num = (double) rand();
    num = num / RAND_MAX;
    num = num * limite;

    return (int) num;
}

struct timespec DiffTimespec(const struct timespec *time_end, const struct timespec *time_start) {
    struct timespec diff = {.tv_sec = time_end->tv_sec - time_start->tv_sec,
            .tv_nsec =time_end->tv_nsec - time_start->tv_nsec};

    if (diff.tv_nsec < 0) {
        diff.tv_nsec += 1000000000;
        diff.tv_sec--;
    }

    return diff;
}

Lista *GeraListaOrdenada(int limite, Lista *lista_ordenada);

Resultado *TestUnitABPOrdenado(NodoABP *arv_de_teste, InfoNo consultado) {
    static Resultado resultados[AMOSTRAS];
    struct timespec  res_temp;

    for (int i = 0; i < AMOSTRAS; i++) {
        timespec_get(&resultados[i].tempo, TIME_UTC);
        ConsultaABPECompara(arv_de_teste, consultado, &resultados[i].comparacoes);
        timespec_get(&res_temp, TIME_UTC);

        resultados[i].tempo = DiffTimespec(&res_temp, &resultados[i].tempo);
    }

    return resultados;
}

Resultado *TestaABPOrdenado(const int limite, struct timespec *tempo_de_insercao) {
    struct timespec  temp;
    static Resultado resultados[Q_TESTES_ORDENADOS][AMOSTRAS];
    NodoABP          *arv          = NULL;
    InfoNo           dado_inserido = {.valor = 0}, *consultas;

    arv = InsereArvoreABP(arv, dado_inserido);

    timespec_get(tempo_de_insercao, TIME_UTC);
    // Prepara a árvore
    for (int i = 1; i < limite; ++i) {
        dado_inserido.valor = i;
        arv = InsereArvoreABP(arv, dado_inserido);
    }
    timespec_get(&temp, TIME_UTC);
    *tempo_de_insercao = DiffTimespec(&temp, tempo_de_insercao);

    consultas = ConsultaOrdenada(limite);

    for (int i = 0; i < Q_TESTES_ORDENADOS; ++i) {
        memcpy(resultados[i], TestUnitABPOrdenado(arv, consultas[i]), sizeof(resultados[i]));
    }

    ExcluirArvoreABP(arv);

    return (Resultado *) resultados;
}

Resultado *TestUnitAVLOrdenado(NodoAVL *arv_de_teste, InfoNo consultado) {
    static Resultado resultados[AMOSTRAS];
    struct timespec  res_temp;

    for (int i = 0; i < AMOSTRAS; i++) {
        timespec_get(&resultados[i].tempo, TIME_UTC);
        ConsultaAVLECompara(arv_de_teste, consultado, &resultados[i].comparacoes);
        timespec_get(&res_temp, TIME_UTC);

        resultados[i].tempo = DiffTimespec(&res_temp, &resultados[i].tempo);
    }

    return resultados;
}

Resultado *TestaAVLOrdenado(int limite, struct timespec *tempo_de_insercao) {
    struct timespec  temp;
    static Resultado resultados[Q_TESTES_ORDENADOS][AMOSTRAS];
    int              ok;
    NodoAVL          *arv = NULL;
    InfoNo           dado_inserido, *consultas;

    timespec_get(tempo_de_insercao, TIME_UTC);
    // Prepara a árvore
    for (int i = 0; i < limite; ++i) {
        dado_inserido.valor = i;
        arv = InsereAVL(arv, dado_inserido, &ok);
    }
    timespec_get(&temp, TIME_UTC);
    *tempo_de_insercao = DiffTimespec(&temp, tempo_de_insercao);

    consultas = ConsultaOrdenada(limite);

    for (int i = 0; i < Q_TESTES_ORDENADOS; ++i) {
        memcpy(resultados[i], TestUnitAVLOrdenado(arv, consultas[i]), sizeof(resultados[i]));
    }

    ExcluirArvoreAVL(arv);

    return (Resultado *) resultados;
}

Lista *GeraListaOrdenada(int limite, Lista *lista_ordenada) {
    struct timespec  temp;
    InfoNo inserido;

    for (int i = 0; i < limite; ++i) {
        inserido.valor = i;
        lista_ordenada = Push(lista_ordenada, inserido);
    }

    return lista_ordenada;
}

Resultado *TestaABPAleatoria(int limite, struct timespec *tempo_de_insercao) {
    static Resultado resultados[Q_TESTES_ALEATORIOS];
    NodoABP          *arv            = NULL;
    Lista            *lista_ordenada = CriaLista();
    int              tamanho_lista   = limite, posicao_a_remover;
    InfoNo           removido, valores_buscados[Q_TESTES_ALEATORIOS];
    struct timespec  temp;

    // Cria a lista com os números até o limite.
    lista_ordenada = GeraListaOrdenada(limite, lista_ordenada);

    timespec_get(tempo_de_insercao, TIME_UTC);
    // Remove esses valores aleatoriamente e insere na ABP.
    for (int i = tamanho_lista; i > 0; i--) {
        posicao_a_remover = GeradorAleatorio(i);
        removido          = PopListaPos(&lista_ordenada, posicao_a_remover);

        arv = InsereArvoreABP(arv, removido);
    }
    timespec_get(&temp, TIME_UTC);
    *tempo_de_insercao = DiffTimespec(&temp, tempo_de_insercao);

    // Gera os valores aleatórios para consulta
    for (int i = 0; i < Q_TESTES_ALEATORIOS; ++i) {
        valores_buscados[i].valor = GeradorAleatorio(limite);
    }

    // Faz o cálculo do tempo.
    for (int i = 0; i < Q_TESTES_ALEATORIOS; ++i) {
        timespec_get(&resultados[i].tempo, TIME_UTC);
        ConsultaABPECompara(arv, valores_buscados[i], &resultados[i].comparacoes);
        timespec_get(&temp, TIME_UTC);

        resultados[i].tempo = DiffTimespec(&temp, &resultados[i].tempo);
    }

    ExcluirArvoreABP(arv);

    return resultados;
}

Resultado *TestaAVLAleatoria(int limite, struct timespec *tempo_de_insercao) {
    static Resultado resultados[Q_TESTES_ALEATORIOS];
    NodoAVL          *arv            = NULL;
    Lista            *lista_ordenada = CriaLista();
    int             tamanho_lista   = limite, posicao_a_remover, ok;
    InfoNo          removido, valores_buscados[Q_TESTES_ALEATORIOS];
    struct timespec temp;

    // Cria a lista com os números até o limite.
    lista_ordenada = GeraListaOrdenada(limite, lista_ordenada);

    timespec_get(tempo_de_insercao, TIME_UTC);
    // Remove esses valores aleatoriamente e insere na ABP.
    for (int i = tamanho_lista; i > 0; i--) {
        posicao_a_remover = GeradorAleatorio(i);
        removido          = PopListaPos(&lista_ordenada, posicao_a_remover);

        arv = InsereAVL(arv, removido, &ok);
    }
    timespec_get(&temp, TIME_UTC);
    *tempo_de_insercao = DiffTimespec(&temp, tempo_de_insercao);

    // Gera os valores aleatórios para consulta
    for (int i = 0; i < Q_TESTES_ALEATORIOS; ++i) {
        valores_buscados[i].valor = GeradorAleatorio(limite);
    }

    // Faz o cálculo do tempo.
    for (int i = 0; i < Q_TESTES_ALEATORIOS; ++i) {
        timespec_get(&resultados[i].tempo, TIME_UTC);
        ConsultaAVLECompara(arv, valores_buscados[i], &resultados[i].comparacoes);
        timespec_get(&temp, TIME_UTC);

        resultados[i].tempo = DiffTimespec(&temp, &resultados[i].tempo);
    }

    ExcluirArvoreAVL(arv);

    return resultados;
}

void GravaResultadosOrdenados(FILE *saida, int testes[Q_TESTES], Resultado
resultados[Q_TESTES][Q_TESTES_ORDENADOS][AMOSTRAS]) {
    char temp[256], local_do_valor[Q_TESTES_ORDENADOS][10] = {"Comeco", "Meio", "Fim"};

    for (int i = 0; i < Q_TESTES; ++i) {
        sprintf(temp, "\t%d\n", testes[i]);
        fputs(temp, saida);

        fputs("\t\t", saida);

        for (int j = 0; j < Q_TESTES_ORDENADOS; ++j) {
            sprintf(temp, "%s;;", local_do_valor[j]);
            fputs(temp, saida);
        }

        fputs("\n\t\t", saida);

        for (int j = 0; j < Q_TESTES_ORDENADOS; ++j) {
            sprintf(temp, "Tempo;Comparacoes;");
            fputs(temp, saida);
        }

        fputs("\n", saida);

        for (int j = 0; j < AMOSTRAS; ++j) {
            fputs("\t\t", saida);
            for (int k = 0; k < Q_TESTES_ORDENADOS; ++k) {
                sprintf(temp, "%lld,%ld;%d;", resultados[i][k][j].tempo.tv_sec, resultados[i][k][j].tempo.tv_nsec,
                        resultados[i][k][j].comparacoes);
                fputs(temp, saida);
            }
            fputs("\n", saida);
        }
        fputs("\n", saida);
    }
}

void GravaResultadosAleatorios(FILE *saida, int testes[Q_TESTES], Resultado resultados[Q_TESTES][Q_TESTES_ALEATORIOS]) {
    char temp[256];

    for (int i = 0; i < Q_TESTES; ++i) {
        sprintf(temp, "\t%d\n", testes[i]);
        fputs(temp, saida);

        sprintf(temp, "\tTempo;Comparacoes;\n");
        fputs(temp, saida);

        for (int j = 0; j < Q_TESTES_ALEATORIOS; ++j) {
            fputs("\t", saida);

            sprintf(temp, "%lld,%ld;%d", resultados[i][j].tempo.tv_sec, resultados[i][j].tempo.tv_nsec,
                    resultados[i][j].comparacoes);
            fputs(temp, saida);

            fputs("\n", saida);
        }

        fputs("\n", saida);
    }
}

int main() {
//    int       testes[Q_TESTES] = {5000, 10000, 100000, 1000000};
    int             testes[Q_TESTES] = {50, 100, 1000, 10000};
    struct timespec tempo_de_insercao[Q_TESTES][4];
    Resultado       res_abp_ordenados[Q_TESTES][Q_TESTES_ORDENADOS][AMOSTRAS],
                    res_avl_ordenados[Q_TESTES][Q_TESTES_ORDENADOS][AMOSTRAS],
                    res_abp_aleatorios[Q_TESTES][Q_TESTES_ALEATORIOS],
                    res_avl_aleatorios[Q_TESTES][Q_TESTES_ALEATORIOS];
    char            nome_saida[]     = "resultados.csv";
    FILE            *resultado;

    srand(time(NULL));
    setbuf(stdout, 0);

    for (int i = 0; i < Q_TESTES; ++i) {
        if (i == Q_TESTES - 1)
            printf("AVISO: os proximos testes podem demorar MUITO! Tenha paciencia!\n");

        memcpy(res_abp_ordenados[i],
               TestaABPOrdenado(testes[i], &tempo_de_insercao[i][0]),
               sizeof(res_abp_ordenados[i]));
        printf("Concluido teste de ABP ordenado em %d.\n", testes[i]);
        memcpy(res_avl_ordenados[i],
               TestaAVLOrdenado(testes[i], &tempo_de_insercao[i][1]),
               sizeof(res_avl_ordenados[i]));
        printf("Concluido teste de AVL ordenado em %d.\n", testes[i]);

        memcpy(res_abp_aleatorios[i],
               TestaABPAleatoria(testes[i], &tempo_de_insercao[i][2]), sizeof(res_abp_aleatorios[i]));
        printf("Concluido teste de ABP aleatorio em %d.\n", testes[i]);
        memcpy(res_avl_aleatorios[i],
               TestaAVLAleatoria(testes[i], &tempo_de_insercao[i][3]), sizeof(res_avl_aleatorios[i]));
        printf("Concluido teste de AVL aleatorio em %d.\n", testes[i]);
        puts("");
    }

    resultado = fopen(nome_saida, "w");

    // Caso seja possível a abertura do arquivo.
    if (resultado != NULL) {
        fputs("RESULTADOS ABP ORDENADOS:\n\n", resultado);
        GravaResultadosOrdenados(resultado, testes, res_abp_ordenados);

        fputs("RESULTADOS AVL ORDENADOS:\n\n", resultado);
        GravaResultadosOrdenados(resultado, testes, res_avl_ordenados);

        fputs("RESULTADOS ABP ALEATORIOS:\n\n", resultado);
        GravaResultadosAleatorios(resultado, testes, res_abp_aleatorios);

        fputs("RESULTADOS AVL ALEATORIOS:\n\n", resultado);
        GravaResultadosAleatorios(resultado, testes, res_avl_aleatorios);

        fclose(resultado);
        resultado = NULL;
    } else printf("Erro ao salvar arquivo de resultado.");

    return 0;
}
