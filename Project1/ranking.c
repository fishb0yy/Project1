#define _CRT_SECURE_NO_WARNINGS
#include "ranking.h"
#include <stdio.h>

#define MAX_RANKING 100

typedef struct {
    char nome[50];
    int pontos;
} registro;

static registro ranking[MAX_RANKING];
static int total = 0;

// carrega ranking
void ranking_carregar() {
    FILE* f = fopen("ranking.txt", "r");
    total = 0;

    if (!f) return;

    while (fscanf(f, "%49[^;];%d\n", ranking[total].nome, &ranking[total].pontos) == 2) {
        total++;
        if (total >= MAX_RANKING) break;
    }

    fclose(f);
}

// insere registro
void ranking_inserir(const char* nome, int pontos) {
    FILE* f = fopen("ranking.txt", "a");
    if (!f) return;

    fprintf(f, "%s;%d\n", nome, pontos);
    fclose(f);
}

// imprime ranking no console
void ranking_imprimir_console() {
    ranking_carregar();

    printf("\n===== ranking =====\n");
    for (int i = 0; i < total; i++) {
        printf("%d - %s : %d\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }
    printf("===================\n");
}

// limpa ranking
void ranking_limpar() {
    total = 0;
}
