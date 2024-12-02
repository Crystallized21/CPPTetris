//
// Created by Michael Bui on 12/2/24.
//

#include "block.h"

Block::Block() {
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
}

void Block::Draw() {
    std::vector<Position> tiles = cells[rotationState];
    for (Position item: tiles) {
        DrawRectangle(item.column * cellSize + 1, item.row * cellSize + 1, cellSize - 1, cellSize - 1, colors[id]);
    }
}
