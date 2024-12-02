//
// Created by Michael Bui on 12/2/24.
//

#ifndef GAME_H
#define GAME_H

#pragma once
#include "blocks.cpp"
#include "grid.h"

class Game {
public:
    Game();

    Block GetRandomBlock();

    std::vector<Block> GetAllBlocks();

    void Draw();

    void HandleInput();

    void MoveBlockLeft();

    void MoveBlockRight();

    void MoveBlockDown();

    Grid grid;
private:
    bool IsBlockOutside();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};

#endif //GAME_H
