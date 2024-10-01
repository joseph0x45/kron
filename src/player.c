#include "player.h"
#include "stdlib.h"
#include <raylib.h>
#include <stdio.h>

Player *init_player() {
  Player *player = malloc(sizeof(Player));
  if (player == NULL) {
    perror("Error while allocating space for player");
    return NULL;
  }
  // TODO: Make the player spawn either in the middle of the map
  // or randomly on the screen
  player->pos_x = 50;
  player->pos_y = 50;
  player->hp = PLAYER_MAX_HP;
  player->stamina = PLAYER_MAX_STAMINA;
  return player;
}

void draw_coordinates(Player *player) {
  char x[256];
  char y[256];
  sprintf(x, "Position X: %d", player->pos_x);
  sprintf(y, "Position Y: %d", player->pos_y);
  DrawText(x, 5, 5, 5, RED);
  DrawText(y, 5, 20, 5, RED);
  return;
}
