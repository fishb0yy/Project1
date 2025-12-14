#include "jogador.h"

// inicializa jogador
void jogador_init(jogador* j) {
    j->pos_x = 400;
    j->pos_y = 300;
    j->velocidade = 4.0f;
    j->pontuacao = 0;
    j->vida = 100;
}

// atualiza movimento
void jogador_atualizar(jogador* j, int esq, int dir, int cima, int baixo) {
    if (esq) j->pos_x -= j->velocidade;
    if (dir) j->pos_x += j->velocidade;
    if (cima) j->pos_y -= j->velocidade;
    if (baixo) j->pos_y += j->velocidade;

    if (j->pos_x < 10) j->pos_x = 10;
    if (j->pos_x > 790) j->pos_x = 790;
    if (j->pos_y < 10) j->pos_y = 10;
    if (j->pos_y > 590) j->pos_y = 590;

    j->pontuacao++;
}

// desenha jogador
void jogador_desenhar(jogador* j, ALLEGRO_BITMAP* sprite) {
    float w = al_get_bitmap_width(sprite);
    float h = al_get_bitmap_height(sprite);

    al_draw_bitmap(sprite,
        j->pos_x - w / 2,
        j->pos_y - h / 2,
        0);
}
