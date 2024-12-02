#include <raylib.h>
#include <random>
#include "game.h"

int main() {
    // Seed random number generator
    std::random_device rd;
    srand(rd());

    Color darkBlue = {44, 44, 127, 255};
    InitWindow(300, 600, "raylib Tetris");
    SetTargetFPS(120);

    Game game = Game();

    while (WindowShouldClose() == false) {
        game.HandleInput();
        BeginDrawing();
        ClearBackground(darkBlue);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}