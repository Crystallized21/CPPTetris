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
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int grid[20][10];
private:
    int numRows;
    int numCols;
    int cellSize;

    std::vector<Color> colors;
};

#endif //GRID_H
