#include <raylib.h>
#include <random>
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {
    // Seed random number generator
    std::random_device rd;
    srand(rd());

    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(120);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false) {
        game.HandleInput();
        if (EventTriggered(0.2)) {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.gameOver) {
            DrawTextEx(font, "Game Over", {320, 450}, 38, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}