//
// Created by Michael Bui on 12/2/24.
//

#ifndef COLOURS_H
#define COLOURS_H

#pragma once
#include <raylib.h>
#include <vector>

extern const Color darkGray;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

std::vector<Color> GetCellColors();

#endif //COLOURS_H
