//
// Created by Michael Bui on 12/2/24.
//

#include "game.h"

Game::Game() {
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() {
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    switch (keyPressed) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            break;
        case KEY_UP:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockLeft() {
    currentBlock.Move(0, -1);
    if (IsBlockOutside()) {
        currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight() {
    currentBlock.Move(0, 1);
    if (IsBlockOutside()) {
        currentBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown() {
    currentBlock.Move(1, 0);
    if (IsBlockOutside()) {
        currentBlock.Move(-1, 0);
    }

}

bool Game::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item: tiles) {
        if (grid.IsCellOutside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() {
    currentBlock.Rotate();
    if (IsBlockOutside()) {
        currentBlock.UndoRotation();
    }
}
