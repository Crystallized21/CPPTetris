#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

constexpr int SCREEN_WIDTH = 600;
constexpr int SCREEN_HEIGHT = 800;
constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;
constexpr int BLOCK_SIZE = 40;

struct Tetromino {
    const int width;
    const int height;
    const int (*shape)[4]; // Pointer to a 4x4 array of integers
};

// The Global Game Grid
int grid[GRID_HEIGHT][GRID_WIDTH] = {};

constexpr int GRID_OFFSET_X = (SCREEN_WIDTH - GRID_WIDTH * BLOCK_SIZE) / 2;
constexpr int GRID_OFFSET_Y = (SCREEN_HEIGHT - GRID_HEIGHT * BLOCK_SIZE) / 2;

// Tetromino Shape Definitions
constexpr int I_BLOCK[4][4]{
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr int J_BLOCK[4][4]{
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr int L_BLOCK[4][4]{
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr int O_BLOCK[4][4]{
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr int S_BLOCK[4][4]{
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr int T_BLOCK[4][4]{
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr int Z_BLOCK[4][4]{
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

constexpr Tetromino tetrominoes[] = {
    {4, 4, I_BLOCK}, // I-block
    {3, 3, J_BLOCK}, // J-block
    {3, 3, L_BLOCK}, // L-block
    {2, 2, O_BLOCK}, // O-block
    {3, 3, S_BLOCK}, // S-block
    {3, 3, T_BLOCK}, // T-block
    {3, 3, Z_BLOCK}  // Z-block
};

void renderGrid(SDL_Renderer *renderer) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == 0) {
                // Empty Cells
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Dark Grey
            } else {
                // Filled Cell - draw a block.
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }

            // Calculate the cell's position on the screen
            SDL_Rect rect = {GRID_OFFSET_X + x * BLOCK_SIZE, GRID_OFFSET_Y + y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
            SDL_RenderDrawRect(renderer, &rect);

            // Draw Grid Lines
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void renderTetromino(SDL_Renderer *renderer, const Tetromino &tetromino, int x, int y) {
    for (int i = 0; i < tetromino.height; i++) {
        for (int j = 0; j < tetromino.width; j++) {
            if (tetromino.shape[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red

                SDL_Rect rect = {
                    GRID_OFFSET_X + (x + j) * BLOCK_SIZE, GRID_OFFSET_Y + (y + i) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE
                };
                SDL_RenderFillRect(renderer, &rect);

                // Black Outline
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}

int main() {
    // Initialise SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    // Create the window
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Window could not be created!" << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Tetromino activeTetromino = tetrominoes[0]; // Start with I-block
    int tetrominoX = 3; // Starting column
    int tetrominoY = 0; // Starting row


    // The main game loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear Screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the Grid
        renderGrid(renderer);

        // Render the Tetromino
        renderTetromino(renderer, activeTetromino, tetrominoX, tetrominoY);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean Up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
