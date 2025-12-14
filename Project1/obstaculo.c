#include "obstaculo.h"
#include <stdlib.h>
#include <math.h>

// inicializa obstaculos
void obstaculos_init(obstaculo obs[]) {
    for (int i = 0; i < MAX_OBS; i++) {
        obs[i].x = 800 + rand() % 300;
        obs[i].y = rand() % 600;
        obs[i].ativo = 1;
    }
}

// atualiza obstaculos
void obstaculos_atualizar(obstaculo obs[]) {
    for (int i = 0; i < MAX_OBS; i++) {
        obs[i].x -= 3.0f + (i % 3);

        if (obs[i].x < -20) {
            obs[i].x = 800 + rand() % 200;
            obs[i].y = rand() % 600;
            obs[i].ativo = 1;
        }
    }
}

// desenha obstaculos
void obstaculos_desenhar(obstaculo obs[], ALLEGRO_BITMAP* sprite) {
    for (int i = 0; i < MAX_OBS; i++) {
        if (obs[i].ativo) {
            float w = al_get_bitmap_width(sprite);
            float h = al_get_bitmap_height(sprite);

            al_draw_bitmap(sprite,
                obs[i].x - w / 2,
                obs[i].y - h / 2,
                0);
        }
    }
}

// colisao simples
int obstaculos_colisao(jogador* j, obstaculo* o) {
    float dx = fabs(j->pos_x - o->x);
    float dy = fabs(j->pos_y - o->y);
    return (dx < 15 && dy < 15);
}
