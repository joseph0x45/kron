#include "game.h"
#include "player.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  Player *player = init_player(&game->player_texture);
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

int player_is_moving() {
  return IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) ||
         IsKeyDown(KEY_D);
}

void handle_input(Game *game) {
  if (IsKeyDown(KEY_SPACE) && player_is_moving()) {
    game->player->last_used_stamina = GetTime();
    game->player->stamina_cooldown_active = 1;
    if (game->player->stamina > 0) {
      game->player_velocity = DASHING_VEOCITY;
      if (game->player->stamina - 1 < 0) {
        game->player->stamina = 0;
      } else {
        game->player->stamina -= 1;
      }
    }
  }
  if (IsKeyUp(KEY_SPACE)) {
    game->player_velocity = BASIC_VELOCITY;
  }
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

/* void process_game_logic(Game *game) { */
/*  */
/* } */

void render_game(Game *game) {
  /* process_game_logic(game); */
  handle_player(game->player);
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
  UnloadTexture(game->player_texture);
  free(game->player);
  free(game);
}
