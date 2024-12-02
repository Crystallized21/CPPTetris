#include <SDL2/SDL.h>
#include <iostream>
#include <random>

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

// Define colors for each tetromino type
constexpr SDL_Color I_BLOCK_COLOR = {0, 255, 255, 255}; // Cyan
constexpr SDL_Color J_BLOCK_COLOR = {0, 0, 255, 255}; // Blue
constexpr SDL_Color L_BLOCK_COLOR = {255, 165, 0, 255}; // Orange
constexpr SDL_Color O_BLOCK_COLOR = {255, 255, 0, 255}; // Yellow
constexpr SDL_Color S_BLOCK_COLOR = {0, 255, 0, 255}; // Green
constexpr SDL_Color T_BLOCK_COLOR = {128, 0, 128, 255}; // Purple
constexpr SDL_Color Z_BLOCK_COLOR = {255, 0, 0, 255}; // Red

// Array to associate colors with tetrominoes
constexpr SDL_Color tetrominoColors[] = {
    I_BLOCK_COLOR, // I-block
    J_BLOCK_COLOR, // J-block
    L_BLOCK_COLOR, // L-block
    O_BLOCK_COLOR, // O-block
    S_BLOCK_COLOR, // S-block
    T_BLOCK_COLOR, // T-block
    Z_BLOCK_COLOR // Z-block
};


constexpr Tetromino tetrominoes[] = {
    {4, 4, I_BLOCK}, // I-block
    {3, 3, J_BLOCK}, // J-block
    {3, 3, L_BLOCK}, // L-block
    {2, 2, O_BLOCK}, // O-block
    {3, 3, S_BLOCK}, // S-block
    {3, 3, T_BLOCK}, // T-block
    {3, 3, Z_BLOCK} // Z-block
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
            SDL_RenderFillRect(renderer, &rect); // Fill the cell

            // Draw Grid Lines
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

int getTetrominoIndex(const Tetromino &tetromino) {
    for (int i = 0; i < sizeof(tetrominoes) / sizeof(Tetromino); ++i) {
        // Check if the shapes match element by element
        bool match = true;
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                if (tetromino.shape[row][col] != tetrominoes[i].shape[row][col]) {
                    match = false;
                    break;
                }
            }
            if (!match) break;
        }
        if (match) {
            return i;
        }
    }
    return -1; // Return -1 if not found
}

void renderTetromino(SDL_Renderer *renderer, const Tetromino &tetromino, int x, int y) {
    if (const int index = getTetrominoIndex(tetromino);
        index >= 0 && index < sizeof(tetrominoColors) / sizeof(SDL_Color)) {
        auto [r, g, b, a] = tetrominoColors[index];

        for (int i = 0; i < tetromino.height; i++) {
            for (int j = 0; j < tetromino.width; j++) {
                if (tetromino.shape[i][j] == 1) {
                    SDL_SetRenderDrawColor(renderer, r, g, b, 255); // Set color based on tetromino type

                    SDL_Rect rect = {
                        GRID_OFFSET_X + (x + j) * BLOCK_SIZE, GRID_OFFSET_Y + (y + i) * BLOCK_SIZE, BLOCK_SIZE,
                        BLOCK_SIZE
                    };
                    SDL_RenderFillRect(renderer, &rect);

                    // Black Outline
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(renderer, &rect);
                }
            }
        }
    } else {
        cerr << "Error: Tetromino color index out of bounds." << endl;
    }
}

// Main Gameplay Loop
const Tetromino &getRandomTetromino() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, sizeof(tetrominoes) / sizeof(Tetromino) - 1);

    return tetrominoes[dis(gen)]; // Return a reference
}


bool checkCollision(const Tetromino &tetromino, int x, int y) {
    for (int i = 0; i < tetromino.height; i++) {
        for (int j = 0; j < tetromino.width; j++) {
            if (tetromino.shape[i][j] == 1) {
                int gridX = x + j;
                int gridY = y + i;

                // Check boundaries
                if (gridX < 0 || gridX >= GRID_WIDTH || gridY >= GRID_HEIGHT) {
                    return true;
                }

                // Check grid occupation
                if (gridY >= 0 && grid[gridY][gridX] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void lockTetromino(const Tetromino &tetromino, int x, int y) {
    for (int i = 0; i < tetromino.height; i++) {
        for (int j = 0; j < tetromino.width; j++) {
            if (tetromino.shape[i][j] == 1) {
                grid[y + i][x + j] = 1; // Mark as occupied
            }
        }
    }
}

void gameLoop(SDL_Renderer *renderer) {
    bool running = true;
    Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 dropInterval = 500; // Drop every 500ms

    const Tetromino* currentTetromino = &getRandomTetromino();
    int tetrominoX = GRID_WIDTH / 2 - currentTetromino->width / 2;
    int tetrominoY = 0;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                int newX = tetrominoX, newY = tetrominoY;

                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        newX--; // Move left
                        break;
                    case SDLK_RIGHT:
                        newX++; // Move right
                        break;
                    case SDLK_DOWN:
                        newY++; // Soft drop
                        break;
                    case SDLK_UP:
                        // Implement rotation logic
                        // rotateTetromino(*currentTetromino);
                        break;
                }

                // Apply movement only if there's no collision
                if (!checkCollision(*currentTetromino, newX, newY)) {
                    tetrominoX = newX;
                    tetrominoY = newY;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastUpdateTime > dropInterval) {
            if (!checkCollision(*currentTetromino, tetrominoX, tetrominoY + 1)) {
                tetrominoY++;
            } else {
                // Lock the tetromino in place
                lockTetromino(*currentTetromino, tetrominoX, tetrominoY);

                // Spawn a new tetromino
                currentTetromino = &getRandomTetromino();
                tetrominoX = GRID_WIDTH / 2 - currentTetromino->width / 2;
                tetrominoY = 0;

                // Check for game over
                if (checkCollision(*currentTetromino, tetrominoX, tetrominoY)) {
                    std::cout << "Game Over!" << std::endl;
                    running = false;
                }
            }
            lastUpdateTime = currentTime;
        }

        // Render the game state
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderGrid(renderer);
        renderTetromino(renderer, *currentTetromino, tetrominoX, tetrominoY);

        SDL_RenderPresent(renderer);
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

    // The main game loop
    gameLoop(renderer);

    // Clean Up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
