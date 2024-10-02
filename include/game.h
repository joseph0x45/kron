#pragma once
#include "player.h"
#include <raylib.h>

#define BASIC_VELOCITY 3
#define DASHING_VEOCITY 8
#define player_img_path "/home/joseph/personal/kron/assets/player.png"

typedef enum {
  RUNNING,
  PAUSED,
  FINISHED,
} GameState;

typedef struct {
  GameState state;
  Player *player;
  int number_of_players;
  Texture2D player_texture;
  int player_velocity;
  int screen_width;
  int screen_height;
} Game;

Game *init_game(int screen_width, int screen_height);

void render_game(Game *game);

void play(Game *game);

void clean_up_game(Game *game);

void handle_input(Game *game);

void process_game_logic(Game *game);
