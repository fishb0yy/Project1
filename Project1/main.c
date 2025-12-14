#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "jogador.h"
#include "obstaculo.h"
#include "ranking.h"

enum estado_jogo {
    JOGANDO,
    GAME_OVER
};

int main() {

    if (!al_init()) return -1;
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();

    srand((unsigned)time(NULL));

    ALLEGRO_DISPLAY* janela = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE* fila = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(fila, al_get_keyboard_event_source());
    al_register_event_source(fila, al_get_display_event_source(janela));
    al_register_event_source(fila, al_get_timer_event_source(timer));

    ALLEGRO_BITMAP* sprite_player = al_load_bitmap("eevee.png");
    ALLEGRO_BITMAP* sprite_obs = al_load_bitmap("gyrados.png");

    if (!sprite_player || !sprite_obs) return -1;

    ranking_carregar();

    jogador player;
    jogador_init(&player);

    obstaculo obs[MAX_OBS];
    obstaculos_init(obs);

    bool esq = false, dir = false, cima = false, baixo = false;
    bool rodando = true;
    bool redesenhar = true;

    enum estado_jogo estado = JOGANDO;

    ALLEGRO_EVENT ev;
    al_start_timer(timer);

    while (rodando) {

        al_wait_for_event(fila, &ev);

        switch (ev.type) {

        case ALLEGRO_EVENT_KEY_DOWN:
            if (ev.keyboard.keycode == ALLEGRO_KEY_A) esq = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_D) dir = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_W) cima = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_S) baixo = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) rodando = false;
            break;

        case ALLEGRO_EVENT_KEY_UP:
            if (ev.keyboard.keycode == ALLEGRO_KEY_A) esq = false;
            if (ev.keyboard.keycode == ALLEGRO_KEY_D) dir = false;
            if (ev.keyboard.keycode == ALLEGRO_KEY_W) cima = false;
            if (ev.keyboard.keycode == ALLEGRO_KEY_S) baixo = false;
            break;

        case ALLEGRO_EVENT_TIMER:

            if (estado == JOGANDO) {

                jogador_atualizar(&player, esq, dir, cima, baixo);
                obstaculos_atualizar(obs);

                for (int i = 0; i < MAX_OBS; i++) {
                    if (obstaculos_colisao(&player, &obs[i])) {
                        player.vida -= 1;
                        obs[i].ativo = 0;
                    }
                }

                if (player.vida <= 0) {
                    ranking_inserir("player", player.pontuacao);
                    ranking_imprimir_console();
                    estado = GAME_OVER;
                }

                player.pontuacao++;
            }

            redesenhar = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            rodando = false;
            break;
        }

        if (redesenhar && al_is_event_queue_empty(fila)) {
            redesenhar = 0;

            al_clear_to_color(al_map_rgb(255, 255, 255));

            // desenha jogador e obstaculos
            jogador_desenhar(&player, sprite_player);
            obstaculos_desenhar(obs, sprite_obs);

            //  barra de vida
            float vida_pct = player.vida / 100.0f;
            if (vida_pct < 0) vida_pct = 0;

            // fundo da barra
            al_draw_filled_rectangle(10, 10, 210, 30,
                al_map_rgb(60, 60, 60));

            // vida atual
            al_draw_filled_rectangle(10, 10,
                10 + 200 * vida_pct, 30,
                al_map_rgb(200, 0, 0));

            al_flip_display();
        }

    }

    al_destroy_bitmap(sprite_player);
    al_destroy_bitmap(sprite_obs);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila);
    al_destroy_display(janela);

    return 0;
}
