#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <allegro5/allegro.h>
#include "jogador.h"

#define MAX_OBS 5

typedef struct {
    float x;
    float y;
    int ativo;
} obstaculo;

// inicializa obstaculos
void obstaculos_init(obstaculo obs[]);

// atualiza obstaculos
void obstaculos_atualizar(obstaculo obs[]);

// desenha obstaculos
void obstaculos_desenhar(obstaculo obs[], ALLEGRO_BITMAP* sprite);

// verifica colisao
int obstaculos_colisao(jogador* j, obstaculo* o);

#endif
