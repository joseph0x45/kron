#include "game.h"
#include "raylib.h"

int main(void) {
  const int screenWidth = 900;
  const int screenHeight = 500;
  InitWindow(screenWidth, screenHeight, "Kron");
  Game *game = init_game(screenWidth, screenHeight);

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    ClearBackground(GRAY);
    BeginDrawing();
    play(game);
    EndDrawing();
  }
  clean_up_game(game);
  CloseWindow();
  return 0;
}
