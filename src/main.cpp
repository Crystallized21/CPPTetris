#include <raylib.h>
#include "grid.h"

int main() {
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(300, 600, "raylib Tetris");
    SetTargetFPS(120);

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[3][5] = 4;
    grid.grid[17][8] = 7;
    grid.print();

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(darkBlue);
        grid.Draw();

        EndDrawing();
    }

    CloseWindow();
}