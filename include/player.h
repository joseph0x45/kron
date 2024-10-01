#pragma once
#define PLAYER_MAX_HP 100
#define PLAYER_MAX_STAMINA 100

typedef struct {
  int pos_x;
  int pos_y;
  int hp;
  int stamina;
} Player;

Player *init_player();

void draw_coordinates(Player *player);
