#pragma once
#include <raylib.h>
#define PLAYER_MAX_HP 100
#define PLAYER_MAX_STAMINA 100
#define STAMINA_COOLDOWN_TIME 3

typedef struct {
  int pos_x;
  int pos_y;
  int hp;
  int stamina;
  Texture2D *texture;
  int stamina_cooldown;
} Player;

Player *init_player(Texture2D *texture);

void draw_player(Player *player);

void draw_player_stats(Player *player);
