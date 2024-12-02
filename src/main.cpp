#include <raylib.h>
#include <random>
#include "game.h"

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

    Color darkBlue = {44, 44, 127, 255};
    InitWindow(300, 600, "raylib Tetris");
    SetTargetFPS(120);

    Game game = Game();

    while (WindowShouldClose() == false) {
        game.HandleInput();
        if (EventTriggered(0.2)) {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}