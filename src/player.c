#include "player.h"
#include "stdlib.h"
#include <raylib.h>
#include <stdio.h>

Player *init_player(Texture2D *texture) {
  Player *player = malloc(sizeof(Player));
  if (player == NULL) {
    perror("Error while allocating space for player");
    return NULL;
  }
  // TODO: Make the player spawn either in the middle of the map
  // or randomly on the screen
  player->texture = texture;
  player->pos_x = 50;
  player->pos_y = 50;
  player->hp = PLAYER_MAX_HP;
  player->stamina = PLAYER_MAX_STAMINA;
  player->stamina_cooldown = STAMINA_COOLDOWN_TIME;
  return player;
}

/* void draw_coordinates(Player *player) { */
/*   char x[256]; */
/*   char y[256]; */
/*   sprintf(x, "Position X: %d", player->pos_x); */
/*   sprintf(y, "Position Y: %d", player->pos_y); */
/*   DrawText(x, 5, 5, 5, RED); */
/*   DrawText(y, 5, 20, 5, RED); */
/*   return; */
/* } */

void draw_player(Player *player) {
  DrawTexture(*player->texture, player->pos_x, player->pos_y, GRAY);
}

void draw_player_stats(Player *player) {
  char health[64];
  char stamina[64];
  sprintf(health, "Health: %d %%", player->hp);
  sprintf(stamina, "Stamina: %d %%", player->stamina);
  DrawText(health, 5, 5, 5, RED);
  DrawText(stamina, 5, 20, 5, RED);
}
