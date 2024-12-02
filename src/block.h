//
// Created by Michael Bui on 12/2/24.
//

#ifndef BLOCK_H
#define BLOCK_H

#pragma once
#include <vector>
#include <map>
#include "position.h"

class Block {
public:
    Block();
    int id;
    std::map<int, std::vector<Position>> cells;
private:
    int cellSize;
    int roationState;
};

#endif //BLOCK_H
