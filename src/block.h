//
// Created by Michael Bui on 12/2/24.
//

#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block {
public:
    Block();

    void Draw();

    int id;
    std::map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
};

#endif //BLOCK_H
