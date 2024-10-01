#include "game.h"
#include "player.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASIC_VELOCITY 5;
#define DASHING_VEOCITY 10;

#define player_img_path "/home/joseph/personal/kron/assets/player.png"

/*
 * Creates a game
 *
 * Initialize player(s)
 *
 * Load stuff on the map
 */
Game *init_game(int screen_width, int screen_height) {
  Game *game = malloc(sizeof(Game));
  if (game == NULL) {
    perror("Failed to allocate memory for game");
    return NULL;
  }
  Player *player = init_player();
  if (player == NULL) {
    free(game);
    return NULL;
  }
  game->player = player;
  game->state = RUNNING;
  game->number_of_players = 1;
  Image image = LoadImage(player_img_path);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);
  game->player_texture = texture;
  game->player_velocity = BASIC_VELOCITY;
  game->screen_width = screen_width;
  game->screen_height = screen_height;
  return game;
}

void handle_input(Game *game) {
  int x = game->player->pos_x;
  int y = game->player->pos_y;
  if (IsKeyDown(KEY_W)) {
    y -= game->player_velocity;
  };
  if (IsKeyDown(KEY_A)) {
    x -= game->player_velocity;
  };
  if (IsKeyDown(KEY_S)) {
    y += game->player_velocity;
  }
  if (IsKeyDown(KEY_D)) {
    x += game->player_velocity;
  };
  if (IsKeyDown(KEY_SPACE)) {
    game->player_velocity = DASHING_VEOCITY;
  }
  if (IsKeyUp(KEY_SPACE)) {
    game->player_velocity = BASIC_VELOCITY;
  }
  if (x < 0) {
    x = 0;
  } else if (x >= game->screen_width - game->player_texture.width) {
    x = game->screen_width - game->player_texture.width;
  }
  if (y < 0) {
    y = 0;
  } else if (y > game->screen_height - game->player_texture.height) {
    y = game->screen_height - game->player_texture.height;
  }
  game->player->pos_x = x;
  game->player->pos_y = y;
}

void render_game(Game *game) {
  // render player
  draw_coordinates(game->player);
  DrawTexture(game->player_texture, game->player->pos_x, game->player->pos_y,
              GRAY);
}

void play(Game *game) {
  handle_input(game);
  render_game(game);
  return;
}

void clean_up_game(Game *game) {
  if (game == NULL) {
    return;
  }
  free(game->player);
  UnloadTexture(game->player_texture);
  free(game);
}
