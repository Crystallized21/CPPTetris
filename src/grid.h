//
// Created by Michael Bui on 12/2/24.
//

#ifndef GRID_H
#define GRID_H

#pragma once
#include <vector>
#include <raylib.h>

class Grid {
public:
    Grid();
    void Initialize();
    void print();
    void Draw();
    int grid[20][10];
private:
    std::vector<Color> GetCellColors();

    int numRows;
    int numCols;
    int cellSize;

    std::vector<Color> colors;
};

#endif //GRID_H
