#ifndef JOGADOR_H
#define JOGADOR_H

#include <allegro5/allegro.h>

typedef struct {
    float pos_x;
    float pos_y;
    float velocidade;
    int pontuacao;
    int vida;
} jogador;

// inicializa jogador
void jogador_init(jogador* j);

// atualiza movimento
void jogador_atualizar(jogador* j, int esq, int dir, int cima, int baixo);

// desenha jogador
void jogador_desenhar(jogador* j, ALLEGRO_BITMAP* sprite);

#endif
