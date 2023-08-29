#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "8-chip emulator"

int main(int argc, char *argv[]) {
  printf("8-chip emulator\n");

  if (argv[1] == NULL) {
    printf("Usage: ./8_chip_emulator <path-to-rom>\n");
    exit(EXIT_FAILURE);
  }

  InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, WINDOW_TITLE);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    const char *text = "8-chip emulator";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, SCREEN_HEIGHT / 2, 20,
             BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
